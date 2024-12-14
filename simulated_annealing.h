#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

// Realiza o Simulated Annealing para otimização
void simulated_annealing(int **current, int **goal, int num_rows, int num_cols, 
                         int max_iter, double initial_temp, double cooling_rate);

// Versão adaptativa do Simulated Annealing
void adaptive_simulated_annealing(int **current, int **goal, int num_rows, int num_cols, 
                                  int max_iter, double initial_temp, double cooling_rate);

#endif // SIMULATED_ANNEALING_H
