#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

/* Parsea un comando simple */

static scommand parse_scommand(Parser p) {
    assert(!parser_at_eof(p));
    scommand cmd = scommand_new();
    bool pipe = false;
    arg_kind_t arg_type;
    char *arg = NULL;

    while (!pipe && !parser_at_eof(p)){
        arg = parser_next_argument(p, &arg_type);
        if (arg_type == ARG_NORMAL && arg != NULL) {
            scommand_push_back(cmd, arg);   
        } else if (arg_type == ARG_INPUT && arg != NULL) {
            scommand_set_redir_in(cmd, arg);
        } else if (arg_type == ARG_OUTPUT && arg != NULL) {
            scommand_set_redir_out(cmd, arg);
        } else if (arg_type == ARG_INPUT && arg == NULL) {
            // Se encontró una redirección de entrada sin nombre de archivo
            printf("Error: Falta el nombre del archivo de entrada.\n");
            scommand_destroy(cmd);
            return NULL;
        } else if (arg_type == ARG_OUTPUT && arg == NULL) {
            // Se encontró una redirección de salida sin nombre de archivo
            printf("Error: Falta el nombre del archivo de salida.\n");
            scommand_destroy(cmd);
            return NULL;
        } else {
            pipe = true;
        }
        parser_skip_blanks(p);
    }
    return cmd;
}

/* Parsea un pipeline */

pipeline parse_pipeline(Parser p) {
    pipeline result = pipeline_new();
    scommand cmd = NULL;
    bool error = false, another_pipe = true;

    cmd = parse_scommand(p);
    error = (cmd == NULL || scommand_is_empty(cmd));
    while (another_pipe && !error) {
        pipeline_push_back(result, cmd);
        if (!parser_at_eof(p)) {
            parser_op_pipe(p, &another_pipe);
            if (another_pipe) {
                parser_skip_blanks(p);
                cmd = parse_scommand(p);
                error = (cmd == NULL || scommand_is_empty(cmd));
                parser_skip_blanks(p);
            }

        } else {
            another_pipe = false;
        }
    }
    /* Reviso cuando hay un & y/o basura al final del comando */
    bool wait = false;
    bool garbage = false;
    if (!parser_at_eof(p)) {
        parser_op_background(p, &wait);
        pipeline_set_wait(result, !wait);
        parser_garbage(p, &garbage);
    }

    /* Hago cleanup si hay un error */
    if (error) {
        if (!pipeline_is_empty(result)) {
            printf("Invalid command.\n");
        }
        result = pipeline_destroy(result);
        if (cmd != NULL) {
            cmd = scommand_destroy(cmd);
            cmd = NULL;
        }
        result = NULL;
    }

    /* Considero inválido <command> & <gabage> */
    if (garbage) {
        if (wait) {
            result = pipeline_destroy(result);
            result = NULL;
            printf("Invalid command.\n");
        }
    }
    return result;
}

