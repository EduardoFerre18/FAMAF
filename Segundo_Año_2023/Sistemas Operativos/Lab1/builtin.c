#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "command.h"
#include "builtin.h"
#include "tests/syscall_mock.h"
#define COMMAND_AMOUNT 3 //Se puede ajustar para incluir mas comandos

char * builtin_commands[COMMAND_AMOUNT] = {"cd", "help", "exit"};

bool builtin_is_internal(scommand cmd){ //Busca el nombre del comando en bultin_commands
	assert(cmd != NULL);
	for(int i = 0; i < COMMAND_AMOUNT; i++){
		if(strcmp(builtin_commands[i], scommand_front(cmd)) == 0){
			return true;
		}
	}
	return false;
}

bool builtin_alone(pipeline p){
	assert(p != NULL);
	return pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p));
}

void builtin_run(scommand cmd){
	assert(builtin_is_internal(cmd));
	if(strcmp(scommand_front(cmd), "help") == 0){
		printf("---MyShell---\nAutores\n	Eduardo Ferre Valderrama, Agustin Astrada, Kevin Ponce, Francisco Navarro\nComandos internos\n	cd: permite moverse entre directorios\n	help: muestra informacion sobre la consola y sus autores\n	exit: finaliza la ejecucion de la consola\n");
	}
	else if(strcmp(scommand_front(cmd), "cd") == 0){
		int result = 0;
		scommand_pop_front(cmd);
		if(!scommand_is_empty(cmd)){
			char * path = scommand_front(cmd);
			result = chdir(path);
			if(result == -1){ //Error en el cambio de directorio
				printf("%s\n", strerror(errno)); //Informa al usuario del tipo de error
			}
		} else {

			result = chdir(getenv("HOME"));
		}
	}else if(strcmp(scommand_front(cmd), "exit") == 0){
		printf("Consola terminada\n");
		exit(EXIT_SUCCESS);
	}
}





