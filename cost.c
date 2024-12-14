#include <math.h>
#include "cost.h"
#include "grid.h"

// Calcula o custo baseado na diferença entre o estado atual e o objetivo, 
// e no número de células vivas no estado atual
double calculate_cost(int **state, int **goal, int **next, int num_rows, int num_cols) {
    evolve(state, next, num_rows, num_cols); // Gera a próxima geração
    double difference_cost = 0.0, live_cells_cost = 0.0;

    // Calcula o custo baseado na diferença e no número de células vivas
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (next[i][j] != goal[i][j]) {
                difference_cost += 1.0;
            }
            if (state[i][j] == ALIVE) {
                live_cells_cost += 1.0;
            }
        }
    }

    // Ajuste dinâmico dos pesos
    double alpha = 20.0 * (1.0 + difference_cost / (num_rows * num_cols));
    double beta = 1.0;
    double total_cost = alpha * difference_cost + beta * live_cells_cost;

    // Retorna custo infinito caso ultrapasse um limite
    return (total_cost > 1e6) ? INFINITY : total_cost;
}
