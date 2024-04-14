#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_hello(void)
{
	printf("Hello world from kernel\n");
	return 0;
}

semaphore semaphore_arr[NSEMAPHORE]; //El SO tiene NSEMAPHORE cantidad de semaforos (definido en param.h)

uint64 sys_sem_open(void)
{
    int sem;
    int value;
    argint(0, &sem);
    argint(1, &value);

    if (sem < 0 || NSEMAPHORE <= sem) {
        return 0;
    }

    acquire(&semaphore_arr[sem].lock);  

    if (semaphore_arr[sem].is_open) {
        release(&semaphore_arr[sem].lock);  
        return 0;
    }

    semaphore_arr[sem].is_open = 1;
    semaphore_arr[sem].count = value;

    release(&semaphore_arr[sem].lock);  

    return 1;
}

uint64 sys_sem_close(void)
{
	int sem;
	argint(0, &sem);
	if(sem < 0 || NSEMAPHORE <= sem){ 
		return 0;
	}
	acquire(&semaphore_arr[sem].lock);
	semaphore_arr[sem].is_open = 0;
	semaphore_arr[sem].count = 0;
	release(&semaphore_arr[sem].lock);
	return 1;
}

uint64 sys_sem_up(void)
{
	int sem;
	argint(0,&sem);
	if(sem < 0 || NSEMAPHORE <= sem ){ 
		return 0;
	}
	if (semaphore_arr[sem].is_open == 0){
		return 0;
	}	
	acquire(&semaphore_arr[sem].lock);
	
	semaphore_arr[sem].count = semaphore_arr[sem].count + 1; 
	if (semaphore_arr[sem].count == 1)
		wakeup(&semaphore_arr[sem]);

	release(&semaphore_arr[sem].lock);

	return 1;
}

uint64 sys_sem_down(void)
{
	int sem;
	argint(0, &sem);
	if(sem < 0 || NSEMAPHORE <= sem){ 
		return 0;
	}
	acquire(&semaphore_arr[sem].lock);
	if (semaphore_arr[sem].is_open == 0){
    release(&semaphore_arr[sem].lock);  
		return 0;
	}
	while (semaphore_arr[sem].count == 0)
		sleep(&semaphore_arr[sem], &semaphore_arr[sem].lock);

	if (semaphore_arr[sem].count >= 1)
		semaphore_arr[sem].count = semaphore_arr[sem].count - 1;

	release(&semaphore_arr[sem].lock);
	return 1;
}

