<div align="center">
  
# Simulador de Corridas e Campeonato

  <img src="https://img.shields.io/badge/C-151515?style=for-the-badge&logo=c&logoColor=white" alt="C"/>
  <img src="https://img.shields.io/badge/Linux-151515?style=for-the-badge&logo=linux&logoColor=white" alt="Linux"/>
  <img src="https://img.shields.io/badge/GCC-151515?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC"/>
  <img src="https://img.shields.io/badge/UFPel-151515?style=for-the-badge&logo=codeigniter&logoColor=white" alt="UFPel"/>

</div>

Projeto de um simulador de corridas completo, gerenciando karts, pilotos, pistas, itens (estilo Mario Kart) e um sistema integrado de campeonato e oficina mecânica. 

**Instituição:** Universidade Federal de Pelotas (UFPel) - Centro de Desenvolvimento Tecnológico  
**Curso:** Engenharia de Computação  
**Autor:** Lúcio Vagner Carvalho Souza

---

## ⚙️ Estruturas de Dados Utilizadas

O projeto faz uso intensivo de diversas estruturas de dados para gerenciar o ecossistema do jogo de forma otimizada e performática:

### 1. Árvore Binária de Busca Balanceada (Árvore AVL)
* **Onde:** `camp.h` (`struct camp`)
* **Por que:** Utilizada para o gerenciamento do Ranking do Campeonato. A árvore AVL mantém os nós balanceados pela altura, garantindo que buscas, inserções de novos resultados e atualizações de pontuação ocorram em tempo logarítmico **O(log n)**. Isso oferece o melhor desempenho para manter o placar dinâmico e ordenado após cada corrida.

### 2. Fila de Prioridade (Max-Heap / Min-Heap)
* **Onde:** `corridas.h` (`HeapCorridas`) e `oficina.h` (`HeapOficina`)
* **Por que:** O Heap é a estrutura ideal para acessar o elemento de maior ou menor prioridade instantaneamente. Em `corridas.h`, garante que a próxima corrida a ser executada seja sempre a de maior prioridade. Na `oficina.h`, permite que karts destruídos (perda total) furem a fila padrão de manutenção, sendo consertados com base na sua urgência.

### 3. Fila Simples (FIFO - First In, First Out)
* **Onde:** `oficina.h` (`FilaOficina` e `Nofila`)
* **Por que:** Usada para o conserto de karts com danos comuns (`damaged`). Segue a lógica justa de "quem chega primeiro, sai primeiro", permitindo inserções no fim e remoções no início em tempo constante **O(1)**.

### 4. Lista Duplamente Encadeada
* **Onde:** `pilotos.h` (`NoPiloto`) e `historico.h` (`Historico`)
* **Por que:** Para os **Pilotos**, permite navegação bidirecional (avançar e retroceder) nos menus de visualização e remoção de participantes em tempo **O(1)** (após encontrar o nó). Para o **Histórico**, simula perfeitamente uma "linha do tempo", permitindo ao usuário passear facilmente pelas temporadas passadas ou mais recentes.

### 5. Lista Simplesmente Encadeada
* **Onde:** `itens.h` (`struct item`)
* **Por que:** Utilizada para o catálogo e estoque de itens especiais do jogo. Como o estoque só precisa ser iterado em uma única direção para visualização, sorteios ou distribuição nas corridas, a lista simples economiza memória ao omitir o ponteiro "anterior".

---
## Como Compilar e Executar
O projeto adota uma arquitetura modularizada, separando o código-fonte (`src/`) das assinaturas e cabeçalhos (`include/`). A automação da compilação é garantida pelo `Makefile`.

### Pré-requisitos
* Compilador GCC
* Ferramenta GNU Make

### Compilação e Execução
Na raiz do projeto, execute o comando de compilação:

```bash
make