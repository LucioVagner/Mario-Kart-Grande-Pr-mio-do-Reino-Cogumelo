#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"
#include "corridas.h"
#include "pilotos.h"
#include "karts.h"
#include "itens.h"
#include "camp.h"

//FUNÇÃO PRA DEFINIR A ALTURA DA ARVORE
int altura(Camp *no){
    if(no == NULL){
        return 0;
    }

    return no->alt;
}

int height(Camp *no){
    int esq, dir;
    if(no == NULL){
        return 0;
    }
    esq = altura(no->esq);
    dir = altura(no->dir);

    if(esq > dir){
        return 1 + esq;
    }else{
        return 1 + dir;
    }
}
//FAZ O BALANCEAMENTO DA ARVORE, SE BALANCE FOR > 1 OU MENOR QUE -1 VAI TER Q ROTACIONAR E AJUSTAR A ARVORE
int balance(Camp *no){
    if(no == NULL){
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}
//AJUSTA A ARVORE PARA A DIREITA
Camp *rotation_dir(Camp *no){
    if(no == NULL){
        return NULL;
    }

    Camp *new = no->esq;

    no->esq = new->dir;
    new->dir = no;

    no->alt = height(no);
    new->alt = height(new);

    return new;

}
// AJUSTA A ARVORE PARA A ESQUERDA
Camp *rotation_esq(Camp *no){
    if(no == NULL){
        return NULL;
    }

    Camp *new = no->dir;

    no->dir = new->esq;
    new->esq = no;

    no->alt = height(no);
    new->alt = height(new);
    return new;
}
//ajusta os nós das arvores
Camp *balancear(Camp *no){
    int i = balance(no); //diferença das alturas

    if(i > 1){ //maior que 1 tem que balancear para a direita
        if(balance(no->esq) < 0){
            no->esq = rotation_esq(no->esq);
        }
        return rotation_dir(no);
    }
    if(i < -1){
        if(balance(no->dir) > 0){
            no->dir = rotation_dir(no->dir);
        }
        return rotation_esq(no);
    }

    return no;
}
//insere elementos na arvore
Camp *inserir(Camp *raiz, char nome[], int pontos){
    if (raiz == NULL){
        Camp *novo = (Camp*) malloc(sizeof(Camp));
        if(novo == NULL){
            printf("ERRO! IMPOSSIVEL ALOCAR MEMORIA.\n");
            return NULL;
        }
        strcpy(novo->nome, nome);
        novo->pontos = pontos;
        novo->alt = 1;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if(pontos <= raiz->pontos){
        raiz->esq = inserir(raiz->esq, nome, pontos);
    }else{
        raiz->dir = inserir(raiz->dir, nome, pontos);
    }
    raiz->alt = height(raiz);

    return balancear(raiz);
}
//imprime o ranking
void ranking(Camp *raiz, int *cont){
    if ((raiz == NULL) || (*cont >= 10)){
        return;
    }
    ranking(raiz->dir, cont);

    (*cont)++;
    printf("%dº lugar\t|Piloto: %s\t %d pontos\n", *cont, raiz->nome, raiz->pontos);

    ranking(raiz->esq, cont);
}

Camp* att_pont(Camp *raiz, char nome[], int pont){
    Camp *pilot = search(raiz, nome);
    int aux;
    if(pilot == NULL){
        return raiz;
    }
    aux = pilot->pontos + pont;

    raiz = remover(raiz, pilot->pontos, pilot->nome);

    raiz = inserir(raiz, nome, aux);


    return raiz;

}

Camp *remover(Camp *raiz, int ponto, char nome[]){
    Camp *temp;
    if(raiz == NULL){
        return NULL;
    }
    if(ponto < raiz->pontos){
        raiz->esq = remover(raiz->esq, ponto, nome);

    }else if(ponto > raiz->pontos){
        raiz->dir = remover(raiz->dir, ponto, nome);

    }else{

        if(strcmp(raiz->nome, nome)== 0){
            if(raiz->esq == NULL){
                temp = raiz->dir;
                free(raiz);
                return temp;
            }
                if(raiz->dir == NULL){
                temp = raiz->esq;
                free(raiz);
                return temp;
            }

            temp = menor(raiz->dir);
            strcpy(raiz->nome, temp->nome);
            raiz->pontos = temp->pontos;
            raiz->dir = remover(raiz->dir, temp->pontos, temp->nome);
    
            

        }else{
            raiz->esq = remover(raiz->esq, ponto, nome);
            raiz->dir = remover(raiz->dir, ponto, nome);
        }
    }
    raiz->alt = height(raiz);
    return balancear(raiz);

    
}

Camp *search(Camp *raiz, char nome[]){
    Camp *aux;

    if(raiz == NULL){
        return NULL;
    }

    if(strcmp(raiz->nome, nome) == 0){
        return raiz;
    }

    aux = search(raiz->esq, nome);
    if(aux != NULL){
        return aux;
    }

    return search(raiz->dir, nome);
}

Camp* menor(Camp *no){
    if(no->esq == NULL){
        return no;
    }
    return menor(no->esq);
}

void champion(Camp *raiz){
    Camp *aux;
    if(raiz == NULL){
        printf("Nenhuma corrida realizada.\n");
        return;
    }
    

    aux = raiz;
    while(aux->dir != NULL){
        aux = aux->dir;
    }

    printf("Campeão da temporada: %s\t|Pontos: %d", aux->nome, aux->pontos);
}

void rank_tot(Camp *raiz, int *cont, int *last_pont){
    if(raiz == NULL){
        return;
    }

    rank_tot(raiz->dir, cont, last_pont);
    (*cont)++;
    if((*last_pont) == raiz->pontos){
        printf("%dº lugar\t|Piloto: %s\t|%d pontos(EMPATE)\n",*cont, raiz->nome, raiz->pontos);
    }else{
         printf("%dº lugar\t|Piloto: %s\t|%d pontos\n",*cont, raiz->nome, raiz->pontos);
    }
    (*last_pont) = raiz->pontos;
   

    rank_tot(raiz->esq, cont, last_pont);
}

void consult_player(Camp *raiz, char nome[], NoPiloto *lista){
    Camp *pilot = search(raiz, nome);
    NoPiloto *aux = lista;
    if(pilot == NULL){
        printf("Piloto não existente.\n");
        return;
    }
    while(aux != NULL){
        if(strcmp(aux->piloto.nome, pilot->nome) == 0){
            listar_pilotos(aux);
            printf("Pontuação: %d", pilot->pontos);
        }
        aux = aux->proximo;
    }



}

int calc_pos(int posicao){
    if(posicao >= 3 && posicao < 6){
        return 12 - posicao;
    }
    if(posicao >= 6 && posicao <= 8){
        return 17 - 2 * posicao;
    }if(posicao > 8){
        return 0;
    }
    return 18 - 3 * posicao;
}