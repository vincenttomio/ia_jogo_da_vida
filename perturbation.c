#include <stdlib.h>
#include "perturbation.h"
#include "grid.h"

void perturb_state(int **state, int n, int m) {
    int x = rand() % (n - 2) + 1;
    int y = rand() % (m - 2) + 1;
    state[x][y] = 1 - state[x][y];
}
