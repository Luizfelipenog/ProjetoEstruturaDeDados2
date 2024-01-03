typedef struct artistas Artistas;


int insesrir_A(Artistas **raiz,Artistas *no);
void cadastrarArtista(Artistas** raiz);
void balanceamento(Artistas **no);
void TrocaCor(Artistas **raiz);
void rotacaoDireita_A(Artistas **raiz);
void rotacaoEsquerda_A(Artistas **raiz);
Artistas *busca_Artista(Artistas* raiz, char nome[20]);
void mostrarartista(Artistas *pessoas);
int remover_A(Artistas **raiz, char nome[20]);
Artistas* menorValor(Artistas* raiz);
void liberaArtista(Artistas *a);