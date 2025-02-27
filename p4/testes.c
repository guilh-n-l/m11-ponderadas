#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tfidf.h"

// Se estiver usando o COLAB, mude o valor de COLAB abaixo para 1:
#define COLAB 0

int test_converter_minusculo() {
    int i, corretos = 0;
    char original[3][TAMANHO_MAX] = {
        "ola;mundo",
        "OLa, MuNdO!",
        "man1pulando $trings\tEm Lingu@gem-{C]."
    };
    char esperado[3][TAMANHO_MAX] = {
        "ola mundo",
        "ola  mundo ",
        "man pulando  trings em lingu gem  c  "
    };

    printf("\nTestando a funcao converter_minusculo():\n");
    for(i = 0; i < 3; i++) {
        converter_minusculo(original[i]);
        if (!strcmp(original[i], esperado[i])) {
            corretos++;
            printf("  PASS...");
        } else
            printf("  FAIL...");
        printf("String obtida: \"%s\"\n         String esperada: \"%s\"\n", original[i], esperado[i]);
    }
    return corretos;
}


int test_tokenize() {
    int i, j, corretos = 0;
    char original[3][TAMANHO_MAX] = {
        "olamundo",
        "ola mundo",
        "programacao em   linguagem  c",
    };
    char original_qtd[3] = {1, 2, 4};
    char *original_enderecos[3][MAX_TERMOS] = {
        {&original[0][0]},
        {&original[1][0], &original[1][4]},
        {&original[2][0], &original[2][12], &original[2][17], &original[2][28]}
    };
    char original_termos[3][MAX_TERMOS][TAMANHO_MAX] = {
        {"olamundo"},
        {"ola", "mundo"},
        {"programacao", "em", "linguagem", "c"}
    };
    printf("\nTestando a funcao tokenize():\n");
    for(i = 0; i < 3; i++) {
        char copia[TAMANHO_MAX];
        strcpy(copia, original[i]);
        char *termos[MAX_TERMOS];
        int qtd_termos;
        tokenize(termos, &qtd_termos, original[i]);
        int ok = 1; // true
        for(j = 0; j < original_qtd[i]; j++) {
            // compara se todos os enderecos de memoria sao iguais
            if (termos[j] != original_enderecos[i][j] || strcmp(termos[j], original_termos[i][j]) != 0) {
                ok = 0; // false
                break;
            }
        }
        if (ok && (qtd_termos == original_qtd[i])) {
            corretos++;
            printf("  PASS...");
        } else
            printf("  FAIL...");
        printf("String original: \"%s\"\n", copia);
        printf("         Qtd de termos obtidos / esperados: %d / %d\n         Termos obtidos: ", qtd_termos, original_qtd[i]);
        for(j = 0; j < qtd_termos; j++) {
            printf("\"%s\"", termos[j]);
            if (j < qtd_termos-1)
                printf(", ");
        }
        printf("\n         Termos esperados: ");
        for(j = 0; j < original_qtd[i]; j++) {
            printf("\"%s\"", original_termos[i][j]);
            if (j < original_qtd[i]-1)
                printf(", ");
        }
        printf("\n");
        //printf("\n         Qtd de termos obtidos / esperados: %d / %d\n", qtd_termos, original_qtd[i]);
    }
    return corretos;
}


int test_carregar_termos() {
    int i, corretos = 0;
    char documentos[3][TAMANHO_MAX] = {
        "um\0dois\0tres",
        "quatro\0tres\0um",
        "cinco\0um"
    };
    ListaTermos lista_termos[3];
    lista_termos[0].termos[0] = &documentos[0][0];
    lista_termos[0].termos[1] = &documentos[0][3];
    lista_termos[0].termos[2] = &documentos[0][8];
    lista_termos[0].qtd_termos = 3;
    lista_termos[1].termos[0] = &documentos[1][0];
    lista_termos[1].termos[1] = &documentos[1][7];
    lista_termos[1].termos[2] = &documentos[1][12];
    lista_termos[1].qtd_termos = 3;
    lista_termos[2].termos[0] = &documentos[2][0];
    lista_termos[2].termos[1] = &documentos[2][6];
    lista_termos[2].qtd_termos = 2;
    char termos[MAX_TERMOS][TAMANHO_MAX];
    int qtd_termos;
    printf("\nTestando a funcao carregar_termos():\n");
    carregar_termos(lista_termos, 3, termos, &qtd_termos);
    if (qtd_termos == 5 && strcmp(termos[0], "um") == 0 && strcmp(termos[1], "dois") == 0 && strcmp(termos[2], "tres") == 0
        && strcmp(termos[3], "quatro") == 0 && strcmp(termos[4], "cinco") == 0) {
        corretos++;
        printf("  PASS...");
    } else
        printf("  FAIL...");
    printf("Qtd de termos obtidos / esperados: %d / %d\n", qtd_termos, 5);
    printf("         Termos unicos obtidos: ");
    for(i = 0; i < qtd_termos; i++) {
        printf("\"%s\"", termos[i]);
        if (i < qtd_termos-1)
            printf(", ");
    }
    printf("\n         Termos unicos esperados: \"um\", \"dois\", \"tres\", \"quatro\", \"cinco\"\n");
    return corretos;
}


int test_tf() {
    int i, corretos = 0;
    char documento[TAMANHO_MAX] = {"um\0dois\0tres\0dois\0um\0quatro\0dois\0sete"};
    ListaTermos lista_termos;
    lista_termos.termos[0] = &documento[0];
    lista_termos.termos[1] = &documento[3];
    lista_termos.termos[2] = &documento[8];
    lista_termos.termos[3] = &documento[13];
    lista_termos.termos[4] = &documento[18];
    lista_termos.termos[5] = &documento[21];
    lista_termos.termos[6] = &documento[28];
    lista_termos.termos[7] = &documento[33];
    lista_termos.qtd_termos = 8;
    char original_termos[3][TAMANHO_MAX] = {"seis", "sete", "dois"};
    int original_freq[3] = {0, 1, 3};
    printf("\nTestando a funcao tf():\n");
    for(i = 0; i < 3; i++) {
        int freq_obtida = tf(original_termos[i], lista_termos);
        if (freq_obtida == original_freq[i]) {
            corretos++;
            printf("  PASS...");
        } else
            printf("  FAIL...");
        printf("Frequencia obtida do termo \"%s\": %d\n", original_termos[i], freq_obtida);
        printf("         Frequencia esperada: %d\n", original_freq[i]);
    }
    return corretos;
}


int test_idf() {
    int i, corretos = 0;
    double tolerancia = 0.01;
    char documentos[5][TAMANHO_MAX] = {
        "um\0dois\0tres\0quatro",
        "cinco\0seis\0um\0tres",
        "sete\0tres\0oito",
        "dez\0onze",
        "quinze"
    };
    ListaTermos lista_termos[5];
    lista_termos[0].termos[0] = &documentos[0][0];
    lista_termos[0].termos[1] = &documentos[0][3];
    lista_termos[0].termos[2] = &documentos[0][8];
    lista_termos[0].termos[3] = &documentos[0][13];
    lista_termos[0].qtd_termos = 4;
    lista_termos[1].termos[0] = &documentos[1][0];
    lista_termos[1].termos[1] = &documentos[1][6];
    lista_termos[1].termos[2] = &documentos[1][11];
    lista_termos[1].termos[3] = &documentos[1][14];
    lista_termos[1].qtd_termos = 4;
    lista_termos[2].termos[0] = &documentos[2][0];
    lista_termos[2].termos[1] = &documentos[2][5];
    lista_termos[2].termos[2] = &documentos[2][10];
    lista_termos[2].qtd_termos = 3;
    lista_termos[3].termos[0] = &documentos[3][0];
    lista_termos[3].termos[1] = &documentos[3][4];
    lista_termos[3].qtd_termos = 2;
    lista_termos[4].termos[0] = &documentos[4][0];
    lista_termos[4].qtd_termos = 1;
    char original_termos[3][TAMANHO_MAX] = {"um", "tres", "nove"};
    double original_valor[3] = {0.510826, 0.223144, 0};
    printf("\nTestando a funcao idf():\n");
    for(i = 0; i < 3; i++) {
        double valor_obtido = idf(original_termos[i], lista_termos, 5);
        if (fabs(original_valor[i] - valor_obtido) <= tolerancia) {
            corretos++;
            printf("  PASS...");
        } else
            printf("  FAIL...");
        printf("Valor do idf obtido para o termo \"%s\": %lf\n", original_termos[i], valor_obtido);
        printf("         Valor esperado do idf: %lf +/-0.01\n", original_valor[i]);
    }
    return corretos;
}


int test_similaridade_cosseno() {
    int i, j, corretos = 0;
    double tolerancia = 0.01;
    double vet1[3][10] = {
        {1.0, 2.0, -1.0},
        {3.0, 0.0, 2.0, 1.0},
        {1.2, 2.3, 3.1, 4.4, 5.0, 6.8, 7.2, 8.5, 9.3, 6.1}
    };
    double vet2[3][10] = {
        {2.0, -1.0, 0.0},
        {1.0, 2.0, 3.0, 1.0},
        {0.9, 5.4, 2.7, 3.6, 4.2, 5.5, 6.3, 7.1, 8.4, 9.0}
    };
    double produto_esperado[3] = {0.0, 0.690066, 0.964486};
    int qtd_elementos[3] = {3, 4, 10};
    printf("\nTestando a funcao similaridade_cosseno():\n");
    for(i = 0; i < 3; i++) {
        double resp = similaridade_cosseno(vet1[i], vet2[i], qtd_elementos[i]);
        if (fabs(produto_esperado[i] - resp) <= tolerancia) {
            corretos++;
            printf("  PASS...");
        } else
            printf("  FAIL...");
        printf("Similaridade entre os vetores:\n         vet1 = (");
        for(j = 0; j < qtd_elementos[i]; j++) {
            printf("%.1lf", vet1[i][j]);
            if (j < qtd_elementos[i]-1)
                printf(", ");
        }
        printf(")\n         vet2 = (");
        for(j = 0; j < qtd_elementos[i]; j++) {
            printf("%.1lf", vet2[i][j]);
            if (j < qtd_elementos[i]-1)
                printf(", ");
        }
        printf(")\n");
        printf("         Valor obtido: %lf\n         Valor esperado: %lf +/-0.01\n", resp, produto_esperado[i]);
    }
    return corretos;
}


int main() {
    char opcao;
    printf("Executar testes? (S/N): ");
    #if COLAB
        opcao = 's';
    #else
        scanf("%c", &opcao);
    #endif
    if (opcao == 's' || opcao == 'S') {
        double nota = 0;
        nota += test_converter_minusculo();
        nota += test_tokenize();
        nota += (test_carregar_termos() * 3);
        nota += test_tf();
        nota += test_idf();
        nota += test_similaridade_cosseno();
        nota = (nota/18.0)*10.0;
        printf("\nNOTA FINAL DA ATIVIDADE (0 a 10): %.1lf\n", nota);
    } else {
        char documentos[NUM_DOCS][TAMANHO_MAX] = {
            "A inteligencia artificial esta revolucionando diversas industrias",
            "O aprendizado de maquina e uma subarea da inteligencia artificial",
            "Os algoritmos de busca ajudam a encontrar informacoes relevantes na web.",
            "A linguagem de programacao Python e amplamente usada para ciencia de dados",
            "O processamento de linguagem natural permite a comunicacao entre humanos e maquinas",
            "Grandes volumes de dados exigem tecnicas eficientes (bons algoritmos) de analise",
            "Os avancos em redes neurais profundas tem melhorado a precisao de modelos de IA",
            "A criptografia e fundamental para garantir a seguranca na comunicacao digital.",
            "Sistemas embarcados sao usados em dispositivos com recursos computacionais limitados.",
            "A computacao em nuvem permite o armazenamento e processamento de dados remotamente",
            "O paradigma de programacao orientado a objetos organiza o codigo em classes e objetos",
            "C e um exemplo de linguagem do paradigma imperativo!",
            "No paradigma funcional, funcoes PURAS sao o principal bloco de construcao dos programas",
            "Programas em Lisp seguem o paradigma funcional e sao usados em inteligencia artificial",
            "O paradigma logico, como visto na linguagem Prolog, se baseia em regras e fatos.",
            "A linguagem Java e amplamente usada no desenvolvimento de sistemas orientados a objetos.",
            "Uma linguagem orientada a objetos, como Java, promove o reuso de codigo e a modularidade?",
            "Um compilador traduz codigo-fonte de linguagens de alto nivel para linguagem de maquina.",
            "Automatos finitos sao usados para modelar sistemas com um numero limitado de estados",
            "Gramaticas livres de contexto sao fundamentais para a construcao de compiladores"
        };
        ListaTermos lista_termos[NUM_DOCS];
        long qtd_documentos = NUM_DOCS;
        int i, j, k;

        // Processamento inicial dos documentos: converte para letras minúsculas sem caracteres especiais e separa os tokens
        for(i = 0; i < qtd_documentos; i++) {
            converter_minusculo(documentos[i]);
            tokenize(lista_termos[i].termos, &lista_termos[i].qtd_termos, documentos[i]);
        }

        // Carrega os termos únicos dos documentos
        char termos[MAX_TERMOS][TAMANHO_MAX];
        int qtd_termos;
        carregar_termos(lista_termos, qtd_documentos, termos, &qtd_termos);

        // Calcula o tf-idf dos documentos
        double tf_idf_docs[NUM_DOCS][MAX_TERMOS];
        for(i = 0; i < qtd_documentos; i++) {
            for(j = 0; j < qtd_termos; j++) {
                int valor_tf = tf(termos[j], lista_termos[i]);
                double valor_idf = idf(termos[j], lista_termos, qtd_documentos);
                tf_idf_docs[i][j] = valor_tf * valor_idf;
            }
        }

        // Lê a string de pesquisa
        char string_busca[TAMANHO_MAX];
        double tf_idf_busca[MAX_TERMOS];
        printf("Digite a string de busca: ");
        scanf(" %150[^\n]", string_busca); // lê qualquer caractere que não seja \n. O espaço na frente faz com que o scanf não considere o último ENTER.

        ListaTermos lista_busca;
        tokenize(lista_busca.termos, &lista_busca.qtd_termos, string_busca);

        // Calcula o tf-idf da string de busca
        for (int j = 0; j < qtd_termos; j++) {
            int valor_tf = tf(termos[j], lista_busca);
            double valor_idf = idf(termos[j], lista_termos, qtd_documentos);
            tf_idf_busca[j] = valor_tf * valor_idf;
        }

        // Restaura os espaços nos documentos: deve ser usado no fim do programa, quando não for mais necessário usar tokenize()
        for(i = 0; i < qtd_documentos; i++) {
            for(j = TAMANHO_MAX-1; documentos[i][j] == '\0'; j--); // for sem bloco
            for(k = 0; k < j; k++) {
                if (documentos[i][k] == '\0')
                    documentos[i][k] = ' ';
            }
        }

        // Calcula a similaridade entre a string de pesquisa e cada documento
        double maior_similaridade = 0.0;
        int i_melhor_doc = -1;
        printf("Comparando os documentos existentes\n");
        for (int i = 0; i < qtd_documentos; i++) {
            double similaridade = similaridade_cosseno(tf_idf_docs[i], tf_idf_busca, qtd_termos);
            if (similaridade > maior_similaridade) {
                maior_similaridade = similaridade;
                i_melhor_doc = i;
            }
            printf(" * documentos[%d]: \"%s\"\n     Similaridade: %lf;  Maior similaridade ate aqui: %lf\n", i, documentos[i], similaridade, maior_similaridade);
        }

        // Mostra o resultado
        if (i_melhor_doc != -1)
            printf("\nO documento mais próximo é: \"%s\"\n", documentos[i_melhor_doc]);
        else
            printf("\nNenhum documento correspondente foi encontrado!\n");
    }
    return 0;
}


