#include "artista.h"
#include "album.h"
#include "musica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artistas{
    char nome_artista[20];
    char estilo_musical[20];
    int num_albums;
    Albums *albums;
    int cor;// 1 é vermelho e 0 é preto
    int raiz;
    struct artistas *esq;
    struct artistas *dir;

    //ponteiro para os albuns  (endereço da árvore vermelho e preta)
};

void cadastrarArtista(Artistas** raiz) {
    Artistas *no = (Artistas*)malloc(sizeof(Artistas));

	printf("\n\nDiga o estilo musical: ");
	scanf(" %[^\n]",no->estilo_musical);
	printf("Diga o nome do artista: ");
	scanf(" %[^\n]",no->nome_artista);
	no->num_albums = 0;

    if (*raiz == NULL){
        no->cor = 0;
        no->raiz = 1;
    }else{
        no->cor = 1;
        no->raiz = 0;
    }
    //porque preciso por paretenses?
	no->dir = NULL;
	no->esq = NULL;
	no->albums = NULL;

    int verifica = insesrir_A(raiz, no);
    if (verifica != 0)
        printf("Artista inserida com sucesso!\n");
    else{
        printf("Erro ao inserir o artista. ja existe.\n");
        free(no);//lembrar de dar free se existir um igual
    }
}

int insesrir_A(Artistas **raiz,Artistas *no){
	int inseriu = 1;

	if(*raiz == NULL)
		*raiz = no;        
    
	else if(strcmp(no->nome_artista,(*raiz)->nome_artista)<0)
		inseriu = insesrir_A((&(*raiz)->esq),no);
        // inseriu = insesrir_A(&((*raiz)->esq), no);


	else if(strcmp(no->nome_artista,(*raiz)->nome_artista)>0)
		inseriu = insesrir_A((&(*raiz)->dir),no);
        //inseriu = insesrir_A(&((*raiz)->dir), no);


	else if(strcmp(no->nome_artista,(*raiz)->nome_artista)==0)
		inseriu = 0;
    

    balanceamento(raiz);
	return inseriu;
	
}

// void balanceamento(Artistas **no){

//     if (*no == NULL) {
//         return;
//     }

//     else if((*no)->dir != NULL && (*no)->dir->cor == 1)// SE e vermelho
//         rotacaoEsquerda_A(no);

//     else if((*no)->esq != NULL && (*no)->dir->cor == 1 && (*no)->esq->esq->cor == 1 )
//         rotacaoDireita_A(no);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

//     else if((*no)->esq != NULL && (*no)->esq->cor == 1 && (*no)->dir != NULL && (*no)->dir->cor == 1){
//         TrocaCor(no);
//     }
// }

void balanceamento(Artistas **raiz) {
    if (*raiz == NULL) {
        return;
    }

    // Caso 1: O nó pai é vermelho
    if ((*raiz)->esq != NULL && (*raiz)->esq->cor == 1) {
        // Caso 1.1: O tio também é vermelho
        if ((*raiz)->dir != NULL && (*raiz)->dir->cor == 1) {
            TrocaCor(raiz);  // Troca cor do pai e tio para preto
            (*raiz)->esq->cor = 0;  // Atualiza cor do avô para vermelho
        } else {
            // Caso 1.2: O tio é preto ou nulo
            if ((*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == 1) {
                rotacaoDireita_A(raiz);
                TrocaCor(raiz);  // Troca cor do pai e avô
            } else if ((*raiz)->esq->dir != NULL && (*raiz)->esq->dir->cor == 1) {
                rotacaoEsquerda_A(&((*raiz)->esq));
                rotacaoDireita_A(raiz);
                TrocaCor(raiz);  // Troca cor do pai e avô
            }
        }
    }

    // Caso 2: O nó direito é vermelho
    if ((*raiz)->dir != NULL && (*raiz)->dir->cor == 1) {
        // Caso 2.1: O tio também é vermelho
        if ((*raiz)->esq != NULL && (*raiz)->esq->cor == 1) {
            TrocaCor(raiz);  // Troca cor do pai e tio para preto
            (*raiz)->dir->cor = 0;  // Atualiza cor do avô para vermelho
        } else {
            // Caso 2.2: O tio é preto ou nulo
            if ((*raiz)->dir->dir != NULL && (*raiz)->dir->dir->cor == 1) {
                rotacaoEsquerda_A(raiz);
                TrocaCor(raiz);  // Troca cor do pai e avô
            } else if ((*raiz)->dir->esq != NULL && (*raiz)->dir->esq->cor == 1) {
                rotacaoDireita_A(&((*raiz)->dir));
                rotacaoEsquerda_A(raiz);
                TrocaCor(raiz);  // Troca cor do pai e avô
            }
        }
    }
}


void TrocaCor(Artistas **raiz){
    (*raiz)->cor = 1;
    if((*raiz)->raiz == 1)
        (*raiz)->cor = 0;
    (*raiz)->dir->cor = 0;
    (*raiz)->esq->cor = 0;
}

void rotacaoDireita_A(Artistas **raiz){
    Artistas *aux; 
	aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir =  *raiz;
	aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    if((*raiz)->raiz == 1){
        (*raiz)->raiz = 0;
        aux->raiz = 1;
        aux->cor = 0;
    }
    *raiz = aux;
}

void rotacaoEsquerda_A(Artistas **raiz){
    Artistas *aux;
	aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
	aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    if((*raiz)->raiz == 1){
        (*raiz)->raiz = 0;
        aux->raiz = 1;
        aux->cor = 0;
    }
    *raiz = aux;
}

Artistas *busca_Artista(Artistas* raiz, char nome[20]) {
    Artistas *aux;
    aux = NULL;
    if (raiz != NULL) {
        int comparacao = strcmp(nome, raiz->nome_artista);

        if (comparacao == 0) {
            aux = raiz;
        } else if (comparacao < 0) {
            aux = busca_Artista(raiz->esq, nome);
        } else {
            aux = busca_Artista(raiz->dir, nome);
        }
    }
    return aux;
}


void mostrarartista(Artistas *pessoas){
	if (pessoas != NULL){
        printf("\n\nNome do artista: %s", pessoas->nome_artista);
	    printf("\nNome do estilo musical: %s", pessoas->estilo_musical);
	    printf("\nNumero de albums: %d", pessoas->num_albums);
	    printf("\n Cor do NO(lembrar de tirar isso ao enviar): %d", pessoas->cor);
    }else
        printf("Artista nao encontrado!!!");
}


int remover_A(Artistas **raiz, char nome[20]) {
    if (*raiz != NULL) {

        int comparacao = strcmp(nome, (*raiz)->nome_artista);

        if (comparacao < 0) {
            return remover_A(&((*raiz)->esq), nome);
        } else if (comparacao > 0) {
            return remover_A(&((*raiz)->dir), nome);
        } else {

            if ((*raiz)->dir == NULL && (*raiz)->esq == NULL) {
                liberaAlbums((*raiz)->albums);
                free(*raiz);
                (*raiz) = NULL;
            } else if ((*raiz)->esq == NULL && (*raiz)->dir != NULL) {
                Artistas *temp = (*raiz)->dir;
                if ((*raiz)->raiz == 1) {
                    temp->cor = 0;
                }
                liberaAlbums((*raiz)->albums);
                free(*raiz);
                *raiz = temp;
            } else if ((*raiz)->dir == NULL && (*raiz)->esq != NULL) {
                Artistas *temp = (*raiz)->esq;
                liberaAlbums((*raiz)->albums);
                free(*raiz);
                *raiz = temp;
            } else {
                Artistas *temp = menorValor((*raiz)->dir);

                strcpy((*raiz)->nome_artista, temp->nome_artista);

                return remover_A(&((*raiz)->dir), temp->nome_artista);
            }

            balanceamento(raiz);
            return 1;
        }
    }

    return 0; // Indica que o nó não foi encontrado
}

Artistas* menorValor(Artistas* raiz) {
    Artistas* atual = raiz;

    // Percorre a árvore até encontrar o nó mais à esquerda
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

void liberaArtista(Artistas *a){
	if (a != NULL){
		liberaArtista(a->esq);
		liberaArtista(a->dir);
		liberaAlbums(a->albums);
		free(a);
	}
}