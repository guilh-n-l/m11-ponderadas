# Análise e Previsão de Vendas de Café com Modelos de Machine Learning

Este notebook se concentra na análise e previsão das vendas de café de uma máquina de vendas automatizada, usando técnicas de Machine Learning para prever as vendas futuras de diferentes tipos de café.

O objetivo deste projeto é explorar um conjunto de dados de vendas de café, que contém informações diárias de transações desde março de 2024 até o momento presente, e criar modelos preditivos para estimar as vendas futuras.

## Compilando dados

Para este projeto, foi utilizado o conjunto de dados de vendas de café fornecido por Yaroslav Isaienkov no Kaggle. O dataset contém registros diários de transações de uma máquina de vendas de café, com dados coletados desde março de 2024 até o presente.

Os dados originais foram baixados diretamente do Kaggle, e o processamento foi feito com o objetivo de preparar os dados para modelos de séries temporais. Para garantir que o conjunto de dados fosse compatível com esses modelos, algumas transformações foram necessárias:

1. **Conversão para Formato Compatível com Séries Temporais**:
   - A coluna de **data** foi convertida para o formato `datetime` utilizando o método `pd.to_datetime()`. Essa conversão é essencial para trabalhar com séries temporais, pois permite a manipulação eficiente das datas.
   
1. **Agregação de Vendas por Mês**:
   - Para adaptar os dados a um formato mais adequado para modelagem preditiva, foi realizada uma agregação das vendas diárias para **vendas mensais**. Isso foi feito utilizando o `groupby` para agrupar os dados por data e tipo de café, seguido do `resample('ME')` para fazer a soma das vendas por mês.
   
1. **Filtragem dos Cafés Mais Populares**:
   - Para focar na análise dos cafés mais vendidos, selecionei os 6 tipos de café com maior volume de vendas, o que ajuda a reduzir a complexidade do modelo e melhora a qualidade das previsões.


Essas etapas garantiram que os dados estivessem no formato adequado para serem utilizados em modelos de séries temporais. O formato final foi uma tabela onde cada linha representa um mês, e cada coluna contém o número de vendas de um tipo de café específico.

### Dataset

This [dataset](https://www.kaggle.com/datasets/ihelon/coffee-sales) contains detailed records of coffee sales from a vending machine.
The vending machine is the work of a dataset author who is committed to providing an open dataset to the community.
It is intended for analysis of purchasing patterns, sales trends, and customer preferences related to coffee products.
Data Collection Period

The dataset spans from March 2024 to Present time, capturing daily transaction data. And new information continues to be added.

> Author: Yaroslav Isaienkov @ihelon

## Usando o modelo Prophet

O Prophet é um modelo de previsão de séries temporais desenvolvido pelo Facebook, projetado para lidar com séries temporais que possuem padrões sazonais e efeitos de feriados, além de permitir a manipulação de dados com lacunas e anomalias. O Prophet é especialmente útil quando os dados apresentam tendências e sazonalidades de longo prazo, o que é comum em muitos problemas de previsão, como vendas, clima e comportamento de usuários.

## Modelo de LSTM usando Keras

O LSTM (Long Short-Term Memory) é um tipo de rede neural recorrente (RNN) projetada para lidar com dados sequenciais, como séries temporais. Diferentemente das RNNs tradicionais, as LSTMs são capazes de aprender dependências de longo prazo, o que as torna ideais para tarefas em que o contexto de eventos passados pode influenciar eventos futuros. Isso é especialmente útil quando lidamos com dados temporais, como vendas de café, onde as tendências passadas podem fornecer informações importantes para prever as vendas futuras.

A métrica de loss utilizada no modelo LSTM (Long Short-Term Memory) foi a "mean squared error" (MSE). O MSE é uma medida que quantifica a diferença entre os valores reais (ou observados) e os valores preditos pelo modelo. Ele é calculado pela média dos quadrados das diferenças entre os valores previstos e os valores reais.

A motivação pela escolha dessa métrica está justamento no fato de que ela é altamente adequada para tarefas de regressão, que é o caso desse problema, onde o objetivo é prever valores contínuos, como as vendas mensais de diferentes tipos de café.
