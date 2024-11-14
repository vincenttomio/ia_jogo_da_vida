#include "cost.h"
#include "grid.h"

int calculate_cost(int **state, int **goal, int **next, int n, int m) {
    evolve(state, next, n, m);
    int difference_cost = 0, live_cells_cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (next[i][j] != goal[i][j]) {
                difference_cost++;
            }
            if (state[i][j] == ALIVE) {
                live_cells_cost++;
            }
        }
    }
    int alpha = 10;
    int beta = 1;
    return alpha * difference_cost + beta * live_cells_cost;
}

