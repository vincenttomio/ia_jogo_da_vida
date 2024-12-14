#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "grid.h"
#include "cost.h"
#include "log_utils.h"
#include "perturbation.h"
#include "simulated_annealing.h"
#include "matrix_splitter.h"


int main(int argc, char *argv[]) {
    // Medição de tempo de início
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Medição de uso de memória inicial
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    init_log("debug.log");
    puts("Iniciando log, acesse depois informações detalhadas no arquivo: debug.log\n");


    // Leitura de entrada
    int n, m;
    log_message("Lendo matriz de entrada");
    scanf("%d %d", &n, &m);
    
    // Alocação de memória
    int **current_position = allocate_grid(n, m);


    // Leitura da matriz de entrada
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &current_position[i][j]);
        }
    }

    printf("\nImprimindo matriz de entrada:\n");
    print_grid(current_position, n, m);

    analyze_and_split_matrix(current_position, n, m);
    int **previous_state = solve_divided_matrix(current_position, n, m);


    printf("\nImprimindo matriz de estado anterior:\n");
    print_grid(previous_state, n, m);
  

    // Medição de tempo final
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_usec - start.tv_usec) / 1000000.0;

    // Medição de uso de memória final
    getrusage(RUSAGE_SELF, &usage_end);
    long memory_used = usage_end.ru_maxrss; // Uso de memória em KB

    // Imprimir estatísticas
    printf("\n--- Estatísticas de Execução ---\n");
    printf("Tempo total de execução: %.4f segundos\n", time_taken);
    printf("Memória máxima utilizada: %ld KB (%.2f MB)\n", 
           memory_used, memory_used / 1024.0);

    // Loggin info
    log_message("\n--- Estatísticas de Execução ---\n");
    log_message("Tempo total de execução: %.4f segundos\n", time_taken);
    log_message("Memória máxima utilizada: %ld KB (%.2f MB)\n", 
           memory_used, memory_used / 1024.0);


    close_log();
    return 0;
}

