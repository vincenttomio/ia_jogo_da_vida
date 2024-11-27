#include <stdlib.h>
#include "perturbation.h"
#include "grid.h"

// void perturb_state(int **state, int n, int m) {
//     int x = rand() % (n - 2) + 1;
//     int y = rand() % (m - 2) + 1;
//     state[x][y] = 1 - state[x][y];
// }

// void perturb_state(int **state, int n, int m) {
//     int perturbations = (rand() % 3) + 1; // De 1 a 3 células para perturbar
//     for (int k = 0; k < perturbations; k++) {
//         int x = rand() % (n - 2) + 1;
//         int y = rand() % (m - 2) + 1;
//         state[x][y] = 1 - state[x][y]; // Inverte o estado da célula escolhida
//     }
// }

void perturb_state(int **state, int n, int m) {
    int perturbations = (rand() % 3) + 1; // De 1 a 3 células para perturbar
    for (int k = 0; k < perturbations; k++) {
        int x = rand() % n;  // Inclui bordas
        int y = rand() % m;  // Inclui bordas
        state[x][y] = 1 - state[x][y]; // Inverte o estado da célula escolhida
    }
}
    