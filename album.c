    #include "artista.h"
    #include "album.h"
    #include "musica.h"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    //Cada álbum deve ter, o título, o ano de lançamento, a quantidade de músicas e as Músicas (endereço lista ordenada). P
    struct albums{
        char titulo_album[20];
        int ano_lancamento;
        int qnt_musicas;
        Musicas *musicas;
        int cor;
        int raiz;
        struct albums *esq;
        struct albums *dir;
    };


    int cadastrarBum(Albums ** raiz) {
        Albums *no = (Albums*)malloc(sizeof(Albums));

        printf("\n\nDiga o titulo do album: ");
        scanf(" %[^\n]",no->titulo_album);
        printf("Diga o ano de lancamento: ");
        scanf("%d",&no->ano_lancamento);
        no->qnt_musicas = 0;
        if (*raiz == NULL){
            no->cor = 0;
            no->raiz = 1;
        }else{
            no->cor = 1;
            no->raiz = 0;
        }
        no->dir = NULL;
        no->esq = NULL;
        no->musicas = NULL;

        int verifica = insesrir_BUM(raiz, no);

        if (verifica != 0)
            printf("Album inserida com sucesso!\n");
        else{
            printf("Erro ao inserir a Abum. dados ja existes.\n");
            free(no);//lembrar de dar free se existir um igual
        }
        return verifica;
    }

    int insesrir_BUM(Albums **raiz,Albums *no){
        int inseriu = 1;

        if(*raiz == NULL)
            *raiz = no;        

        else if(strcmp(no->titulo_album,(*raiz)->titulo_album)<0)
            inseriu = insesrir_BUM((&(*raiz)->esq),no);

        else if(strcmp(no->titulo_album,(*raiz)->titulo_album)>0)
            inseriu = insesrir_BUM((&(*raiz)->dir),no);

        else if(strcmp(no->titulo_album,(*raiz)->titulo_album)==0)
            inseriu = 0;

        balanceamentobum(raiz);
        return inseriu;
        
    }

    void balanceamentobum(Albums **no){

        if (*no == NULL) {
            return;
        }

        if((*no)->dir->cor == 1)// SE e vermelho
            rotacaoEsquerda_BUM(no);
        
        if((*no)->esq != NULL && (*no)->esq->cor == 1 && (*no)->esq->esq->cor == 1 )
            rotacaoDireita_BUM(no);

        if((*no)->esq != NULL && (*no)->dir != NULL && (*no)->esq->cor == 1 && (*no)->dir->cor == 1)
            TrocaCorBUM(no);

    }

    // void balanceamentobum(Albums **raiz) {
    //     if (*raiz == NULL) {
    //         return;
    //     }

    //     // Caso 1: O nó pai é vermelho
    //     if ((*raiz)->esq != NULL && (*raiz)->esq->cor == 1) {
    //         // Caso 1.1: O tio também é vermelho
    //         if ((*raiz)->dir != NULL && (*raiz)->dir->cor == 1) {
    //             TrocaCorBUM(raiz);  // Troca cor do pai e tio para preto
    //             (*raiz)->esq->cor = 0;  // Atualiza cor do avô para vermelho
    //         } else {
    //             // Caso 1.2: O tio é preto ou nulo
    //             if ((*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == 1) {
    //                 rotacaoDireita_BUM(raiz);
    //                 TrocaCorBUM(raiz);  // Troca cor do pai e avô
    //             } else if ((*raiz)->esq->dir != NULL && (*raiz)->esq->dir->cor == 1) {
    //                 rotacaoEsquerda_BUM(&((*raiz)->esq));
    //                 rotacaoDireita_BUM(raiz);
    //                 TrocaCorBUM(raiz);  // Troca cor do pai e avô
    //             }
    //         }
    //     }

    //     // Caso 2: O nó direito é vermelho
    //     if ((*raiz)->dir != NULL && (*raiz)->dir->cor == 1) {
    //         // Caso 2.1: O tio também é vermelho
    //         if ((*raiz)->esq != NULL && (*raiz)->esq->cor == 1) {
    //             TrocaCorBUM(raiz);  // Troca cor do pai e tio para preto
    //             (*raiz)->dir->cor = 0;  // Atualiza cor do avô para vermelho
    //         } else {
    //             // Caso 2.2: O tio é preto ou nulo
    //             if ((*raiz)->dir->dir != NULL && (*raiz)->dir->dir->cor == 1) {
    //                 rotacaoEsquerda_BUM(raiz);
    //                 TrocaCorBUM(raiz);  // Troca cor do pai e avô
    //             } else if ((*raiz)->dir->esq != NULL && (*raiz)->dir->esq->cor == 1) {
    //                 rotacaoDireita_BUM(&((*raiz)->dir));
    //                 rotacaoEsquerda_BUM(raiz);
    //                 TrocaCorBUM(raiz);  // Troca cor do pai e avô
    //             }
    //         }
    //     }
    // }

    void TrocaCorBUM(Albums **raiz){
        (*raiz)->cor = 1;
        if((*raiz)->raiz == 1)
            (*raiz)->cor = 0;
        (*raiz)->dir->cor = 0;
        (*raiz)->esq->cor = 0;
    }

    void rotacaoDireita_BUM(Albums **raiz){
        Albums *aux; 
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

    void rotacaoEsquerda_BUM(Albums **raiz){
        Albums *aux; 
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

    Albums *busca_Albuns(Albums* raiz, char nome[20]) {
        Albums *aux;
        aux = NULL;
        if (raiz != NULL) {
            int comparacao = strcmp(nome, raiz->titulo_album);

            if (comparacao == 0) {
                aux = raiz;
            } else if (comparacao < 0) {
                aux = busca_Albuns(raiz->esq, nome);
            } else {
                aux = busca_Albuns(raiz->dir, nome);
            }
        }
        return aux;
    }

    void mostrararAlbuns(Albums *pessoas){
        if (pessoas != NULL){
            printf("\n\nTitulo do album: %s", pessoas->titulo_album);
            printf("\nQuantidade de musicas: %d", pessoas->qnt_musicas);
            printf("\nAno de lancamento: : %d", pessoas->ano_lancamento);
            printf("\n Cor do NO(lembrar de tirar isso ao enviar): %d", pessoas->cor);
        }else
            printf("Album nao encontrado!!!");
    }


int remover_BUM(Albums **raiz, char nome[20]) {
    if (*raiz != NULL) {

        int comparacao = strcmp(nome, (*raiz)->titulo_album);

        if (comparacao < 0) {
            return remover_BUM(&((*raiz)->esq), nome);
        } else if (comparacao > 0) {
            return remover_BUM(&((*raiz)->dir), nome);
        } else {

            if ((*raiz)->dir == NULL && (*raiz)->esq == NULL) {
                liberarMem_M((*raiz)->musicas);
                free(*raiz);
                (*raiz) = NULL;
            } else if ((*raiz)->esq == NULL && (*raiz)->dir != NULL) {
                Albums *temp = (*raiz)->dir;
                if ((*raiz)->raiz == 1) {
                    temp->cor = 0;
                }
                liberarMem_M((*raiz)->musicas);
                free(*raiz);
                *raiz = temp;
            } else if ((*raiz)->dir == NULL && (*raiz)->esq != NULL) {
                Albums *temp = (*raiz)->esq;
                liberarMem_M((*raiz)->musicas);
                free(*raiz);
                *raiz = temp;
            } else {
                Albums *temp = menorValorBUM((*raiz)->dir);

                strcpy((*raiz)->titulo_album, temp->titulo_album);

                return remover_BUM(&((*raiz)->dir), temp->titulo_album);
            }

            balanceamentobum(raiz);
            return 1;
        }
    }

    return 0;
}


Albums* menorValorBUM(Albums* raiz) {
    Albums* atual = raiz;

    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}



void liberaAlbums(Albums *a){
	if (a != NULL){
		liberaAlbums(a->esq);
		liberaAlbums(a->dir);
		liberarMem_M(a->musicas);
		free(a);
	}
}