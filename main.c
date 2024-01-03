//FALTA REMOVER
//MOSTRAR TUDO

#include <stdio.h>
#include <stdlib.h>

#include "artista.h"
#include "album.h"
#include "musica.h"
#include "artista.c"
#include "album.c"
#include "musica.c"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main () {
    Artistas *arvore,*arvore_Temp;
    Albums *album_temp;
    int temp,opcao,opcao_busca,RIsposta;
    char nome[20];

    arvore = NULL;
    arvore_Temp = NULL;
    album_temp = NULL;

    while (1) {
        printf("\n==== Menu ====\n");
        printf("1. Cadastrar Artista\n");
        printf("2. Cadastrar Album\n");
        printf("3. Cadastrar Musica\n");
        printf("4. menu de buscas\n");
        printf("5. menu de remocao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); 

        switch (opcao) {
            case 1:

                cadastrarArtista(&arvore);
                break;
                
            
            case 2:

                printf("Diga o nome da artista que deseja acessar: ");
                scanf(" %[^\n]", nome);
                arvore_Temp = busca_Artista(arvore,nome);
                
                if(arvore_Temp == NULL){
                    printf("Artista nao encontrada!!\n");
                }else{
                    temp = cadastrarBum(&arvore_Temp->albums);
                    if(temp == 1){
                        arvore_Temp->num_albums += 1;   
                        temp = 0;
                    }
                }
                arvore_Temp = NULL;
                break;

            case 3:
            
                printf("Diga o nome da artista que deseja acessar: ");
                scanf(" %[^\n]", nome);
                arvore_Temp = busca_Artista(arvore,nome);
                if(arvore_Temp == NULL){
                    printf("Artista nao encontrada!!\n");

                }else{
                    printf("Agora diga o nome do album: ");
                    scanf(" %[^\n]", nome);
                    album_temp = busca_Albuns(arvore_Temp->albums,nome);
                    if(album_temp == NULL)
                        printf("Album nao encontrada!!\n");
                    
                    else{
                        temp = cadastro_M(&album_temp->musicas);
                        
                        if(temp == 1){
                            album_temp->qnt_musicas =+ 1;
                            temp = 0;
                        }
                    }
                }
                arvore_Temp = NULL;
                album_temp = NULL;
                break;


            case 4:
                do{
                    printf("\n\n1. Buscar em Artistas\n");
                    printf("2. Buscar em Albuns\n");
                    printf("3. Buscar em Musicas\n");
                    printf("0. Voltar ao Menu Principal\n");
                    scanf("%d",&opcao_busca);
                 

                    switch (opcao_busca) {

                        case 1:
                            printf("\nDiga o nome do artista que deseja buscar: ");
                            scanf(" %[^\n]",nome);
                            arvore_Temp = busca_Artista(arvore,nome);
                            mostrarartista(arvore_Temp);
                            arvore_Temp = NULL;
                            break;
                        
                        case 2:
                            printf("\nDiga o nome do artista para buscar: ");
                            scanf(" %[^\n]",nome);
                            arvore_Temp = busca_Artista(arvore,nome);
                            if(arvore_Temp == NULL){
                                printf("Artista nao encontrado!!!");
                                break;
                            }
                            printf("\nAgora informe nome do album que deseja buscar: ");
                            scanf(" %[^\n]",nome);                       
                            album_temp = busca_Albuns(arvore_Temp->albums,nome);
                            if(album_temp == NULL){
                                printf("Album nao encontrado!!!");
                                break;
                            }
                            mostrararAlbuns(album_temp);
                            arvore_Temp = NULL;
                            album_temp = NULL;
                            break;

                        case 3:
                            printf("\nDiga o nome do artista para buscar: ");
                            scanf(" %[^\n]",nome);
                            arvore_Temp = busca_Artista(arvore,nome);
                            if(arvore_Temp == NULL){
                                printf("Artista nao encontrado!!!");
                                break;
                            }
                            printf("\nInforme nome do album que deseja buscar: ");
                            scanf(" %[^\n]",nome);                       
                            album_temp = busca_Albuns(arvore_Temp->albums,nome);
                            if(album_temp == NULL){
                                printf("Album nao encontrado!!!");
                                break;
                            }
                            printf("Agora diga o nome da musica: ");
                            scanf(" %[^\n]",nome);
                            mostrar_M(album_temp->musicas,nome);
                            arvore_Temp = NULL;
                            album_temp = NULL;
                            break;
                    }
                
                } while (opcao_busca != 0);
                break;

            case 5:
                do{
                    printf("\n\n1. Remover em Artistas\n");
                    printf("2. Remover em Albuns\n");
                    printf("3. Remover em Musicas\n");
                    printf("0. Voltar ao Menu Principal\n");
                    scanf("%d",&opcao_busca);
                 

                    switch (opcao_busca) {

                        case 1:
                            printf("\n ------ATENCAO---------\n");
                            printf("ESSA ACAO REMOVERA TODOS OS DEPENDENTES DO ARTISTA SENDO ELES TODOS SEUS ALBUMS E MUSICAS");
                            printf("\nDESEJA CONTINUAR?(1-S/0-N)\n");
                            scanf("%d",&RIsposta);
                            if(RIsposta == 1){
                                printf("\nDiga o nome do artista que deseja remover: ");
                                scanf(" %[^\n]",nome);
                                temp = remover_A(&arvore,nome);
                                if(temp == 1)
                                    printf("\nSucesso ao remover!!!");
                                else
                                    printf("\nFalha ao remover!!!!!");
                            }
                            break;
                        
                        case 2:
                            printf("\n ------ATENCAO---------\n");
                            printf("ESSA ACAO REMOVERA TODOS OS DEPENDENTES DO ALBUM SENDO ELES TODOS SUAS MUSICAS");
                            printf("\nDESEJA CONTINUAR?(1-S/0-N)\n");
                            scanf("%d",&RIsposta);
                            if(RIsposta == 1){

                                printf("\nDiga o nome do que deseja remover: ");
                                scanf(" %[^\n]",nome);
                                arvore_Temp = busca_Artista(arvore,nome);
                                if(arvore_Temp == NULL){
                                    printf("Artista nao encontrado!!!");
                                    break;
                                }
                                printf("\nAgora informe nome do album que deseja remover: ");
                                scanf(" %[^\n]",nome);                       
                                temp = remover_BUM(&arvore_Temp->albums,nome);
                                if(temp == 1)
                                    printf("\nSucesso ao remover!!!");
                                else
                                    printf("\nFalha ao remover!!!!!");
                                arvore_Temp = NULL;

                            }
                            break;

                        case 3:
                            printf("\n ------ATENCAO---------\n");
                            printf("ESSA ACAO REMOVERA A MUSICA EM QUESTAO PERMANENTEMENTE!");
                            printf("\nDESEJA CONTINUAR?(1-S/0-N)\n");
                            scanf("%d",&RIsposta);
                            if(RIsposta == 1){
                                
                                printf("\nDiga o nome do artista fazer a remocao: ");
                                scanf(" %[^\n]",nome);
                                arvore_Temp = busca_Artista(arvore,nome);
                                if(arvore_Temp == NULL){
                                    printf("Artista nao encontrado!!!");
                                    break;
                                }
                                printf("\nInforme nome do album fazer a remocao: ");
                                scanf(" %[^\n]",nome);                       
                                album_temp = busca_Albuns(arvore_Temp->albums,nome);
                                if(album_temp == NULL){
                                    printf("Album nao encontrado!!!");
                                    break;
                                }
                                printf("Agora diga o nome da musica para a remocao: ");
                                scanf(" %[^\n]",nome);
                                removerMusica(&album_temp->musicas,nome);
                                arvore_Temp = NULL;
                                album_temp = NULL;
                            }
                            break;
                    }
                
                } while (opcao_busca != 0);
                break;

            case 0:
            
                // liberaSerie(arvore);
                return 0;
            
            default:
                printf("Opcao invalida. Por favor, escolha novamente.\n");
                getchar();

       }
     }

    return 0;
}