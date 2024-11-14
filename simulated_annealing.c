#include <stdio.h>
#include <stdlib.h>  // Necessário para o RAND_MAX
#include <math.h>
#include "grid.h"
#include "cost.h"
#include "perturbation.h"
#include "simulated_annealing.h"

// Função de Simulated Annealing
void simulated_annealing(int **current, int **goal, int n, int m, int max_iter, double initial_temp, double cooling_rate) {
    int **next = allocate_grid(n, m);
    double temp = initial_temp;
    int cost = calculate_cost(current, goal, next, n, m);

    for (int iter = 0; iter < max_iter; iter++) {
        int **new_state = allocate_grid(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                new_state[i][j] = current[i][j];
            }
        }

        perturb_state(new_state, n, m);
        int new_cost = calculate_cost(new_state, goal, next, n, m);
        double delta_cost = new_cost - cost;

        if (delta_cost < 0 || exp(-delta_cost / temp) > ((double)rand() / RAND_MAX)) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    current[i][j] = new_state[i][j];
                }
            }
            cost = new_cost;
        }

        temp *= cooling_rate;
        free_grid(new_state, n);

        if (temp < 1e-10) break;
    }

    free_grid(next, n);
}
