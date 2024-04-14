#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int result = sem_open(9, 2);
	int res = sem_down(1);
	printf("SEM: %d\n",res);
	if(res==-1) printf("Eror Sem");
	if(result == -1) printf("Error\n");
	return 0;
}
