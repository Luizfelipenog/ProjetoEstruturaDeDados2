#include <stdio.h>
#include <stdlib.h>
#include "artista.c"


void menu()
{
    printf("\nDigite a opcao desejada:\n0 - Sair\n1 - Cadastrar Artista\n2 - Exibir Artista\n3 - Cadastrar Albuns\n4 - Cadastrar Musicas\n5 - Buscas\n6 - Excluir\n>>> ");
}

void limparBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    Artista *arvore = NULL;
    //Info *achado_artista = NULL;
    Artista *achou = NULL;
    Artista *no = NULL;
    int op, numero_album,opcao_busca,RIsposta;
    char nome[70], estilo[70], nome_procurar[70];
    char titulo[70], artista[70];
    int ano_lancamento, num_musicas;
    do
    {
        int flag, achado, achado_2;
        Info sobe;
        menu();
        scanf("%d",&op);
        limparBuffer(); 
        switch (op)
        {
            case 0:
                break;
            case 1:
                printf("Nome do artista: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';
                printf("Numero de albuns: ");
                scanf("%d", &numero_album);
                limparBuffer();
                inserir(&arvore, nome, estilo, numero_album, NULL, &sobe, &flag);
                if(flag == 1)
                    printf("insercao completa.\n");
                else
                    printf("erro ao inserir\n");
                break;
            case 2:
                imprimir(arvore);
                break;
            
            case 3:
                printf("nome do artista que deseja procurar: ");
                fgets(nome_procurar, sizeof(nome_procurar), stdin);
                nome_procurar[strcspn(nome_procurar, "\n")] = '\0';
                no = achar_artista(arvore, nome_procurar, &achado);
                if(no)
                {
                    printf("posicao: %d\n",achado);
                    printf("nome info 1: %s\n",no->info_1->nome);
                    printf("nome info 2: %s\n",no->info_2->nome);
                    printf("titulo: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    printf("ano lancamento: ");
                    scanf("%d",&ano_lancamento);
                    printf("Numero de albuns: ");
                    scanf("%d", &num_musicas);
                    cadastrar_albuns(no, titulo, ano_lancamento, num_musicas, achado);
                    printf("insercao completa.\n");
                }
                else
                    printf("nao achei\n");
                break;
            
            case 4:
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                if(achou)
                    mostrar_album(achou, achado_2);
                else
                    printf("artista nao encontrado\n");
                break;
            case 6:
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
                                removeArtista(&arvore,nome);
                            }
                            break;
                        
                        // case 2:
                        //     printf("\n ------ATENCAO---------\n");
                        //     printf("ESSA ACAO REMOVERA TODOS OS DEPENDENTES DO ALBUM SENDO ELES TODOS SUAS MUSICAS");
                        //     printf("\nDESEJA CONTINUAR?(1-S/0-N)\n");
                        //     scanf("%d",&RIsposta);
                        //     if(RIsposta == 1){

                        //         printf("\nDiga o nome do que deseja remover: ");
                        //         scanf(" %[^\n]",nome);
                        //         arvore_Temp = busca_Artista(arvore,nome);
                        //         if(arvore_Temp == NULL){
                        //             printf("Artista nao encontrado!!!");
                        //             break;
                        //         }
                        //         printf("\nAgora informe nome do album que deseja remover: ");
                        //         scanf(" %[^\n]",nome);                       
                        //         temp = remover_BUM(&arvore_Temp->albums,nome);
                        //         if(temp == 1)
                        //             printf("\nSucesso ao remover!!!");
                        //         else
                        //             printf("\nFalha ao remover!!!!!");
                        //         arvore_Temp = NULL;

                        //     }
                        //     break;

                        // case 3:
                        //     printf("\n ------ATENCAO---------\n");
                        //     printf("ESSA ACAO REMOVERA A MUSICA EM QUESTAO PERMANENTEMENTE!");
                        //     printf("\nDESEJA CONTINUAR?(1-S/0-N)\n");
                        //     scanf("%d",&RIsposta);
                        //     if(RIsposta == 1){
                                
                        //         printf("\nDiga o nome do artista fazer a remocao: ");
                        //         scanf(" %[^\n]",nome);
                        //         arvore_Temp = busca_Artista(arvore,nome);
                        //         if(arvore_Temp == NULL){
                        //             printf("Artista nao encontrado!!!");
                        //             break;
                        //         }
                        //         printf("\nInforme nome do album fazer a remocao: ");
                        //         scanf(" %[^\n]",nome);                       
                        //         album_temp = busca_Albuns(arvore_Temp->albums,nome);
                        //         if(album_temp == NULL){
                        //             printf("Album nao encontrado!!!");
                        //             break;
                        //         }
                        //         printf("Agora diga o nome da musica para a remocao: ");
                        //         scanf(" %[^\n]",nome);
                        //         removerMusica(&album_temp->musicas,nome);
                        //         arvore_Temp = NULL;
                        //         album_temp = NULL;
                        //     }
                        //     break;
                    }
                
                } while (opcao_busca != 0);
                break;


            default:
                break;
        }
    } while (op != 0);
}