typedef struct musicas Musicas;
int cadastro_M(Musicas** pessoa);
int inserir_M(Musicas ** M, Musicas *new);
void mostrar_M(Musicas *pessoas,char nome[20]);
void liberarMem_M(Musicas *pessoas);
void removerMusica(Musicas **a, char nome[20]);