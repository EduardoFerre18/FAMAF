#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "ERROR: Se requiere un argumento para la cantidad de rondas.\n");
        exit(1);
    }

    int N = atoi(argv[1]);
    if (N < 1) {
        fprintf(2, "ERROR: El número de rondas debe ser mayor o igual a 1.\n");
        exit(1);
    }

    // Creo e inicializo semáforos
    int sem_id_1 = 0;
    int result_1 = sem_open(sem_id_1, 1);
    while(result_1 == 0){
    	sem_id_1 ++;
    	if(sem_id_1 == 64){
    		fprintf(2, "ERROR: No hay semaforos disponibles.\n");
    		exit(1);
    	}
    	result_1 = sem_open(sem_id_1, 1);
    } 
    int sem_id_2 = 0;
    int result_2 = sem_open(sem_id_2, 0);
    while(result_2 == 0){
    	sem_id_2 ++;
    	if(sem_id_2 == 64){
    		fprintf(2, "ERROR: No hay semaforos disponibles.\n");
    		exit(1);
    	}
    	result_2 = sem_open(sem_id_2, 0);
    }
    int pid = fork();
    if (pid == -1) {
        fprintf(2, "ERROR: Falló la creación de un nuevo proceso.\n");
        exit(1);
    } else if (pid == 0) {  // Proceso hijo (imprime "pong")
        for (int i = 0; i < N; i++) {
            sem_down(sem_id_2);
            printf("    pong\n");
            sem_up(sem_id_1);
        }
        exit(0);
    } else {  // Proceso padre (imprime "ping")
        for (int i = 0; i < N; i++) {
            sem_down(sem_id_1);
            printf("ping\n");
            sem_up(sem_id_2);
        }
        wait(0);
    }

    // Libero semáforos
    sem_close(sem_id_1);
    sem_close(sem_id_2);

    exit(0);
}

