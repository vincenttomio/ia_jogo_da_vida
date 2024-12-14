#include <stdio.h>
#include <stdarg.h>
#include "log_utils.h"

// Variável global para o arquivo de log
FILE *log_file = NULL;

// Inicializa o arquivo de log
void init_log(const char *file_name) {
    log_file = fopen(file_name, "w");
    if (log_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de log: %s\n", file_name);
    }
}

// Finaliza o arquivo de log
void close_log() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

// Função de log (semelhante ao printf)
void log_message(const char *format, ...) {
    va_list args;

    // Envia para o arquivo de log, se aberto
    if (log_file != NULL) {
        va_start(args, format);
        vfprintf(log_file, format, args);
        va_end(args);
        fflush(log_file); // Garante que o log seja gravado imediatamente
    }

    // Opcional: também imprime na tela para depuração
    va_start(args, format);
    // vprintf(format, args);
    va_end(args);
}
