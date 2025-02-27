#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tfidf.h"
#include <math.h>


void converter_minusculo(char *documento) {
/*
Parâmetros:
    - documento: uma string passada por referência.

A função deve converter todos os caracteres maiúsculos (entre 'A' e 'Z', ou 65 e 90 da tabela ASCII)
para minúsculo (isto é, entre 'a' até 'z').

Em seguida, converta qualquer caractere da tabela ASCII entre 1 e 127 (com exceção de 'a' até 'z') para
espaço em branco (caractere 32). Para facilitar, ignore a existência caracteres com acento.

Exemplo:
    "Rua ABC, 149, Bairro: Xyz" deve ser convertida para:
    "rua abc       bairro  xyz"
*/

    char *head = documento;

    while (*head) {
        if (*head >= 'a' && *head <= 'z') {
            head++;
            continue;
        }

        *head = *head >= 'A' && *head <= 'Z' ? *head - 'A' + 'a' : ' ';
        head++;
    }

}


void tokenize(char **resultado, int *qtd_termos, char *str) {
/*
Parâmetros:
    - resultado: um array de char* (ou seja, cada posição deste array guarda um endereço de memória).
    Considere que este array de char* já foi alocado na memória e que há espaço (posições no array) suficiente para
    guardar os endereços dos tokens.
    - qtd_termos: ponteiro para int. Serve para retornar (por referência) a quantidade de termos (tokens) encontrados.
    - str: uma string passada por referência, sobre a qual encontraremos os termos.

A função deve encontrar o início de cada nova palavra em str, e guardar o seu endereço em uma nova posição da variável resultado.
Além disso, a função deve transformar todos os espaços em branco em \0.

Exemplo:
    A string str "Programando em linguagem C\0" será convertida em "Programando\0em\0linguagem\0C\0".
    Além disso, a variável resultado terá os seguintes valores:
        - resultado[0] guarda o endereço de memória de "P" em "Programando";
        - resultado[1] guarda o endereço de memória de "e" em "em";
        - resultado[2] guarda o endereço de memória de "l" em "linguagem";
        - resultado[3] guarda o endereço de memória de "C" em "C";
    Por fim, o valor apontado por qtd_termos deve receber o valor 4.
*/
    const char DELIM[] = " ";
    char *tok = strtok(str, DELIM);
    *qtd_termos = 0;

    while (tok) {
        resultado[(*qtd_termos)++] = tok;
        tok = strtok(NULL, DELIM);
    }

}


void carregar_termos(ListaTermos *lista_termos, int qtd_documentos, char matriz_termos[][TAMANHO_MAX], int *qtd_termos) {
/*
Parâmetros:
    - lista_termos: um array cujas posições são elementos da struct ListaTermos. Cada elemento do array contém a lista
    de termos de um documento diferente, e a quantidade de termos naquele documento.
    - qtd_documentos: quantidade de documentos. O array lista_termos terá qtd_documentos elementos.
    - matriz_termos: matriz de char para armazenar os termos únicos encontrados em todos os documentos;
    Considere que esta matriz de char já foi alocada na memória e que há espaço suficiente para guardar todos os termos encontrados. Além disso,
    considere que nenhum termo será maior que TAMANHO_MAX.
    - qtd_termos: ponteiro para int. Serve para retornar (por referência) a quantidade de termos adicionados na matriz_termos, pois a matriz
    terá mais posições alocadas do que termos únicos existentes. Ou seja, o valor de qtd_termos será importante para saber até qual posição de
    matriz_termos contém termos válidos.

A função deve varrer todos os termos existentes em todas as posições do array lista_termos, e em seguida fazer uma busca sequencial em matriz_termos,
para saber se o termo atual já foi incluído em matriz_termos. Se o termo não existe em matriz_termos, adicione-o em matriz_termos e atualize o valor de qtd_termos.

Exemplo:
    Suponha a lista de termos de 3 documentos:
        lista_termos[0].termos = {"ola", "mundo", "ola"}
        lista_termos[1].termos = {"ela", "disse", "ola"}
        lista_termos[2].termos = {"ela", "conhece", "o", "mundo"}
    Então matriz_termos deve ter os seguintes elementos (desconsidere a atribuição, pois você terá que usar strcpy):
        matriz_termos[0] = "ola"
        matriz_termos[1] = "mundo"
        matriz_termos[2] = "ela"
        matriz_termos[3] = "disse"
        matriz_termos[4] = "conhece"
        matriz_termos[5] = "o"
    E o conteúdo apontado por qtd_termos deve ser 6, pois foram encontrados 6 termos únicos em todos os documentos.
*/
    for (int i = 0; i < qtd_documentos; i++) {
        ListaTermos *tmp = lista_termos + i;

        for (int j = 0; j < tmp->qtd_termos; j++) {
            char found = 0;

            for (int k = 0; k < *qtd_termos; k++)
                if (!strcmp(matriz_termos[k], tmp->termos[j])) {
                    found = 1;
                    break;
                }

            if (found) continue;

            strcpy(matriz_termos[(*qtd_termos)++], tmp->termos[j]);
        }
    }

}


int tf(char *termo, ListaTermos lista_termos) {
/*
Parâmetros:
    - termo: uma string passada por referência.
    - lista_termos: struct com a lista de termos de um documento (pode haver várias ocorrências de um mesmo termo).

A função deve varrer todos os termos existentes em lista_termos, e contar quantas vezes a string termo aparece em lista_termos.

Retorno:
    A função deve retornar um número inteiro, representando o número de ocorrências da string termo.

Exemplo:
    Suponha que:
        lista_termos.termos = {"ola", "mundo", "ola"}
    Se o parâmetro termo for "ola", a função deve retornar 2.
    Se o parâmetro termo for "mundo", a função deve retornar 1.
    Se o parâmetro termo for "ela", a função deve retornar 0.
*/
    int res = 0;
    for (int i = 0; i < lista_termos.qtd_termos; i++)
        if (!strcmp(termo, lista_termos.termos[i]))
            res++;

    return res;
}


double idf(char *termo, ListaTermos *lista_termos, int qtd_documentos) {
/*
Parâmetros:
    - termo: uma string passada por referência.
    - lista_termos: um array cujas posições são elementos da struct ListaTermos. Cada elemento do array contém a lista
        de termos de um documento diferente, e a quantidade de termos naquele documento.
    - qtd_documentos: quantidade de documentos. O array lista_termos terá qtd_documentos elementos.

A função calcula o inverso da frequência nos documentos (inverse document frequency) do termo passado por parâmetro. Ou seja,
você deve contar em quantos documentos o termo aparece (vamos chamar esta medida de docs_com_termo).

Retorno:
    Se docs_com_termo for igual a zero, retorne 0. Caso contrário, retorne: log((double)qtd_documentos) / (1 + docs_com_termo)).
*/
    int counter = 0;

    for (int i = 0; i < qtd_documentos; i++) {
        for (int j = 0; j < lista_termos[i].qtd_termos; j++)
            if (!strcmp(termo, lista_termos[i].termos[j])) {
                ++counter;
                break;
            }
    }

    return !counter ? .0 : log(((double)qtd_documentos / ++counter));
}


double similaridade_cosseno(double *vet1, double *vet2, int qtd_termos) {
/*
Parâmetros:
    - vet1: array com os valores de tf-idf de um documento.
    - vet2: array com os valores de tf-idf de outro documento.
    - qtd_termos: quantidade de termos únicos. Considere que os arrays vet1 e vet2 possuem este tamanho.

A função calcula a similaridade do cosseno entre os arrays vet1 e vet2.

Retorno:
    Considere as seguintes variáveis hipotéticas:
        - produto_interno, o produto interno de vet1 e vet2;
        - norma_vet1, a norma de vet1;
        - norma_vet2, a norma de vet2;
    A função deve retornar:
        - zero, se norma_vet1 for igual a zero, ou norma_vet2 for igual a zero.
        - produto_interno / (norma_vet1 * norma_vet2)
*/
    double intern = 0, n1 = 0, n2 = 0;

    for (int i = 0; i < qtd_termos; i++)
        intern += vet1[i] * vet2[i],
        n1 += pow(vet1[i], 2),
        n2 += pow(vet2[i], 2);

    n1 = sqrt(n1), n2 = sqrt(n2);

    return .0 ? !n1 || !n2 : intern / (n1 * n2);
}
