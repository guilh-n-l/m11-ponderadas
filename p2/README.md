# Tradutor Neural de Máquinas Usando Transformers

Este projeto implementa um sistema de tradução usando a arquitetura Transformer, especificamente projetado para traduzir texto de Português (PT) para Inglês (EN). O modelo é treinado com o dataset "ted_hrlr_translate/pt_to_en" do TensorFlow Datasets e aproveita o poder dos mecanismos de autoatenção para obter traduções de alta qualidade.

## Características

- **Arquitetura Transformer**: Utiliza o modelo Transformer de ponta, que inclui autoatenção multi-cabeça, codificação posicional e camadas feedforward.
- **Tokenizer Personalizado**: Emprega um tokenizer pré-treinado para tradução de Português para Inglês para pré-processar e tokenizar sequências de entrada.
- **Pipeline de Dados Eficiente**: Implementa as otimizações do pipeline de dados do TensorFlow.
- **Treinamento em GPU**: Otimizado para aceleração em GPU para acelerar o processo de treinamento.
- **Pipeline de Inferência**: Inclui uma classe `Translator` para realizar traduções utilizando o modelo treinado.

## Conclusões pessoais

- Pontos positivos:
    - Aprendizado sobre a arquitetura de transformers.
    - Modelo portátil e relativamente leve que pode ser usado em diversas situações.
- Pontos negativos:
    - Necessidade de alto poder computacional para treinos (Isso ocasionou um tempo de treino reduzido e consequentemente uma queda na qualidade do produto final)
    - Tempo de treinamento: O tempo de treinamento é bastante extenso, dificultando o processo de fine-tuning e tweaking do modelo.

## Créditos

[Tensorflow transformer tutorial](https://www.tensorflow.org/text/tutorials/transformer)
