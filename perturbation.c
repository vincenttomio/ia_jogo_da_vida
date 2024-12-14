#include <stdlib.h>
#include "perturbation.h"
#include "grid.h"

// Aplica pequenas perturbações no estado, alterando de 1 a 3 células aleatoriamente
void perturb_state(int **state, int num_rows, int num_cols) {
    int perturbations = (rand() % 3) + 1; // Define de 1 a 3 células para perturbar

    for (int k = 0; k < perturbations; k++) {
        int x, y;

        // Seleciona células aleatórias até encontrar uma válida
        do {
            x = rand() % num_rows;
            y = rand() % num_cols;
        } while (state[x][y] == ALIVE && count_neighbors(state, x, y, num_rows, num_cols) == 0);

        // Inverte o estado da célula selecionada
        state[x][y] = 1 - state[x][y];
    }
}
