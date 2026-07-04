#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"
#include "karts.h"

NoPiloto* criar_lista_pilotos(){
    return NULL;
}
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
    printf("Digite a velocidade do piloto [1 ... 100]: ");
    while (scanf("%d", &aux->piloto.vel) != 1 || aux->piloto.vel < 1 || aux->piloto.vel > 100){
        while (getchar() != '\n');
        printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");
    }
    aux->piloto.trofeus = 0;
    aux->piloto.status = 0;
    aux->piloto.kart = select_kart();
    
    getchar();
    printf("Digite o nome do seu kart: ");
    fgets(aux->piloto.kart.nome, sizeof(aux->piloto.kart.nome), stdin);
    aux->piloto.kart.nome[strcspn(aux->piloto.kart.nome, "\n")] = 0;

    if(lista == NULL){
        return aux;
    }
    
    NoPiloto *novo = lista;
    while (novo->proximo != NULL){
        novo = novo->proximo;
    }
    novo->proximo = aux;
    aux->anterior = novo;

    return lista;
}
void listar_pilotos(NoPiloto *lista){
    NoPiloto *aux = lista;


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

        printf("Velocidade: %d\n", aux->piloto.vel);
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
        
NoPiloto* remover_piloto(NoPiloto *lista, NoPiloto **removidos){
    NoPiloto* aux =  lista;

    if (aux == NULL){
        printf("ERRO!! LISTA VAZIA.\n");
        return lista;
    }
    NoPiloto *fimremovidos = *removidos;
    if(fimremovidos != NULL){
        while (fimremovidos->proximo != NULL){
            fimremovidos = fimremovidos->proximo;
        }
    }
    

    while (aux != NULL){
        if(aux->piloto.status == 1){
            NoPiloto *remover = aux;
            aux = aux->proximo;


            if(remover->anterior != NULL){
                remover->anterior->proximo = remover->proximo;
            } else{
                lista = remover->proximo;
            }

            if (remover->proximo != NULL){
                remover->proximo->anterior = remover->anterior;
            }   
            remover->anterior = fimremovidos;
            remover->proximo = NULL;

            if(fimremovidos != NULL){
                fimremovidos->proximo = remover;
            }else{
                *removidos = remover;
            }
            fimremovidos = remover;
            printf("Piloto removido.\n");

        } else{
            aux = aux->proximo;
        }
    }

    return lista;
}

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

void att_piloto(NoPiloto **lista, char name[50], int willatt, int new_trophy, int new_status){
    NoPiloto *aux = *lista;
    int choose;

    if (aux == NULL){
        printf("ERRO! LISTA VAZIA.\n");
        return;
    }

    while (aux != NULL){

        if(strcmp(aux->piloto.nome, name) == 0){
            if(willatt == 1){ //Se o willatt for 1 ele atualiza manualmente, se for 0 ele atualiza os status automaticamente
                printf("Escolha o que deseja atualizar: ");
                printf("[1] para atualizar o nome.\n[2] para atualizar a categoria.\n[3] para atualizar a velocidade.\n");
                while(scanf("%d", &choose) != 1 || choose < 1 || choose > 3){
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
                    case 3:{
                        int newvel;
                        printf("Digite a nova velocidade do piloto: ");
                        while (scanf("%d", &newvel) != 1 || newvel < 1 || newvel > 100){
                            while (getchar() != '\n');
                            printf("ERRO! DIGITE UMA ENTRADA VALIDA\n");
                    
                        }
                        aux->piloto.vel = newvel;
                        break;
                    }
                    default: 
                        printf("Opção Inválida.");
                        break;
                }
            }else if(willatt == 0){
                aux->piloto.trofeus = new_trophy;
                aux->piloto.status = new_status;
            }
            return; 

        }else{
            aux = aux->proximo;
        }
    }
    printf("Piloto não encontrado.\n");


}

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
        }
        aux = aux->proximo;
    }
}