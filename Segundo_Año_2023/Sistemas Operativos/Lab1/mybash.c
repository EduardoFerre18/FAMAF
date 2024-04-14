#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"

static void show_prompt(void) {
	printf ("mybash> %s ", get_current_dir_name());
	fflush (stdout);
}

int main(int argc, char *argv[]) {
	pipeline pipe;
	Parser input;
	bool quit = false;
	input = parser_new(stdin);

	while (!quit) {
		show_prompt();
		
		pipe = parse_pipeline(input);
		quit = parser_at_eof(input);
		if (pipe != NULL){	/* Hay que salir luego de ejecutar? */
			execute_pipeline(pipe);
			pipeline_destroy(pipe);
		}
	}
	parser_destroy(input); 
	input = NULL;
	return EXIT_SUCCESS;
}

