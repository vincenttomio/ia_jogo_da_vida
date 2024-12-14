#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grid.h"
#include "cost.h"
#include "perturbation.h"
#include "simulated_annealing.h"

// Realiza o Simulated Annealing para encontrar o estado ideal
void simulated_annealing(int **current, int **goal, int num_rows, int num_cols, 
                         int max_iter, double initial_temp, double cooling_rate) {
    int **next = allocate_grid(num_rows, num_cols); // Matriz auxiliar para próxima geração
    double temp = initial_temp; // Temperatura inicial
    double cost = calculate_cost(current, goal, next, num_rows, num_cols);

    for (int iter = 0; iter < max_iter; iter++) {
        int **new_state = allocate_grid(num_rows, num_cols);
        copy_grid(new_state, current, num_rows, num_cols); // Copia o estado atual para modificação

        perturb_state(new_state, num_rows, num_cols); // Aplica perturbações no estado
        double new_cost = calculate_cost(new_state, goal, next, num_rows, num_cols);
        double delta_cost = new_cost - cost;

        // Aceita mudanças se o custo diminuir ou baseado em probabilidade
        if (delta_cost < 0 || exp(-delta_cost / temp) > ((double)rand() / RAND_MAX)) {
            copy_grid(current, new_state, num_rows, num_cols);
            cost = new_cost;
        }

        temp *= cooling_rate; // Reduz a temperatura gradualmente
        free_grid(new_state, num_rows); // Libera a matriz temporária

        // Encerra se a temperatura atingir um limite
        if (temp < 1e-10) break;
    }

    free_grid(next, num_rows); // Libera a matriz auxiliar
}

// Versão adaptativa do Simulated Annealing
void adaptive_simulated_annealing(int **current, int **goal, int num_rows, int num_cols, 
                                  int max_iter, double initial_temp, double cooling_rate) {
    int **next = allocate_grid(num_rows, num_cols); // Matriz auxiliar para próxima geração
    double temp = initial_temp; // Temperatura inicial
    double cost = calculate_cost(current, goal, next, num_rows, num_cols);
    int no_improvement_count = 0; // Contador de iterações sem melhoria

    for (int iter = 0; iter < max_iter; iter++) {
        int **new_state = allocate_grid(num_rows, num_cols);
        copy_grid(new_state, current, num_rows, num_cols); // Copia o estado atual para modificação

        perturb_state(new_state, num_rows, num_cols); // Aplica perturbações no estado
        double new_cost = calculate_cost(new_state, goal, next, num_rows, num_cols);
        double delta_cost = new_cost - cost;

        // Atualiza o estado atual se o custo diminuir
        if (delta_cost < 0) {
            no_improvement_count = 0;
            copy_grid(current, new_state, num_rows, num_cols);
            cost = new_cost;
        } else {
            no_improvement_count++;
            double accept_prob = exp(-delta_cost / temp);

            // Aceita mudanças com base em probabilidade
            if (accept_prob > ((double)rand() / RAND_MAX)) {
                copy_grid(current, new_state, num_rows, num_cols);
                cost = new_cost;
            }
        }

        // Ajusta a temperatura se não houver melhorias por muitas iterações
        if (no_improvement_count > max_iter / 10) {
            temp *= 1.5;
            no_improvement_count = 0;
        } else {
            temp *= cooling_rate;
        }

        free_grid(new_state, num_rows); // Libera a matriz temporária

        // Encerra se a temperatura atingir um limite
        if (temp < 1e-10) break;
    }

    free_grid(next, num_rows); // Libera a matriz auxiliar
}
