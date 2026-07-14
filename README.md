# Mario Kart: Central Digital do Grande Prêmio

## Sobre o Projeto
O Reino Cogumelo está enfrentando uma crise sem precedentes em seus campeonatos devido a interferências digitais causadas pelo Bowser. Para evitar o colapso das corridas, este projeto implementa a nova **Central Digital do Grande Prêmio**, o sistema oficial da Federação Mushroom Kart Racing (FMKR). 

O sistema foi projetado sob a premissa de execução em hardware embarcado nos karts, exigindo gerenciamento rigoroso de memória e estruturas de dados de alto desempenho. 

Este projeto é o Trabalho Final da disciplina de Algoritmos e Estruturas de Dados I.

## Autores
* Lúcio Vagner Carvalho
* Carlos Henrique Leite Bianchin

## Módulos do Sistema
O ecossistema da aplicação é dividido em seis módulos integrados para resolver as falhas de organização do campeonato:

* **Módulo 1 - Central de Corridas:** Gerencia as corridas pendentes, ordenando-as automaticamente de acordo com o Nível de Perigo (prioridade) e ordem de cadastro.
* **Módulo 2 - Registro Oficial de Pilotos:** Permite o cadastro, atualização e busca rápida de pilotos no banco de dados da Federação.
* **Módulo 3 - Arsenal de Itens:** Controla rigidamente o estoque global da Federação, distribuindo itens nas corridas e removendo os que foram consumidos.
* **Módulo 4 - Histórico do Grande Prêmio:** Armazena os resultados das corridas finalizadas para gerar estatísticas e rankings históricos do campeonato.
* **Módulo 5 - Oficina do Professor E. Gadd:** Fila de manutenção de veículos acidentados, tratando reparos de Karts Destruídos com prioridade máxima sobre os Karts Danificados.
* **Módulo 6 - Sistema de Campeonato:** Calcula a pontuação e processa a classificação oficial da temporada, definindo o campeão.

> **Nota:** O sistema automatiza as corridas, dividindo o processo entre a Fase de Preparação do evento e a Fase de Simulação dos resultados baseada no desempenho, itens e sorte.

## Estruturas de Dados Utilizadas
Para atender aos requisitos técnicos e garantir a estabilidade do sistema, foram implementadas as seguintes estruturas de dados (selecionadas dentre as requisitadas pela especificação):

* **[x] Listas Encadeadas (Simples/Duplas)** -> Usadas no Histórico do Grande Prêmio.
* **[x] Filas** -> Usadas na Oficina do Professor E. Gadd.
* **[x] Heaps** -> Usados na Central de Corridas para gerenciar prioridades.
* **[x] Árvores Binárias Balanceadas** -> Usadas no Registro de Pilotos para busca otimizada.

## Como Compilar e Executar
O projeto adota uma arquitetura modularizada, separando o código-fonte (`src/`) das assinaturas e cabeçalhos (`include/`). A automação da compilação é garantida pelo `Makefile`.

### Pré-requisitos
* Compilador GCC
* Ferramenta GNU Make

### Compilação e Execução
Na raiz do projeto, execute o comando de compilação:

```bash
make