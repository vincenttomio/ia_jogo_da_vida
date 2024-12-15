# Jogo da Vida - Reversão de Estados

Projeto feito para a matéria de - Inteligência Artificial - 2024-2 (CI1209)

### Integrantes: 

Erick da Silva Santos - GRR20242593

Vincent Tomio - GRR20206365

### Execução

make

./game-of-life < entrada.txt

## Descrição do Projeto

Este projeto implementa uma solução para o problema de reversão de estados do Jogo da Vida de Conway. Dada uma matriz representando o estado atual do jogo, o programa busca encontrar um estado anterior que evolua para o estado dado, minimizando o número de células vivas.

### Especificações Principais

- **Entrada:** Uma matriz n x m representando o estado atual, com bordas fixas mortas.
- **Saída:** Uma matriz n x m que representa um estado anterior válido com o menor número possível de células vivas.
- **Restrições:** Tempo máximo de execução de 300 segundos e consumo de memória limitado a 8GB.

---

## Arquivos do Projeto

### Principais Módulos

1. **`main.c`**
   - Ponto de entrada do programa.
   - Responsável por processar argumentos, alocar memória e coordenar as etapas de análise e resolução da matriz.
   - **Funções**:
     - `main()`: Configura parâmetros, lê a matriz de entrada e coordena o fluxo do programa.

2. **`grid.c`**
   - Manipulação básica de matrizes. Implementa operações básicas como alocação, impressão e manipulação de matrizes, além de funções mais avançadas como evolução do estado da matriz e integração com Simulated Annealing.
   - **Funções**:
     - `allocate_grid()`: Aloca dinamicamente uma matriz 𝑛×𝑚 e inicializa seus elementos com zero.
     - `free_grid()`: Libera a memória de uma matriz previamente alocada com allocate_grid.
     - `print_grid()`: Imprime os elementos de uma matriz 𝑛×𝑚 na saída padrão, organizados em linhas.
     - `copy_grid()`: Copia o conteúdo de uma matriz src para outra matriz dest.
     - `log_grid()`: Registra a matriz em um arquivo de log.
     - `count_neighbors()`: Conta o número de vizinhos vivos de uma célula (x,y).
     - `evolve()`: Gera o próximo estado da matriz next a partir do estado atual current usando as regras do Jogo da Vida.
     - `next_generation()`: Outra implementação da evolução do estado, considerando diretamente as regras do Jogo da Vida.
     - `count_live_cells()`: Conta o número total de células vivas em uma matriz.
     - `run_trials()`: Executa múltiplas tentativas para encontrar o estado anterior ideal com o menor número de células vivas, usando Simulated Annealing.
     - `memcmp_grid()`: Compara duas matrizes para verificar se são idênticas.
     - `intelligent_initialize()`: Inicializa a matriz com base na matriz atual, priorizando células que têm alta probabilidade de estar vivas na geração anterior.
     - `run_trials_adaptive()`: Variante adaptativa de run_trials, ajustando dinamicamente os parâmetros de Simulated Annealing durante a execução.

3. **`matrix_splitter.c`**
   - Implementa funções que processam matrizes, especialmente dividindo-as em submatrizes, detectando padrões conectados e manipulando esses padrões para solucionar o problema de forma modular. Este módulo é essencial para otimizar o tratamento de matrizes maiores, dividindo-as em partes menores e gerenciáveis. Usa busca em profundidade (DFS) para encontrar padrões e organiza submatrizes para facilitar o processamento paralelo ou modular.
   - **Funções principais**:
     - `detect_patterns()`: Detecta padrões conectados em uma matriz usando DFS (busca em profundidade) e adiciona uma borda de zeros ao redor de cada padrão detectado.
     - `divide_matrix()`: Divide uma matriz em submatrizes de tamanho fixo (sub_rows × sub_cols), adicionando uma borda de zeros ao redor de cada submatriz.
     - `analyze_and_split_matrix()`: Analisa uma matriz e decide entre detectar padrões conectados ou dividi-la em submatrizes menores.
     - `solve_divided_matrix()`: Resolve uma matriz dividida em submatrizes, aplicando algoritmos de otimização como Simulated Annealing em cada submatriz.
     - `calcular_numero_submatrixes()`: Função para calcular número de sub-matrixes.
     - `extrair_submatrix()`: Função para extrair sub-matrix com borda.
     - `run_and_copy()`: Resolve a submatrix usando Simulated Annealing e Copiar resultado de volta para a matrix original. 

4. **`simulated_annealing.c`**
   - Implementa duas variações do algoritmo Simulated Annealing, que busca soluções aproximadas para problemas de otimização. Essas funções são aplicadas, ajudando a encontrar estados anteriores que minimizem o número de células vivas e satisfaçam as condições do problema. Explora o espaço de soluções introduzindo pequenas alterações no estado atual e aceita ou rejeita essas mudanças com base em critérios probabilísticos, reduzindo gradualmente a chance de aceitar alterações que aumentem o custo.
   - **Funções principais**:
     - `simulated_annealing()`: Implementa o algoritmo clássico de Simulated Annealing para encontrar um estado anterior válido. Explora estados alterados (new_state) e avalia se devem substituir o estado atual (current) com base no custo e na temperatura atual.
     - `adaptive_simulated_annealing()`: Variante adaptativa do Simulated Annealing, que ajusta dinamicamente a temperatura com base na falta de melhorias no custo. 

5. **`cost.c`**
   - Cálculo do custo de transições entre estados. Ele avalia a adequação de um estado potencial em relação ao estado objetivo, considerando tanto a conformidade com as regras quanto a minimização de células vivas. Avaliar o desvio entre o estado gerado e o estado objetivo, penalizando desajustes e excessos de células vivas.
   - **Funções principais**:
     - `calculate_cost()`: Calcula o custo baseado na diferença de estados e número de células vivas.

6. **`perturbation.c`**
   - Implementa a lógica de perturbação de estados. Essa perturbação é essencial para algoritmos de otimização como Simulated Annealing, que exploram diferentes estados no espaço de soluções.
   - **Funções principais**:
     - `perturb_state()`: Introduz perturbações em até 3 células aleatórias na matriz state. Garante que as perturbações sejam válidas, ou seja, evita modificar células vivas que não possuem vizinhos vivos.

---

## Estratégia Implementada

No desenvolvimento do projeto para resolver o problema reverso do Jogo da Vida, várias estratégias foram exploradas com o objetivo de encontrar uma solução eficiente e escalável. Inicialmente, utilizamos a abordagem de **backtracking**, que consiste em explorar todas as combinações possíveis de estados iniciais para encontrar um resultado. Contudo, o tempo de processamento crescia exponencialmente com o tamanho da matriz, tornando essa solução inviável para matrizes maiores que 6 x 6.

Diante desse desafio, optamos por implementar o algoritmo **Simulated Annealing (SA)**, uma técnica heurística inspirada no resfriamento físico. O SA permite explorar o espaço de soluções de maneira probabilística, escapando de mínimos locais. Apesar disso, a versão inicial do SA apresentou limitações de performance para matrizes maiores, sendo eficaz apenas para matrizes de até 6 x 6. Para superar essa limitação, o algoritmo foi otimizado, evoluindo para uma versão **adaptativa do SA**, que ajusta dinamicamente a temperatura com base no progresso da busca. Isso aumentou a eficiência do algoritmo, tornando-o mais robusto e permitindo a resolução de matrizes 6 x 6 de forma consistente.

No entanto, mesmo com as melhorias do SA adaptativo, ele ainda não conseguia processar matrizes maiores de forma eficiente dentro do tempo esperado. Para lidar com esse problema, desenvolvemos uma nova estratégia: **Divisão e Resolução**. Essa abordagem divide o problema em subproblemas menores e independentes, que podem ser resolvidos pelo SA adaptativo. A estratégia é composta por três cenários principais:

1. **Matrizes de até 6 x 6:**  
   Essas matrizes são resolvidas diretamente pelo SA adaptativo, alcançando soluções ótimas de forma eficiente.

2. **Matrizes maiores com padrões claros:**  
   Quando a matriz original contém padrões conectados com bordas de zeros, e esses padrões têm dimensões menores ou iguais a 6 x 6, a matriz é segmentada nesses padrões. Cada padrão é resolvido pelo SA adaptativo, e os resultados são recombinados na matriz original.

3. **Matrizes maiores sem padrões claros:**  
   Para matrizes que não possuem padrões evidentes ou cujos padrões excedem 6 x 6, a matriz é dividida em submatrizes fixas de 6 x 6, incluindo bordas de zeros. Cada submatriz é processada individualmente pelo SA adaptativo, e os resultados são recombinados para formar a matriz final.

### Benefícios da Estratégia de Divisão e Resolução

Essa estratégia trouxe diversos benefícios. A divisão em submatrizes reduziu significativamente a complexidade do problema, permitindo que o SA adaptativo fosse aplicado em partes menores da matriz, otimizando o tempo de processamento e a utilização de recursos computacionais. Além disso, a detecção de padrões conectados evitou a necessidade de dividir completamente a matriz original em submatrizes, preservando as relações entre células e melhorando a precisão dos resultados.


# Análise de Custo Computacional

---

## 1. Custo Computacional do Jogo da Vida

No Jogo da Vida, a cada iteração, o estado de uma célula depende de:

- O estado da célula atual.
- Os estados das 8 células vizinhas.

### Custo para uma Matriz (n x m)

Para calcular o estado de toda a matriz, é necessário:

- Iterar sobre todas as células (n x m).
- Para cada célula, verificar as 8 vizinhas.

O custo para processar a matriz inteira, considerando uma única iteração, é dado por:

C_matriz = n x m x 8


Ou seja, O(n x m), onde cada célula exige um cálculo constante.

Quando buscamos o estado anterior, utilizamos técnicas como **Simulated Annealing** e perturbações iterativas, o que requer múltiplas iterações (I) para encontrar o estado desejado. Assim, o custo total é:

C_total = I x n x m x 8


Para uma matriz grande (n, m > 100), o custo cresce rapidamente, dificultando a obtenção do resultado em tempo razoável.

---

## 2. Dividir a Matriz em Submatrizes

Uma abordagem mais eficiente é dividir a matriz n x m em submatrizes menores, como 6 x 6, e resolver cada submatriz separadamente. Isso reduz o custo computacional ao custo de resolver as submatrizes mais o custo de processar as bordas.

### Custo para Submatrizes s x s

Ao dividir uma matriz n x m em submatrizes s x s, o número de submatrizes é:

n/s x m/s


O custo computacional para resolver cada submatriz é proporcional a:

C_submatriz = s x s x 8


Assim, o custo total para resolver todas as submatrizes é:

C_total_submatrizes = I x n/s x m/s x (s x s x 8)


## 3. Comparação dos Custos

### Matriz Grande (n x m):

C_matriz = I x n x m x 8


### Matriz Dividida (s x s):

C_submatriz_completa = I x n/s x m/s x (s x s x 8) + C_bordas

Ao dividir a matriz, o custo é significativamente menor para valores de s pequenos, porque:

1. A complexidade de s^2 é menor do que n x m.
2. Processar múltiplas submatrizes s x s tem menos impacto computacional em n/s x m/s do que resolver n x m diretamente.


## 4. Exemplo Prático

**Considere:**
- Matriz (100 x 100).
- Submatrizes (6 x 6).

### Matriz Inteira:

C_matriz = I x 100 x 100 x 8 = 800,000 x I

### Matriz Dividida:
- **Número de submatrizes:** 100/6 x 100/6 ≈ 16 x 16 = 256

- **Custo para cada submatriz:** I x 6 x 6 x 8 = 288 x I

- **Custo total para submatrizes:** 256 x 288 x I = 73,728 x I

- **Custo para bordas:** 256 x 2 x 6 x I = 3,072 x I


### Custo final:

C_total_submatrizes = 73,728 x I + 3,072 x I = 76,800 x I


### Comparação:

C_matriz = 800,000 x I vs  C_submatriz = 76,800 x I


### Conclusão

O projeto evoluiu significativamente, desde uma abordagem inicial baseada em backtracking até uma solução robusta e escalável com SA adaptativo e a estratégia de Divisão e Resolução. Essa abordagem combinou eficiência, precisão e flexibilidade, oferecendo uma solução prática para o problema reverso do Jogo da Vida e abrindo caminho para futuras otimizações.

Dividir a matriz em submatrizes menores é uma estratégia significativamente mais eficiente para resolver o problema reverso do Jogo da Vida. Além de reduzir o custo computacional, a abordagem possibilita paralelismo e otimização de memória, tornando o algoritmo mais escalável e prático para matrizes grandes.


---
