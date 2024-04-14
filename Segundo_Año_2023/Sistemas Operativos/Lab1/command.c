#include <assert.h>
#include <glib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "strextra.h"

/* scommand: comando simple. */
struct scommand_s{
    GQueue *comm_args;
    char *input_file;
    char *output_file;
};

scommand scommand_new(void) {
    scommand new_scommand = malloc(sizeof(struct scommand_s));
    assert(new_scommand != NULL);
    new_scommand->comm_args = g_queue_new();
    new_scommand->input_file = NULL;
    new_scommand->output_file = NULL;
    assert(new_scommand != NULL 
           && scommand_is_empty(new_scommand) 
           && scommand_get_redir_in(new_scommand)==NULL 
           && scommand_get_redir_out(new_scommand)==NULL);
    return new_scommand;
}

scommand scommand_destroy(scommand self) {
    assert(self != NULL);
    if (g_queue_is_empty(self->comm_args)) {
        g_queue_free(self->comm_args);
    } else {
        g_queue_free_full(self->comm_args,free);
    }
    free(self->input_file);
    free(self->output_file);
    self->comm_args = NULL;
    self->input_file = NULL;
    self->output_file = NULL;
    free(self);
    self = NULL;
    assert(self==NULL);
    return self;
}

/* Modificadores */

void scommand_push_back(scommand self, char * argument) {
    assert(self != NULL && argument != NULL);
    g_queue_push_tail(self->comm_args, argument);
}

void scommand_pop_front(scommand self) {
    assert(self != NULL && !scommand_is_empty(self));
    char *to_destroy = g_queue_pop_head(self->comm_args);
    free(to_destroy);
    to_destroy = NULL;
}

void scommand_set_redir_in(scommand self, char * filename) {
    assert(self != NULL);
    if (self->input_file != NULL) {
        free(self->input_file);
        self->input_file = NULL; 
    }   
    self->input_file = filename;
}


void scommand_set_redir_out(scommand self, char * filename) {
    assert(self != NULL);
    if (self->output_file != NULL) {
        free(self->output_file);
        self->output_file = NULL;   
    }
    self->output_file = filename;
}

/* Proyectores */

bool scommand_is_empty(const scommand self) {
    assert(self != NULL);
    return g_queue_is_empty(self->comm_args);
}

unsigned int scommand_length(const scommand self) {
    assert(self != NULL);
    unsigned int length = g_queue_get_length(self->comm_args);
    return length;
}

char * scommand_front(const scommand self) {
    assert(self != NULL && !scommand_is_empty(self));
    char *front = g_queue_peek_head(self->comm_args);
    assert(front != NULL);
    return front;
}

char * scommand_get_redir_in(const scommand self) {
    assert(self != NULL);
    return self->input_file;
}

char * scommand_get_redir_out(const scommand self) {
    assert(self != NULL);
    return self->output_file;
}


char * scommand_to_string(const scommand self){
    assert(self != NULL);
    char *str = NULL;
    unsigned int index = 1;
    if (!scommand_is_empty(self)) {
            str = strmerge(g_queue_peek_head(self->comm_args),"");
        while (g_queue_get_length(self->comm_args) > index && str != NULL) {
            str = strmerge_free(str," ");
            str = strmerge_free(str, g_queue_peek_nth(self->comm_args,index));
            index ++;
        }
        if (self->output_file != NULL) {
            str = strmerge_free(str, CHAR_REDIR_OUT);
            str = strmerge_free(str, self->output_file);
        }
        if (self->input_file != NULL) {
            str = strmerge_free(str, CHAR_REDIR_IN);
            str = strmerge_free(str, self->input_file);
        }
    } else {
        str = strdup("");
    }
    assert(scommand_is_empty(self) || scommand_get_redir_in(self) == NULL 
           || scommand_get_redir_out(self) == NULL || strlen(str) > 0);
    return str;
}


/* pipeline: tubería de comandos. */
struct pipeline_s {
    bool wait;
    GQueue* pipe;
};

pipeline pipeline_new(void) {
    pipeline new;
    new = malloc(sizeof(struct pipeline_s));
    new -> pipe = g_queue_new();
    new -> wait = true;
    return new;
}

pipeline pipeline_destroy(pipeline self) {
    assert(self!=NULL);
    scommand destroy_me;
    while (!g_queue_is_empty(self->pipe)) {
        destroy_me = g_queue_pop_head(self->pipe);
        destroy_me = scommand_destroy(destroy_me);
    }
    g_queue_free(self->pipe);
    free(self);
    self = NULL;
    assert(self == NULL);
    return self;
}

/* Modificadores */

void pipeline_push_back(pipeline self, scommand sc) {
    assert(self != NULL && sc != NULL);
    g_queue_push_tail(self->pipe,sc);
    assert(!pipeline_is_empty(self));
}

void pipeline_pop_front(pipeline self) {
    assert(self != NULL && !pipeline_is_empty(self));
    scommand to_destroy = g_queue_pop_head(self->pipe);
    scommand_destroy(to_destroy);
}

void pipeline_set_wait(pipeline self, const bool w) {
    assert(self != NULL);
    self->wait = w;
}

/* Proyectores */

bool pipeline_is_empty(const pipeline self) {
    assert(self != NULL);
    return g_queue_is_empty(self->pipe);
}

unsigned int pipeline_length(const pipeline self) {
    assert(self != NULL);
    unsigned int length = g_queue_get_length(self->pipe);
    return length;
}

scommand pipeline_front(const pipeline self) {
    assert(self != NULL && !pipeline_is_empty(self));
    scommand front = g_queue_peek_head(self->pipe);
    assert(front != NULL);
    return front;
}

bool pipeline_get_wait(const pipeline self) {
    assert(self != NULL);
    return self->wait;
}

char * pipeline_to_string(const pipeline self) {
    assert(self != NULL);
    char * str = NULL;
    char * aux;
    unsigned int index = 1;
    if (!pipeline_is_empty(self)) {
        str = scommand_to_string(g_queue_peek_head(self->pipe));
        while (g_queue_get_length(self->pipe) > index) {
            str = strmerge_free(str, CHAR_PIPE);
            aux = scommand_to_string(g_queue_peek_nth(self->pipe,index));
            str = strmerge_free(str, aux);
            free(aux);
            index ++;
        }
        if (self->wait == false) {
            str = strmerge_free(str, CHAR_BACKGROUND);
        }
    } else {
        str = strdup("");
    }
    assert(pipeline_is_empty(self) || pipeline_get_wait(self) || strlen(str)>0);
    return str;
}
