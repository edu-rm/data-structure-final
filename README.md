# Trabalho final de Estrutura de Dados I

## Metodologia Usada.

Foi usado a estrutura de dados do tipo Hash para se fazer a inserção dos 100788 nomes e a colisão foi tratada automaticamente pelo conceito de encadeamento. Para o armazenamento de dados foi criado várias listas duplamente encadeadas.

![esquema](https://user-images.githubusercontent.com/37454606/89684688-57249080-d8d1-11ea-905f-d163f80707cf.png)

Keys: estrutura que vai servir unicamente para armazenar o Head e o Tail da lista encadeada de Buckets para a finalidade de iteração.

Buckets: lista duplamente encadeada que possui bucketIndex, e o head e o tail de uma lista de armazenamento de nomes.
- bucketIndex: Número do bucket, é esse atributo que torna cada bucket único.

Nomes: são várias estruturas duplamente encadeadas, cada uma é associada a um bucket, será responsável pelo armazenamento de todos os nomes que são distribuídos para seu respectivo pai.

### Problema e suas variáveis

O N do problema é 100788 e o M escolhido foi de 23. O número 23 foi acatado por ser primo e proporcionar uma boa quantidade de informações por chave.

### Função Espalhadora

A função de hash escolhida foi do tipo modular “valor % 23”: a variável valor vai ser dada pela soma do valor em ASCII das primeiras 5 letras se estas existirem no nome. Se um nome possuir menos que 5 letras, a soma será feita apenas pela quantidade total de letras presente nele.

### Representação gráfica da performance da função hash

A soma das primeiras 5 letras aplicada na função hash com um M de 23, apresentou um ótimo resultado como podemos ver no historiograma abaixo:

![historiograma](https://user-images.githubusercontent.com/37454606/89685023-e6ca3f00-d8d1-11ea-8f58-6deeb90912ad.png)

### Manipulações de strings.

A resolução do problema envolveu bastante manipulação de string, e para isso foi utilizado o arquivo do C chamado string.h além de outras funções utilitárias. 
- Foi usado a função strcpy para a função swap (utilizada para fazer a troca de nomes no quicksort) e para o armazenamento dos nomes.
- A função strcmp do string.h também foi usada para facilitar a pesquisa e a remoção de nomes.
- Foi necessária a criação da função removeStringTrailingNewline para remover nova linha no final de cada nome, pois o método utilizado para iterar o arquivo linha a linha deixava um “\n” ao final de cada string, e com isso as pesquisas não funcionavam. 

### Ordenação

É possível fazer a ordenação de qualquer bucket que o usuário final desejar, isso foi possível com o uso do quicksort. É importante salientar que ele não foi aplicado em um array, mas sim em uma lista duplamente encadeada, e com isso veio a necessidade de adaptação. Após algumas horas de trabalho foi possível ordenar alfabeticamente os nomes, mas considerando apenas a primeira letra.

O próximo desafio foi ordenar os nomes já ordenados, ou seja, ordenar esses nomes considerando as letras seguintes.

A construção da solução se deu através seguinte raciocínio: os nomes já estão ordenados de uma forma geral, mas desta vez é preciso dividir os nomes em conjuntos por letra precedente a da ordenação que está sendo feita no momento.

![qs](https://user-images.githubusercontent.com/37454606/89685245-5a6c4c00-d8d2-11ea-95e3-e703b7a0f058.jpg)

As marcações em vermelho representam o agrupamento por letras, quando esses limites forem achados será chamado o método quicksort passando como atributo a posição da letra atual mais um, ou seja, a posição da letra atual na foto é 0 mas onde realmente tem de ocorrer a ordenação é na posição 1.

O nome dessa função no código é quickSubLetters. É uma função recursiva que serve simplesmente para achar a divisão de letras e então poder chamar o quicksort, isso possibilita a ordenação de letras em uma camada mais profunda (segunda, terceira, e assim por diante)

Como é sabido, a função recursiva chama ela mesma, e essa função chamará ela mesma em três ocasiões diferentes:

- Quando é encontrada a divisão de letras precedentes, então é preciso passar o ponteiro para a próxima letra de mesmo nível.
- Junto com a ocasião anterior, só que dessa vez passando o mesmo conjunto em um nível mais baixo, isso torna possível a ordenação das próximas letras.
- E quando há um caso especial em que o ponteiro aux é nulo, significando que o algoritmo está lidando com a extremidade da lista. Esse caso precisou ser especificado pois os anteriores possuem condições que divergem das necessárias por ele.

A condição de parada é quando letra == 2. Na prática isso significa que será parada a execução quando o array ja está ordenado em 3 níveis.
