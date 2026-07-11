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
        printf("ERRO DE ALOCAÇÃO!");
        return aux;
    }
    aux->proximo = NULL;
    aux->anterior = NULL;
    getchar();
    
    printf("Digite o nome do Piloto: ");
    fgets(aux->piloto.nome, sizeof(aux->piloto.nome), stdin);
    aux->piloto.nome[strcspn(aux->piloto.nome, "\n")] = 0;


    printf("Selecione a categoria do piloto.\n");
    printf("[1] para leve.\n[2] para medio.\n[3] para pesado.\n");
    while (scanf("%d", &aux->piloto.categoria) != 1 || aux->piloto.categoria < 1 || aux->piloto.categoria >3){
        while (getchar() != '\n');
        printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");

    }
    aux->piloto.trofeus = 0;
    aux->piloto.status = 0;
    aux->piloto.item = -1;
    aux->piloto.kart = select_kart(); //vai selecionar o tipo de kart do piloto e depois pedir o nome
    
    getchar();
    printf("Digite o nome do seu kart: ");
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
        printf("ERRO! LISTA VAZIA.\n");
        return;
    }


        printf("Nome do piloto: %s\n", aux->piloto.nome);
        printf("Categoria do piloto: ");
        switch(aux->piloto.categoria){
            case 1:
                printf("Leve.\n");
                break;
            case 2:
                printf("Medio.\n");
                break;
            case 3:
                printf("Pesado.\n");
                break;
        }
        printf("Quantidade de trofeus: %d\n", aux->piloto.trofeus);
        exibir_kart(aux->piloto.kart);

        printf("STATUS DO PILOTO: ");
            switch(aux->piloto.status){
                case 0:
                    printf("DISPONIVEL.\n");
                    break;
                case 1:
                    printf("SUSPENSO.\n");
                    break;
                case 2:
                    printf("ACIDENTADO.\n");
                    break;
            }
        }
void listar_pilotos_all(NoPiloto *lista){
    NoPiloto *aux = lista; //vai receber o valor atual da lista quando a função for chamada e imprimir, não precisa do aux, talvez retirar se for o caso

    if (aux == NULL){
        printf("ERRO! LISTA VAZIA.\n");
        return;
    }

    while(aux != NULL){
        printf("---------------------------------------------\n");
        printf("Nome do piloto: %s\n", aux->piloto.nome);
        printf("Categoria do piloto: ");
        switch(aux->piloto.categoria){
            case 1:
                printf("Leve.\n");
                break;
            case 2:
                printf("Medio.\n");
                break;
            case 3:
                printf("Pesado.\n");
                break;
        }

        printf("Quantidade de trofeus: %d\n", aux->piloto.trofeus);
        exibir_kart(aux->piloto.kart);

        printf("STATUS DO PILOTO: ");
            switch(aux->piloto.status){
                case 0:
                    printf("DISPONIVEL.\n");
                    break;
                case 1:
                    printf("SUSPENSO.\n");
                    break;
                case 2:
                    printf("ACIDENTADO.\n");
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
        printf("ERRO!! LISTA VAZIA.\n");
        return lista;
    }
    NoPiloto *fimremovidos = *removidos; //lista dos removidos da lista(suspensos)
    if(fimremovidos != NULL){
        while (fimremovidos->proximo != NULL){
            fimremovidos = fimremovidos->proximo; //avança pro final pra a possivel proxima inserção nao ter que avançar em outra função
        }
    }
    
    printf("[1] Remover piloto ACIDENTADO.\t[2] EXCLUIR piloto da sua escolha.\n");
    while(scanf("%d", &num) != 1 || num < 1 || num > 2){
        limpar_buffer();
        printf("ERRO! DIGITE UMA ENTRADA VÁLIDA.\n");
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
                printf("Piloto removido.\n");

            } else{
                aux = aux->proximo;
            }
        }
    }else{
        listar_pilotos(lista);
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
                printf("Piloto removido.\n");
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
        printf("ERRO! LISTA VAZIA.\n");
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
void att_piloto(NoPiloto **lista, char name[50], int willatt, int new_trophy, int new_status){
    NoPiloto *aux = *lista;
    int choose;

    if (aux == NULL){
        printf("ERRO! LISTA VAZIA.\n");
        return;
    }

    while (aux != NULL){

        if(strcmp(aux->piloto.nome, name) == 0){

            if(willatt == 0){
                aux->piloto.trofeus = new_trophy;
                aux->piloto.status = new_status;
                return; 
            }else if(willatt == 1){ //Se o willatt for 1 ele atualiza manualmente, se for 0 ele atualiza os status automaticamente
                    printf("Escolha o que deseja atualizar: ");
                    printf("[1] para atualizar o nome.\n[2] para atualizar a categoria.\n");
                    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 2){
                        getchar();
                        printf("ERRO! DIGITE UMA ENTRADA VÁLIDA.\n");
                    }

                    switch (choose){
                        case 1:{
                            char newname[50];
                            getchar();
                            printf("Digite o nome novo: ");
                            fgets(newname, sizeof(newname), stdin);
                            newname[strcspn(newname, "\n")] = 0;
                            strcpy(aux->piloto.nome, newname);
                            break;
                        }
                        case 2:{
                            int newcat;
                            printf("Digite a nova categoria do piloto: ");
                            while (scanf("%d", &newcat) != 1 || newcat < 1 || newcat >3){
                                while (getchar() != '\n');
                                printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");
                            }
                            aux->piloto.categoria = newcat;
                            break;
                        }
                        default: 
                            printf("Opção Inválida.");
                            break;
                }
            

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


    printf("================== PILOTOS SUSPENSOS ==================\n\n");
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

    printf("Escolha a categoria que deseja listar.\n\n[1] leve.\n[2] medio.\n[3] pesado.\n");
    while(scanf("%d", &choose) != 1 || choose < 1 || choose > 3){
        getchar();
        printf("ERRO! DIGITE UMA ENTRADA VÁLIDA.\n");
    }
    while(aux != NULL){
        if(aux->piloto.categoria == choose){
            listar_pilotos(aux);
        }
        aux = aux->proximo;
 
    }
    return;
}
//vai conferir o piloto com a maior quantidade de trofeu
void exibir_trofeu(NoPiloto *lista){
    NoPiloto *aux = lista;
    int max;

    if (aux == NULL){
        printf("ERRO! LISTA VAZIA.\n");
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


