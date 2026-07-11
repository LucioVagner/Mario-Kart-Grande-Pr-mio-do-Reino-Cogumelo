# [cite_start]Mario Kart: Central Digital do Grande Prêmio [cite: 2, 8]

## 🍄 Sobre o Projeto
[cite_start]O Reino Cogumelo está enfrentando uma crise sem precedentes em seus campeonatos devido a interferências digitais causadas pelo Bowser[cite: 3, 5]. [cite_start]Para evitar o colapso das corridas, este projeto implementa a nova **Central Digital do Grande Prêmio**, o sistema oficial da Federação Mushroom Kart Racing (FMKR)[cite: 7, 8]. 

[cite_start]O sistema foi projetado sob a premissa de execução em hardware embarcado nos karts, exigindo gerenciamento rigoroso de memória e estruturas de dados de alto desempenho[cite: 9, 10].

[cite_start]Este projeto é o Trabalho Final da disciplina de Algoritmos e Estruturas de Dados I[cite: 1, 2].

## 👥 Autores
* Lúcio Vagner Carvalho
* Carlos Henrique Leite Bianchin

## ⚙️ Módulos do Sistema
[cite_start]O ecossistema da aplicação é dividido em seis módulos integrados para resolver as falhas de organização do campeonato[cite: 95, 96, 97]:

* [cite_start]**Módulo 1 - Central de Corridas:** Gerencia as corridas pendentes, ordenando-as automaticamente de acordo com o Nível de Perigo (prioridade) e ordem de cadastro[cite: 98, 99, 102, 104, 105].
* [cite_start]**Módulo 2 - Registro Oficial de Pilotos:** Permite o cadastro, atualização e busca rápida de pilotos no banco de dados da Federação[cite: 115, 116, 118, 121, 122].
* [cite_start]**Módulo 3 - Arsenal de Itens:** Controla rigidamente o estoque global da Federação, distribuindo itens nas corridas e removendo os que foram consumidos[cite: 130, 131, 138, 140].
* [cite_start]**Módulo 4 - Histórico do Grande Prêmio:** Armazena os resultados das corridas finalizadas para gerar estatísticas e rankings históricos do campeonato[cite: 152, 154, 157].
* [cite_start]**Módulo 5 - Oficina do Professor E. Gadd:** Fila de manutenção de veículos acidentados, tratando reparos de Karts Destruídos com prioridade máxima sobre os Karts Danificados[cite: 169, 170, 172, 180, 181, 183].
* [cite_start]**Módulo 6 - Sistema de Campeonato:** Calcula a pontuação e processa a classificação oficial da temporada, definindo o campeão[cite: 186, 187, 189, 194].

[cite_start]*(O sistema automatiza as corridas, dividindo o processo entre a Fase de Preparação do evento e a Fase de Simulação dos resultados baseada no desempenho, itens e sorte [cite: 203, 204, 205, 212, 226])*

## 🛠️ Estruturas de Dados Utilizadas
[cite_start]Para atender aos requisitos técnicos e garantir a estabilidade do sistema [cite: 266, 273][cite_start], foram implementadas as seguintes estruturas de dados (selecionadas dentre as requisitadas pela especificação [cite: 274]):

> **Nota da dupla:** *[Lúcio e Carlos, preencham aqui quais das estruturas abaixo vocês de fato implementaram para os módulos. [cite_start]Lembrem-se que o professor exige pelo menos 4 delas [cite: 274]]*

* [cite_start][ ] **Listas Encadeadas (Simples/Duplas)** [cite: 275] -> *(Ex: Usadas no Histórico)*
* [cite_start][ ] **Filas** [cite: 276] -> *(Ex: Usadas na Oficina)*
* [cite_start][ ] **Pilhas** [cite: 277] -> *(Ex: Usadas no Arsenal de Itens)*
* [cite_start][ ] **Heaps** [cite: 278] -> *(Ex: Usados na Central de Corridas para gerenciar prioridades)*
* [cite_start][ ] **Árvores Binárias Balanceadas** [cite: 279] -> *(Ex: Usadas no Registro de Pilotos para busca otimizada)*

## 🚀 Como Compilar e Executar

[cite_start]O projeto adota uma arquitetura modularizada, separando o código-fonte (`src/`) das assinaturas e cabeçalhos (`include/`)[cite: 270, 271]. [cite_start]A automação da compilação é garantida pelo `Makefile`[cite: 269].

### Pré-requisitos
* Compilador GCC.
* Ferramenta GNU Make.

### Compilação
Na raiz do projeto, execute o comando:
```bash
make