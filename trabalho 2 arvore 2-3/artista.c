#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "album.c"


typedef struct ListaAlbum
{
    Album *arvore_album;
    struct ListaAlbum *prox;
}ListaAlbum;



typedef struct Info
{
    char nome[50];
    char estilo_musical[50];
    int num_albuns;
    ListaAlbum *lista_albuns;  // Lista de árvores de álbuns
}Info;

typedef struct Artista 
{
    Info *info_1, *info_2;
    int num_info;
    struct Artista *esq, *dir, *centro; 
}Artista;




Artista *criaNo(char *nome, char *estilo, int num_albuns, Artista *noEsq, Artista *noCentro) 
{
    Artista *no = (Artista*)malloc(sizeof(Artista)); 
    no->info_1 = (Info*)malloc(sizeof(Info));
    strcpy(no->info_1->nome, nome);
    strcpy(no->info_1->estilo_musical, estilo);
    no->info_1->num_albuns = num_albuns;

    no->info_1->lista_albuns = (ListaAlbum*)malloc(sizeof(ListaAlbum));
    no->info_1->lista_albuns->arvore_album = NULL;
    no->num_info = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;
    no->info_2 = NULL;
    return no;
}


void adicionaNo(Artista **raiz, char *nome, char *estilo, int num_albuns, Artista *filho) 
{
    (*raiz)->info_2 = (Info*)malloc(sizeof(Info));
    (*raiz)->info_2->lista_albuns = (ListaAlbum*)malloc(sizeof(ListaAlbum));
    (*raiz)->info_2->lista_albuns->arvore_album = NULL;
    if(strcmp(nome, (*raiz)->info_1->nome) > 0)
    {
        strcpy((*raiz)->info_2->nome, nome);
        strcpy((*raiz)->info_2->estilo_musical, estilo);
        (*raiz)->info_2->num_albuns = num_albuns;
        (*raiz)->dir = filho;
    }
    else
    {
        strcpy((*raiz)->info_2->nome, (*raiz)->info_1->nome);
        strcpy((*raiz)->info_2->estilo_musical, (*raiz)->info_1->estilo_musical);
        (*raiz)->info_2->num_albuns = (*raiz)->info_1->num_albuns;
        (*raiz)->info_2->lista_albuns->arvore_album = (*raiz)->info_1->lista_albuns->arvore_album;

        strcpy((*raiz)->info_1->nome, nome);
        strcpy((*raiz)->info_1->estilo_musical, estilo);
        (*raiz)->info_1->num_albuns = num_albuns;
        (*raiz)->info_1->lista_albuns->arvore_album = NULL;

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    }
    (*raiz)->num_info = 2;
}


Artista *quebraNo(Artista **raiz, Artista *filho, char *nome, char *estilo, int num_albuns, Info *sobe) 
{
    Artista *maiorNo;
    maiorNo = NULL;

    if (strcmp(nome, (*raiz)->info_2->nome) > 0) 
    {
        strcpy(sobe->nome, (*raiz)->info_2->nome);
        strcpy(sobe->estilo_musical, (*raiz)->info_2->estilo_musical);
        sobe->num_albuns = (*raiz)->info_2->num_albuns;

        maiorNo = criaNo(nome, estilo, num_albuns, (*raiz)->dir, filho);
    } 
    
    else if (strcmp(nome, (*raiz)->info_1->nome) < 0) 
    {
        strcpy(sobe->nome, (*raiz)->info_1->nome);
        strcpy(sobe->estilo_musical, (*raiz)->info_1->estilo_musical);
        sobe->num_albuns = (*raiz)->info_1->num_albuns;

        maiorNo = criaNo((*raiz)->info_2->nome, (*raiz)->info_2->estilo_musical, (*raiz)->info_2->num_albuns, (*raiz)->centro, (*raiz)->dir);
        
        strcpy((*raiz)->info_1->nome, nome);
        strcpy((*raiz)->info_1->estilo_musical, estilo);
        (*raiz)->info_1->num_albuns = num_albuns;
        (*raiz)->centro = filho;
    }

    else 
    {
        strcpy(sobe->nome, nome);
        strcpy(sobe->estilo_musical, estilo);
        sobe->num_albuns = num_albuns;
        maiorNo = criaNo((*raiz)->info_2->nome,(*raiz)->info_2->estilo_musical, (*raiz)->info_2->num_albuns, filho, (*raiz)->dir);  
    }

    (*raiz)->num_info = 1;
    (*raiz)->info_2 = NULL;
    (*raiz)->dir = NULL; 
    return maiorNo;
}

int folha(Artista *raiz)
{
    int valid = 0;
    if(raiz->esq == NULL)
        valid = 1;
    return valid;
}

Artista *inserir(Artista **raiz, char *nome, char *estilo, int num_albuns, Artista *pai, Info *infoSobe, int *flag)
{
    Artista *maiorNo;
    if (*raiz == NULL)
    {
        *raiz = criaNo(nome, estilo, num_albuns, NULL, NULL);
        *flag = 1;
    }
    else
    {
        if (folha(*raiz))
        {
            if ((*raiz)->num_info == 1)
            {
                adicionaNo(raiz, nome, estilo, num_albuns, NULL);
                maiorNo = NULL;
                *flag = 1;
            }
            else
            {
                maiorNo = quebraNo(raiz, NULL, nome, estilo, num_albuns, infoSobe);

                if (pai == NULL)
                {
                    *raiz = criaNo(infoSobe->nome, infoSobe->estilo_musical, infoSobe->num_albuns, *raiz, maiorNo);
                    maiorNo = NULL;
                }
                *flag = 1;
            }
        }
        else
        {
            if (strcmp(nome, (*raiz)->info_1->nome) < 0)   
                maiorNo = inserir(&((*raiz)->esq), nome, estilo, num_albuns, *raiz, infoSobe, flag);
            else if (((*raiz)->num_info == 1) || (((*raiz)->num_info == 2) && strcmp(nome, (*raiz)->info_2->nome) < 0))
                maiorNo = inserir(&((*raiz)->centro), nome, estilo, num_albuns, *raiz, infoSobe, flag);
            else
                maiorNo = inserir(&((*raiz)->dir), nome, estilo, num_albuns, *raiz, infoSobe, flag);   

            if (maiorNo != NULL)
            {
                if ((*raiz)->num_info == 1)
                {
                    adicionaNo(raiz, infoSobe->nome, infoSobe->estilo_musical, infoSobe->num_albuns, maiorNo);
                    maiorNo = NULL;
                }
                else
                {
                    maiorNo = quebraNo(raiz, maiorNo, infoSobe->nome, infoSobe->estilo_musical, infoSobe->num_albuns, infoSobe);
                    if (pai == NULL)
                    {
                        *raiz = criaNo(infoSobe->nome, infoSobe->estilo_musical, infoSobe->num_albuns, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

void imprimir(Artista *raiz)
{
    if(raiz != NULL)
    {
        imprimir(raiz->esq);
        printf("Info 1 nome: %s\n", raiz->info_1->nome);
        printf("Info 1 estilo: %s\n", raiz->info_1->estilo_musical);
        printf("Info 1 numero albuns: %d\n", raiz->info_1->num_albuns);
        imprimir(raiz->centro);
        if(raiz->num_info == 2)
        {
            printf("Info 2 nome: %s\n", raiz->info_2->nome);
            printf("Info 2 estilo: %s\n", raiz->info_2->estilo_musical);
            printf("Info 2 numero albuns: %d\n", raiz->info_2->num_albuns);
        }
        imprimir(raiz->dir);
    }
}

Artista *achar_artista(Artista *raiz, const char *nome, int *posicao)
{
    Artista *encontrada = NULL;

    if(raiz != NULL)
    {
        if(strcmp(nome, raiz->info_1->nome) == 0)
        {
            encontrada = raiz;
            *posicao = 1;
        }

        if(raiz->num_info == 2)
        {
            if(strcmp(nome, raiz->info_1->nome) == 0)
            {
                encontrada = raiz;
                *posicao = 1;
            }
            else if(strcmp(nome, raiz->info_2->nome) == 0)
            {
                encontrada = raiz;
                *posicao = 2;   
            }
        }

        if(encontrada == NULL)
        {
            if(strcmp(nome, raiz->info_1->nome) < 0)
                encontrada = achar_artista(raiz->esq, nome, posicao);
            else if((raiz->num_info == 1 || (raiz->num_info == 2 && strcmp(nome, raiz->info_2->nome) < 0)))
                encontrada = achar_artista(raiz->centro, nome, posicao);
            else
                encontrada = achar_artista(raiz->dir, nome, posicao);
        }
    }
    return encontrada;
}


void cadastrar_albuns(Artista *albuns, char *titulo, int ano_lancamento, int num_musicas, int posicao)
{
    printf("posicao cadastrar album: %d\n",posicao);
    Info_album sobe;
    if(posicao == 1)
        inserir_album(&(albuns)->info_1->lista_albuns->arvore_album, titulo, ano_lancamento, num_musicas, NULL, &sobe);
    else if(posicao == 2)
        inserir_album(&(albuns)->info_2->lista_albuns->arvore_album, titulo, ano_lancamento, num_musicas, NULL, &sobe);
}

void mostrar_album(Artista *raiz, int posicao)
{
    printf("entrou aqui!!!\n");
    if(posicao == 1)
        imprimir_album(raiz->info_1->lista_albuns->arvore_album);
    else if(posicao == 2)
        imprimir_album(raiz->info_2->lista_albuns->arvore_album);
}



Artista* findminimum_A(Artista* no) {
    if (no == NULL) 
        return NULL;  
    
    while (no->esq != NULL) 
        no = no->esq;
    
    return no;
}

Artista* findmaximum_A(Artista* no) {
    if (no == NULL) 
        return NULL;  
    
    while (no->dir != NULL) 
        no = no->dir;
    
    return no;
}

void merge_A(Artista **raiz) {
    if (*raiz == NULL || (*raiz)->num_info == 1) 
        return;

    Artista *pai = NULL; 
    Artista *irmao = NULL; 

    if ((*raiz)->esq != NULL) {
        pai = *raiz;
        irmao = (*raiz)->esq;
    } else if ((*raiz)->dir != NULL) {
        pai = *raiz;
        irmao = (*raiz)->dir;
    } else if ((*raiz)->centro != NULL) {
        pai = *raiz;
        irmao = (*raiz)->centro;
    } else if ((*raiz)->esq != NULL && (*raiz)->dir != NULL) {
        pai = *raiz;
        irmao = (*raiz)->esq;
    }

    if (irmao != NULL && irmao->num_info == 1) {
        if (pai->esq == *raiz) {
            pai->centro = irmao->esq;
            pai->info_2 = pai->info_1;
            pai->info_1 = irmao->info_1;
            pai->dir = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        } else if (pai->centro == *raiz) {
            pai->info_2 = irmao->info_1;
            pai->dir = pai->centro;
            pai->centro = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        } else if (pai->dir == *raiz) {
            pai->info_2 = irmao->info_1;
            pai->dir = irmao->centro;
            free(irmao);
            pai->num_info = 2;
        }
    } else {
        if (pai->esq == *raiz) {
            irmao->info_1 = pai->info_1;
            pai->info_1 = pai->info_2;
            irmao->centro = irmao->esq;
            irmao->esq = irmao->dir;
            irmao->dir = NULL;
            pai->num_info = 1;
        } else if (pai->centro == *raiz) {
            irmao->info_1 = pai->info_1;
            pai->info_1 = pai->info_2;
            irmao->dir = irmao->esq;
            irmao->esq = irmao->centro;
            irmao->centro = NULL;
            pai->num_info = 1;
        } else if (pai->dir == *raiz) {
            irmao->info_1 = pai->info_2;
            irmao->centro = irmao->dir;
            irmao->dir = NULL;
            pai->num_info = 1;
        }
    }
}


void removeArtista(Artista **raiz, char titulo[50]) {
    if (*raiz == NULL)
        return;     

    if (*raiz == NULL)
        return;     

    if (strcmp((*raiz)->info_1->nome, titulo) == 0 || strcmp((*raiz)->info_2->nome, titulo) == 0) {
        if (folha(*raiz)) {
            if (strcmp((*raiz)->info_1->nome, titulo) == 0){
                if((*raiz)->info_2 != NULL){
                    // Usando memcpy para copiar a memória de info_1 para info_2
                    memcpy(&(*raiz)->info_2, &(*raiz)->info_1, sizeof(Artista));
                    free((*raiz)->info_1);
                } else {
                    printf("entrou aqui");
                    free((*raiz)->info_1);
                    free(*raiz);
                    *raiz = NULL;
                }
            }
            else
                free((*raiz)->info_2);
        } else {
            if (strcmp((*raiz)->info_1->nome, titulo) == 0) {
                Artista *swap = findmaximum_A((*raiz)->esq);
                free((*raiz)->info_1);
                // Usando memcpy para copiar a memória de swap->info_1 para info_1
                memcpy(&(*raiz)->info_1, &swap->info_1, sizeof(Artista));
                removeArtista(&(*raiz)->esq, swap->info_1->nome);
            } else {
                Artista *swap = findminimum_A((*raiz)->dir);
                free((*raiz)->info_2);
                // Usando memcpy para copiar a memória de swap->info_2 para info_2
                memcpy(&(*raiz)->info_2, &swap->info_2, sizeof(Artista));
                removeArtista(&(*raiz)->dir, swap->info_2->nome);
            }
        }
    } else {
        if (strcmp((*raiz)->info_1->nome, titulo) > 0) {
            removeArtista(&(*raiz)->esq, titulo); 
        } else if (strcmp((*raiz)->info_1->nome, titulo) <= 0 && (*raiz)->num_info == 2) {
            removeArtista(&(*raiz)->centro, titulo);
        } else {
            if (strcmp((*raiz)->info_1->nome, titulo) < 0) {
                removeArtista(&(*raiz)->centro, titulo);
            } else {
                removeArtista(&(*raiz)->dir, titulo);
            }
        }
    }

    merge_A(raiz); 
}