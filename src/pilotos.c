#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"
#include "karts.h"
#include "portabilidade.h"

//função de criar a lista de pilotos
NoPiloto* criar_lista_pilotos(){
    return NULL;
}
//cadastrar o piloto que é uma lista encadeada
NoPiloto* cadastrar_piloto (NoPiloto *lista){
    NoPiloto *aux = (NoPiloto*) malloc(sizeof(NoPiloto));

    if(aux == NULL){
        printf(RED"ERRO DE ALOCAÇÃO!"RESET);
        return aux;
    }
    aux->proximo = NULL;
    aux->anterior = NULL;
    getchar();
    
    printf("Digite o nome do Piloto: ");
    fgets(aux->piloto.nome, sizeof(aux->piloto.nome), stdin);
    aux->piloto.nome[strcspn(aux->piloto.nome, "\n")] = 0;

    printf("\n------------------------------------------\n\n");
    printf("Selecione a categoria do piloto.\n");
    printf(BLUE BOLD"[1] para leve.\n[2] para medio.\n[3] para pesado.\n"RESET);
    while (scanf("%d", &aux->piloto.categoria) != 1 || aux->piloto.categoria < 1 || aux->piloto.categoria >3){
        while (getchar() != '\n');
        printf(RED"ERRO! DIGITE UMA ENTRADA VALIDA\n"RESET);

    }
    aux->piloto.trofeus = 0;
    aux->piloto.status = 0;
    aux->piloto.item = -1;
    aux->piloto.kart = select_kart(); //vai selecionar o tipo de kart do piloto e depois pedir o nome
    
    getchar();
    printf("\nDigite o nome do seu kart: ");
    fgets(aux->piloto.kart.nome, sizeof(aux->piloto.kart.nome), stdin);
    aux->piloto.kart.nome[strcspn(aux->piloto.kart.nome, "\n")] = 0;

    if(lista == NULL){
        return aux;
    }
    
    NoPiloto *novo = lista; //cria outra variavel pra ir pro final da lista e inserir no final pra fazer uma lifo
    while (novo->proximo != NULL){
        novo = novo->proximo;
    }
    novo->proximo = aux;   //o proximo da lista que era nulo vai receber o valor atual do aux(que acabou de ser inserido)
    aux->anterior = novo; // e o anterior do aux que era nulo vai receber o penultimo item da lista

    return lista; //como a lista ta diretamente conectada ao novo e ao aux vai so retornar a lista normalmente
}
//inicialmente era pra listar todos os pilotos mas fiz pra listar so um piloto dps
void listar_pilotos(NoPiloto *lista){
    NoPiloto *aux = lista; //vai receber o valor atual da lista quando a função for chamada e imprimir, não precisa do aux, talvez retirar se for o caso

    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return;
    }


        printf("\nNome do piloto: "YELLOW"%s\n"RESET, aux->piloto.nome);
        printf("Categoria do piloto: ");
        switch(aux->piloto.categoria){
            case 1:
                printf(GREEN BOLD"Leve.\n"RESET);
                break;
            case 2:
                printf(YELLOW BOLD"Medio.\n"RESET);
                break;
            case 3:
                printf(RED BOLD"Pesado.\n"RESET);
                break;
        }
        printf("Quantidade de trofeus: "MAGENTA BOLD "%d\n\n"RESET, aux->piloto.trofeus);
        exibir_kart(aux->piloto.kart);

        printf("\nSTATUS DO PILOTO: ");
            switch(aux->piloto.status){
                case 0:
                    printf(GREEN"DISPONIVEL.\n"RESET);
                    break;
                case 1:
                    printf(RED"SUSPENSO.\n"RESET);
                    break;
                case 2:
                    printf(YELLOW "ACIDENTADO.\n"RESET);
                    break;
            }
        }
void listar_pilotos_all(NoPiloto *lista){
    NoPiloto *aux = lista; //vai receber o valor atual da lista quando a função for chamada e imprimir, não precisa do aux, talvez retirar se for o caso

    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return;
    }

    while(aux != NULL){
        printf("---------------------------------------------\n");
        printf("Nome do piloto: "YELLOW BOLD"%s\n"RESET, aux->piloto.nome);
        printf("Categoria do piloto: ");
        switch(aux->piloto.categoria){
            case 1:
                printf(GREEN BOLD"Leve.\n"RESET);
                break;
            case 2:
                printf(YELLOW BOLD"Medio.\n"RESET);
                break;
            case 3:
                printf(RED BOLD"Pesado.\n"RESET);
                break;
        }

        printf("Quantidade de trofeus: "MAGENTA BOLD"%d\n\n"RESET, aux->piloto.trofeus);
        exibir_kart(aux->piloto.kart);

        printf("\nSTATUS DO PILOTO: ");
            switch(aux->piloto.status){
                case 0:
                    printf(GREEN"DISPONIVEL.\n"RESET);
                    break;
                case 1:
                    printf(RED"SUSPENSO.\n"RESET);
                    break;
                case 2:
                    printf(YELLOW"ACIDENTADO.\n"RESET);
                    break;
            }
        printf("---------------------------------------------\n");
        aux = aux->proximo;
        }
    }
//função de remoção dos pilotos
NoPiloto* remover_piloto(NoPiloto *lista, NoPiloto **removidos){
    NoPiloto* aux =  lista;
    int num;
    char nome[50];
    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return lista;
    }
    NoPiloto *fimremovidos = *removidos; //lista dos removidos da lista(suspensos)
    if(fimremovidos != NULL){
        while (fimremovidos->proximo != NULL){
            fimremovidos = fimremovidos->proximo; //avança pro final pra a possivel proxima inserção nao ter que avançar em outra função
        }
    }
    
    printf("[1] Remover piloto "BOLD YELLOW"ACIDENTADO"RESET".\t[2] "RED"EXCLUIR"RESET" piloto da sua escolha.\n");
    while(scanf("%d", &num) != 1 || num < 1 || num > 2){
        limpar_buffer();
        printf(RED"ERRO! DIGITE UMA ENTRADA VÁLIDA.\n"RESET);
    }
    if(num == 1){
        while (aux != NULL){
            if(aux->piloto.status == 1){    //se tiver danificado ele cria uma variavel auxiliar extra pra aquele ponteiro especifico
                NoPiloto *remover = aux; 
                aux = aux->proximo; //avança o aux pra dar o free no remover


                if(remover->anterior != NULL){
                    remover->anterior->proximo = remover->proximo; //se tiver algo antes ele desconecta
                } else{
                    lista = remover->proximo;
                    if(lista != NULL){
                        lista->anterior = NULL;
                    }
                }

                if (remover->proximo != NULL){
                    remover->proximo->anterior = remover->anterior; //se tiver algo depois ele desconecta 
                }   
                remover->anterior = fimremovidos; //
                remover->proximo = NULL;

                if(fimremovidos != NULL){
                    fimremovidos->proximo = remover; //fim removidos proximo ja era null?
                }else{
                    *removidos = remover; 
                }
                fimremovidos = remover;
                printf("Piloto "RED"removido"RESET".\n");

            } else{
                aux = aux->proximo;
            }
        }
    }else{
        listar_pilotos_all(lista);
        limpar_buffer();
        printf("Digite o nome do piloto que deseja excluir: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';
        while(aux != NULL){
            if(strcmp(aux->piloto.nome, nome) == 0){
                NoPiloto *remover = aux;
                aux = aux->proximo;

                if(remover->anterior != NULL){
                    remover->anterior->proximo = remover->proximo;
                }else {
                    lista = remover->proximo;
                    if(lista != NULL){
                        lista->anterior = NULL;
                    }
                }
                

                if(remover->proximo != NULL){
                    remover->proximo->anterior = remover->anterior;
                }
                free(remover);
                printf("Piloto "RED"removido"RESET".\n");
                return lista;
            }else{
                aux = aux->proximo;
            }
        }
        printf("NENHUM PILOTO COM ESSE NOME ENCONTRADO.\n");
        
    }

    return lista;
}
//funcao que quer saber o nome do piloto para listar, so o basico
void listar_piloto_nome(NoPiloto* lista, char name[50]){
    NoPiloto *aux = lista;

    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return;
    }

    while (aux != NULL){
        if(strcmp(aux->piloto.nome, name) == 0){
            listar_pilotos(aux);
            return;
        }else{
            aux = aux->proximo;
        }
    }
    printf("Piloto não encontrado.\n");

    return;
}
//funcao caso o player queira atualizar algum atributo do piloto, o new trophy e new status sao entradas que vao ser pedidas na main apos a corrida
void att_piloto(NoPiloto **lista, char name[50]){
    NoPiloto *aux = *lista;
    int choose;

    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return;
    }

    while (aux != NULL){

        if(strcmp(aux->piloto.nome, name) == 0){
               
            printf("[1] para atualizar o tipo do kart.\n[2] para atualizar a categoria.\n");
            while(scanf("%d", &choose) != 1 || choose < 1 || choose > 2){
                getchar();
                printf(RED"ERRO! DIGITE UMA ENTRADA VÁLIDA.\n"RESET);
            }
              switch (choose){
                    case 1:{
                        Kart kart;
                        limpar_buffer();
                        kart = select_kart();
                        aux->piloto.kart = kart;
                        printf("Kart atualizado com sucesso.\n");

                   }
                    
                   case 2:{
                    int newcat;
                    printf("Digite a nova categoria do piloto: ");
                    while (scanf("%d", &newcat) != 1 || newcat < 1 || newcat >3){
                    while (getchar() != '\n');
                    printf(RED"ERRO! DIGITE UMA ENTRADA VALIDA\n"RESET);
                    }
                    aux->piloto.categoria = newcat;
                    break;
                   }
                   default: 
                      printf(RED"Opção Inválida."RESET);
                      break;
                }
            

            return; 
        }else{
            aux = aux->proximo;
        }
    }
    printf("Piloto não encontrado.\n");


}
//lista dos pilotos excluidos da lista principal, so o basico tbm
void listar_suspensos (NoPiloto *removidos){
    NoPiloto* aux = removidos;


    printf(RED "================== PILOTOS SUSPENSOS ==================\n\n"RESET);
    if(aux == NULL){
        printf("Não existe pilotos suspenso.\n");
        return;
    }
    while(aux != NULL){

        listar_pilotos(aux);
        aux = aux->proximo;

    }
}
//lista dos pilotos pela categoria
void listar_categoria(NoPiloto *lista){
    NoPiloto *aux = lista;
    int choose;
    int find = 0;
    printf("Escolha a categoria que deseja listar.\n\n[1] "GREEN BOLD"leve"RESET".\n[2] "YELLOW BOLD"medio"RESET".\n[3] "RED BOLD"pesado"RESET".\n");
    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 3){
        getchar();
        printf(RED"ERRO! DIGITE UMA ENTRADA VÁLIDA.\n"RESET);
    }
    while(aux != NULL){
        if(aux->piloto.categoria == choose){
            listar_pilotos(aux);
            find = 1;
        }
        aux = aux->proximo;
 
    }
    if(find == 0){
        printf("\nSEM PILOTOS DESSA CATEGORIA.\n");
    }
    return;
}
//vai conferir o piloto com a maior quantidade de trofeu
void exibir_trofeu(NoPiloto *lista){
    NoPiloto *aux = lista;
    int max;

    if (aux == NULL){
        printf(RED"ERRO! LISTA VAZIA.\n"RESET);
        return;
    }

    max = aux->piloto.trofeus;
    aux = aux->proximo;

    while (aux != NULL){
        if(aux->piloto.trofeus > max){
            max = aux->piloto.trofeus;
        }
        aux = aux->proximo;
    }

    aux = lista;
    while (aux != NULL){
        if(aux->piloto.trofeus == max){
            listar_pilotos(aux);
            return;
        }
        aux = aux->proximo;
    }
}
void liberar_lista_pilotos(NoPiloto *lista){
    NoPiloto *aux;
    while (lista != NULL){
        aux = lista;
        lista = lista->proximo;
        free(aux);
    }
}
// Função auxiliar interna para inserir os dados de forma direta na lista dupla
NoPiloto* inserir_piloto_direto(NoPiloto *lista, char nome[], int categoria, char nome_kart[], int vel, int acel, int controle, int durabil) {
    NoPiloto *aux = (NoPiloto*) malloc(sizeof(NoPiloto));
    if (aux == NULL) {
        return lista;
    }

    // Atributos do piloto
    strcpy(aux->piloto.nome, nome);
    aux->piloto.categoria = categoria;
    aux->piloto.trofeus = 0;
    aux->piloto.status = 0; // Disponível
    aux->piloto.item = -1;

    // Atributos do kart
    strcpy(aux->piloto.kart.nome, nome_kart);
    aux->piloto.kart.vel = vel;
    aux->piloto.kart.acel = acel;
    aux->piloto.kart.controle = controle;
    aux->piloto.kart.durabil = durabil;
    aux->piloto.kart.status = 0; // Operacional
    aux->piloto.kart.damage = 100;

    aux->proximo = NULL;
    aux->anterior = NULL;

    if (lista == NULL) {
        return aux;
    }

    // Caminha até o final da lista para manter a sua lógica de inserção na cauda
    NoPiloto *novo = lista;
    while (novo->proximo != NULL) {
        novo = novo->proximo;
    }
    novo->proximo = aux;
    aux->anterior = novo;

    return lista;
}

// Função principal que gera os três personagens iniciais
NoPiloto* inicializar_pilotos_padrao() {
    NoPiloto *lista = NULL;
    
    // Cadastro automático do Mario, Yoshi e Peach
    lista = inserir_piloto_direto(lista, "Mario", 2, "Standard Kart", 50, 50, 50, 50);
    lista = inserir_piloto_direto(lista, "Yoshi", 1, "Pipe Frame", 70, 40, 60, 30);
    lista = inserir_piloto_direto(lista, "Peach", 2, "Mach 8", 90, 30, 40, 40);
    
    return lista;
}

