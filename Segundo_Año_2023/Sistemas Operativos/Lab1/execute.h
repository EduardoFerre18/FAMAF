/* Ejecuta comandos simples y pipelines.
 * No toca ningún comando interno.
 */

#ifndef EXECUTE_H
#define EXECUTE_H

#include "command.h"

#define READ_END 0 //Define el extremo de lectura para el pipe
#define WRITE_END 1 //Define el extremo de escritura para el pipe

void open_input_files(scommand s);

/*
 * Dado un scommand, abre los archivos de redireccion de entrada
 * y apunta el STDIN a ese archivo
 *
 * Requires: s!=NULL
*/

void open_output_files(scommand s);

/*
 * Dado un scommand, abre los archivos de redireccion de salida
 * y apunta el STDOUT a ese archivo
 *
 * Requires: s!=NULL
*/

void execute_pipeline(pipeline apipe);
/*
 * Ejecuta un pipeline, identificando comandos internos, forkeando, y
 *   redirigiendo la entrada y salida. puede modificar `apipe' en el proceso
 *   de ejecución.
 *   apipe: pipeline a ejecutar
 * Requires: apipe!=NULL
 */

#endif /* EXECUTE_H */
