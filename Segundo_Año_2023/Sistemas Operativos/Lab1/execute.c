#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "execute.h"
#include "command.h"
#include "builtin.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "tests/syscall_mock.h"

static char **get_args(scommand s, unsigned int length) {
    char **args = calloc(length+1,sizeof(char *));
    if(args!=NULL){
    	for (unsigned int i = 0u; i < length;i++) {
        	args[i] = strdup(scommand_front(s));
        	scommand_pop_front(s);
    	}
    	args[length]=NULL;
    }
    return args;
}

static char **free_args(char **args, unsigned int length) {
    for (unsigned int i = 0; i <= length; i++) {
        free(args[i]);
        args[i] = NULL;
    }
    free(args);
    args = NULL;
    return args;
}

void open_input_files(scommand s){
	assert(s!=NULL);

	if(scommand_get_redir_in(s)!=NULL){
		int fd_open = open(scommand_get_redir_in(s),O_RDONLY, 0);
		if(fd_open > 0){
			dup2(fd_open, STDIN_FILENO);
			close(fd_open);
		} else {
			fprintf(stderr,"Error al abrir el archivo %s\n",scommand_get_redir_in(s));
			exit(EXIT_FAILURE);
		}
	}
}

void open_output_files(scommand s){
	assert(s!=NULL);

	if(scommand_get_redir_out(s)!=NULL){
		int fd_open = open(scommand_get_redir_out(s), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if(fd_open > 0){
			dup2(fd_open, STDOUT_FILENO);
			close(fd_open);
		} else {
			fprintf(stderr,"Error al abrir el archivo %s\n",scommand_get_redir_out(s));
			exit(EXIT_FAILURE);
		}
	}
}

void execute_pipeline(pipeline apipe)
{
	assert(apipe!=NULL);
	int fd[2];
	unsigned int pipe_len = pipeline_length(apipe); 
	if(pipe_len==2u){
		scommand s1 = pipeline_front(apipe);
		
		int rv_pipe = pipe(fd);
		
		if(rv_pipe == -1) {
			fprintf(stderr, "Pipe falló\n");
			exit(EXIT_FAILURE);
		}

		if(builtin_is_internal(s1)){
			builtin_run(s1);
		} else {	
			char **comm_args1 = get_args(s1,scommand_length(s1));
			int rv_fork = fork();
			if(rv_fork == 0){
				close(fd[READ_END]);
				
				open_input_files(s1); //Abre los archivos para redireccion de entrada y hace que STDIN apunte a ese archivo
				if(scommand_get_redir_out(s1)!=NULL){
					open_output_files(s1); //Abre los archivos para redireccion de salida y hace que STDOUT apunte a ese archivo
				} else {
					dup2(fd[WRITE_END], STDOUT_FILENO);
				}
				
				close(fd[WRITE_END]);
				
				execvp(comm_args1[0],comm_args1);	
				fprintf(stderr, "%s:Comando no encontrado\n",comm_args1[0]);
				kill(getpid() , SIGKILL); // Cierro al proceso hijo
			}else if(rv_fork > 0){
				close(fd[WRITE_END]);
				free_args(comm_args1,scommand_length(s1));
				pipeline_pop_front(apipe);
				scommand s2 = pipeline_front(apipe);
				
				if(builtin_is_internal(s2)){
					builtin_run(s2);
				} else {
					char ** comm_args2 = get_args(s2,scommand_length(s2));
					int rc_fork = fork();
					if(rc_fork == 0){
						close(fd[WRITE_END]);
						
						if(scommand_get_redir_in(s2)!=NULL){
							open_input_files(s2);
						} else {
							dup2(fd[READ_END], STDIN_FILENO); 	
						}
						close(fd[READ_END]);
						open_output_files(s2); // Abre los archivos para redireccion de salida y hace que STDOUT apunte a ese archivo
						
						execvp(comm_args2[0],comm_args2);	
						fprintf(stderr, "%s:Comando no encontrado\n",comm_args2[0]);
						kill(getpid() , SIGKILL); // Cierro al proceso hijo
					}else if(rc_fork > 0){
						close(fd[READ_END]);
						free_args(comm_args2,scommand_length(s2));		
					}else if(rc_fork==-1){
						fprintf(stderr, "Fork falló\n");
						exit(EXIT_FAILURE);
					}
					
					if(pipeline_get_wait(apipe)){
							waitpid(rv_fork,NULL,0);
							waitpid(rc_fork,NULL,0);
					}	
				}
			}else if(rv_fork==-1){
				fprintf(stderr, "Fork falló\n");
				exit(EXIT_FAILURE);
			}
		}

	} else if (pipe_len==1u){
		scommand s = pipeline_front(apipe);
		
		if(builtin_is_internal(s)){
			builtin_run(s);
		} else {
			char ** comm_args = get_args(s,scommand_length(s)); 
			int rc_fork = fork();
			
			if(rc_fork == 0){
			
				open_input_files(s);
				open_output_files(s);
				
				execvp(comm_args[0],comm_args);
				fprintf(stderr, "%s:Comando no encontrado\n",comm_args[0]);
				kill(getpid() , SIGKILL); // Cierro al proceso hijo
			} else if(rc_fork==-1){
				fprintf(stderr, "Fork falló\n");
				exit(EXIT_FAILURE);
			} else if(rc_fork > 0){
				if(pipeline_get_wait(apipe)){
					waitpid(rc_fork,NULL,0);
				}
				free_args(comm_args,scommand_length(s));				
			}
		}	
	} else if (pipe_len==0u){
		printf("Pipeline vacío\n");
	} else {
        printf("El tamaño máximo permitido de pipeline es 2\n");
    }

}
