#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include <stdio.h>

// Inicializa o arquivo de log
void init_log(const char *file_name);

// Finaliza o arquivo de log
void close_log();

// Função para registrar mensagens de log
void log_message(const char *format, ...);

#endif // LOG_UTILS_H
