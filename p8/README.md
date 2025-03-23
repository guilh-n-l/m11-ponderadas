# Tradução Automática e o Conjunto de Dados

Este notebook implementa um estudo de caso de Tradução Automática e o Conjunto de Dados, utilizando o conjunto de dados do Projeto Tatoeba, que contém sentenças paralelas em inglês e japonês. O objetivo deste estudo é construir um pipeline para pré-processamento de texto, tokenização, obtenção de vocabulário e treinamento de um modelo de tradução automática.

## Download e pré-processamento do conjunto de dados do Projeto Tatoeba
Primeiramente, foi feito download e extração do conjunto de dados do projeto Tatoeba. Esse projeto consiste na compilação de traduções diretas de inúmeras frases de um idioma para outro.

## Pré-processamento

A função`preproc` foi definida para limpar as sentenças, removendo espaços extras, convertendo para minúsculas e adicionando espaços em torno de pontuações específicas (como 。 ou 、). Este passo é importante porque facilita a tokenização, que é a divisão do texto em palavras significativas.

A função `tokenize` usa a expressão regular \S+ para dividir as sentenças em tokens (palavras) que são não-espaços. Essa abordagem é comum em idiomas como o inglês, onde os espaços são delimitadores naturais de palavras. Para o japonês, a tokenização pode ser mais desafiadora, como discutido na segunda pergunta, que será respondida posteriomente no notebook.

## Obtenção do dataset para treinamento

Nessa seção foram definidas algumas funções importantes para produzir um dataset tensorflow, que pode ser utilizado para a criãção de modelos de AI para tradução direta. Abaixo está a descrição das funções definidas:

- A função `get_vocab` gera uma lista de palavras únicas, ordenadas, a partir das sentenças em inglês e japonês.
- A função `get_indices` converte as palavras das sentenças em índices, associando cada palavra a um número específico, com a introdução de tokens especiais (`<PAD>` e `<UNK>`).
- A função `pad_trunc` usa a função pad_sequences do Keras para garantir que todas as sentenças tenham o mesmo tamanho (definido por `MAX_LEN`), adicionando preenchimento (PAD) ou cortando as sentenças muito longas.
- A função `load_data_nmt` organiza os dados em lotes (batch) para treinamento de modelos de tradução automática, e retorna o dataset pré-processado, pronto para ser usado com TensorFlow.

# Respondendo perguntas

> Tente valores diferentes do argumento num_examples na funçãoload_data_nmt. Como isso afeta os tamanhos do vocabulário do idioma de origem e do idioma de destino?

RES: Se você passar um número menor de exemplos (por exemplo `num_examples = 200`), o vocabulário será menor, pois menos palavras únicas estarão presentes. O efeito contrário acontece se são passados mais exemplos.

> O texto em alguns idiomas, como chinês e japonês, não tem indicadores de limite de palavras (por exemplo, espaço). A tokenização em nível de palavra ainda é uma boa ideia para esses casos? Por que ou por que não?

RES: Nesses idiomas, as palavras não são separadas por espaços. Isso dificulta a tokenização em nível de palavra. O processo precisa segmentar os caracteres em palavras significativas. Para isso, seria necessário usar algum outro tipo de biblioteca. Entretanto, como visto no notebook, separar usando espaços com línguas como o japonês ainda é possivel, ainda que o resultado da tokenização seja menos preciso.
