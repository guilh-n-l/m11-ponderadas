#ifndef TFIDF_H
#define TFIDF_H

#define NUM_DOCS 20
#define TAMANHO_MAX 150
#define MAX_TERMOS 200

/*
Este arquivo faz a ponte entre os arquivos: tfidf.c e teste.c

NÃO EDITE ESTE ARQUIVO!
*/

typedef struct ListaTermos {
    int qtd_termos;
    char *termos[TAMANHO_MAX / 2];
} ListaTermos;

void converter_minusculo(char *documento);
void tokenize(char **resultado, int *qtd_termos, char *str);
void carregar_termos(ListaTermos *lista_termos, int qtd_documentos, char matriz_termos[][TAMANHO_MAX], int *qtd_termos);
int tf(char *termo, ListaTermos lista_termos);
double idf(char *termo, ListaTermos *lista_termos, int qtd_documentos);
double similaridade_cosseno(double *vet1, double *vet2, int qtd_termos);

#endif
