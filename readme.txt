1. Árvore Binária de Busca Balanceada (Árvore AVL)

    Onde: camp.h (struct camp)

    Por que: Utilizada para o gerenciamento do Ranking do Campeonato. A árvore AVL mantém os nós balanceados pela altura, garantindo que buscas, inserções de novos resultados e atualizações de pontuação ocorram em tempo logarítmico O(log n). Isso oferece o desempenho ideal para manter o placar dinâmico e ordenado após cada corrida.

2. Fila de Prioridade (Max-Heap / Min-Heap)

    Onde: corridas.h (HeapCorridas) e oficina.h (HeapOficina)

    Por que: O Heap é a estrutura ideal para acessar o elemento de maior ou menor prioridade instantaneamente. Em corridas.h, garante que a próxima corrida a ser executada seja sempre a de maior prioridade. Na oficina.h, permite que karts destruídos (perda total) furem a fila padrão de manutenção, sendo consertados prioritariamente com base na sua urgência.

3. Fila Simples (FIFO - First In, First Out)

    Onde: oficina.h (FilaOficina e Nofila)

    Por que: Usada para o conserto de karts com danos comuns (damaged). Segue a lógica justa de "quem chega primeiro, sai primeiro" para o atendimento mecânico, permitindo inserções no fim e remoções no início da fila em tempo constante O(1).

4. Lista Duplamente Encadeada

    Onde: pilotos.h (NoPiloto) e historico.h (Historico)

    Por que: Na listagem de Pilotos, a estrutura permite navegação bidirecional (avançar e retroceder nos menus) e otimiza a remoção de participantes. No Histórico, simula uma "linha do tempo", permitindo iterar facilmente pelas temporadas passadas ou avançar para as mais recentes.

5. Lista Simplesmente Encadeada

    Onde: itens.h (struct item)

    Por que: Utilizada para o catálogo e estoque de itens especiais do jogo. Como os itens são processados iterando em uma única direção (para visualização, sorteios ou distribuição nas corridas), a lista simples atende perfeitamente ao requisito ao mesmo tempo em que economiza memória ao omitir o ponteiro "anterior".


 Como Compilar e Executar
O projeto adota uma arquitetura modularizada, separando o código-fonte (`src/`) das assinaturas e cabeçalhos (`include/`). A automação da compilação é garantida pelo `Makefile`.

Pré-requisitos
* Compilador GCC
* Ferramenta GNU Make

 Compilação e Execução
Na raiz do projeto, execute o comando de compilação:

bash
make