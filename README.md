<div align="center">
  
# 🏁 Mario Kart: Grande Prêmio do Reino Cogumelo

### *Simulador de Corridas, Campeonato e Oficina em C*

[![C](https://img.shields.io/badge/C-11%20%2F%2099-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.kernel.org/)
[![GCC](https://img.shields.io/badge/GCC-Compiler-fff?style=for-the-badge&logo=gnu&logoColor=black)](https://gcc.gnu.org/)
[![UFPel](https://img.shields.io/badge/UFPel-CDTec-blue?style=for-the-badge)](https://www.ufpel.edu.br/)

</div>

---

## 📖 Sobre o Projeto

O **Mario Kart: Grande Prêmio do Reino Cogumelo** é um simulador de corridas completo desenvolvido em **C**. O sistema gerencia karts, pilotos, pistas, itens especiais clássicos e mecânicas completas de corrida — incluindo acidentes, ultrapassagens, sistema de oficina com fila de reparo, histórico de rivalidades e classificação de campeonato em tempo real.

O projeto foi desenvolvido para a disciplina de **Algoritmos e Estruturas de Dados** do curso de Engenharia de Computação da **Universidade Federal de Pelotas (UFPel)**.

### 👥 Autores
* **Lúcio Vagner Carvalho Souza**
* **Carlos Henrique Leite Bianchin**

---

## 🎮 Funcionalidades do Sistema

* **👥 Gestão de Pilotos:** Cadastro, visualização bidirecional e desativação/reativação de pilotos.
* **🏎️ Oficina Mecânica:**
  * Karts danificados entram em uma **fila sequencial (FIFO)**.
  * Karts com perda total entram em uma **fila de prioridade (Heap)** para reparos emergenciais.
* **📦 Itens Especiais:** Distribuição, estoque e uso de itens icônicos (Casco Verde, Casco Vermelho, Banana, Raio, Estrela, Cogumelo, etc.).
* **🏁 Pistas e Corridas:** Agendamento de pistas ordenadas por prioridade/dificuldade.
* **🎲 Simulação de Corrida:** Cálculo dinâmico volta a volta com ultrapassagens, eventos climáticos, uso de itens, batidas e pontuação.
* **🏆 Campeonato Integrado:** Tabela de pontuação dinâmica e balanceada a cada rodada.
* **📜 Histórico e Rivalidades:** Registro histórico de temporadas passadas e cálculo das maiores rivalidades entre pilotos.
* **💻 Portabilidade:** Suporte a terminais Linux e Windows com comandos ANSI e limpeza de tela multiplataforma.

---

## ⚙️ Estruturas de Dados Utilizadas

O projeto faz uso intensivo de estruturas de dados clássicas, selecionadas de acordo com as necessidades de complexidade e performance de cada módulo:

| Estrutura | Localização | Complexidade | Finalidade Principal |
| :--- | :--- | :--- | :--- |
| **Árvore AVL (ABB Balanceada)** | `camp.h` (`struct camp`) | $O(\log n)$ | Ranking e pontuação dinâmica do campeonato, garantindo buscas e atualizações eficientes |
| **Fila de Prioridade (Heap)** | `corridas.h` (`HeapCorridas`), `oficina.h` (`HeapOficina`) | $O(\log n)$ inserção/remoção | Ordenação prioritária das corridas e atendimento emergencial a karts com perda total |
| **Fila FIFO** | `oficina.h` (`FilaOficina`, `Nofila`) | $O(1)$ | Conserto sequencial de karts com danos leves/médios ("primeiro que chega, primeiro atendido") |
| **Lista Duplamente Encadeada** | `pilotos.h` (`NoPiloto`), `historico.h` (`Historico`) | $O(1)$ remoção local | Navegação bidirecional no menu de pilotos e linha do tempo de temporadas no histórico |
| **Lista Simplesmente Encadeada** | `itens.h` (`struct item`) | $O(n)$ / $O(1)$ | Catálogo de itens e estoque com menor overhead de memória |

---

## 📂 Estrutura do Repositório

```text
Mario-Kart-Grande-Pr-mio-do-Reino-Cogumelo/
├── include/              # Cabeçalhos (.h) com definições de tipos e protótipos
│   ├── camp.h            # Campeonato e árvore AVL
│   ├── corridas.h        # Gestão e heap de pistas
│   ├── historico.h       # Histórico de temporadas e rivalidades
│   ├── itens.h           # Estruturas e manipulação de itens
│   ├── karts.h           # Definição e atributos dos karts
│   ├── menu.h            # Interfaces e menus do usuário
│   ├── oficina.h         # Filas FIFO e Heap da oficina
│   ├── pilotos.h         # Gestão de pilotos (lista duplamente encadeada)
│   ├── portabilidade.h   # Compatibilidade Linux/Windows e cores ANSI
│   └── simulacao.h       # Motor de simulação das corridas
├── src/                  # Implementação (.c) de cada módulo
│   ├── camp.c
│   ├── corridas.c
│   ├── historico.c
│   ├── itens.c
│   ├── karts.c
│   ├── main.c            # Ponto de entrada da aplicação
│   ├── menu.c
│   ├── oficina.c
│   ├── pilotos.c
│   ├── portabilidade.c
│   └── simulacao.c
├── Makefile              # Automação de compilação
├── .gitignore            # Regras para ignorar binários e arquivos temporários
└── README.md             # Documentação principal do projeto
```

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
* Compilador **GCC** instalado (`gcc --version`)
* Ferramenta **GNU Make** (`make --version`)

### 1. Compilar o projeto
Na raiz do repositório, execute:
```bash
make
```
O executável `mario_kart_gp` será gerado.

### 2. Executar
Você pode rodar diretamente via terminal:
```bash
./mario_kart_gp
```
Ou através do atalho configurado no `Makefile`:
```bash
make run
```

### 3. Limpar arquivos de compilação
Para remover os arquivos objeto (`obj/`) e os binários gerados:
```bash
make clean
```

---

## 📄 Licença

Este projeto foi desenvolvido para fins educacionais e acadêmicos na Universidade Federal de Pelotas (UFPel).
Todos os direitos relativos à marca e universo *Mario Kart* pertencem à **Nintendo**.
