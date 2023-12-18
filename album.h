typedef struct albums Albums;

int cadastrarBum(Albums ** raiz);
int insesrir_BUM(Albums **raiz,Albums *no);
void balanceamentobum(Albums **raiz);
void TrocaCorBUM(Albums **raiz);
void rotacaoDireita_BUM(Albums **raiz);
void rotacaoEsquerda_BUM(Albums **raiz);
Albums *busca_Albuns(Albums* raiz, char nome[20]);
void mostrararAlbuns(Albums *pessoas);
Albums* menorValorBUM(Albums* raiz);
int remover_BUM(Albums **raiz, char nome[20]);
void liberaAlbums(Albums *a);