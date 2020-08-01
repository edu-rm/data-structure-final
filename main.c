  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 11

typedef struct sHashNode {
  struct sHashNode *next;
  struct sHashNode *prev;
  char* name;
} HashNode;

typedef struct sHashBucket {
  struct sHashBucket *next;
  struct sHashBucket *prev;

  struct sHashNode *front;
  struct sHashNode *tail;

  int bucketIndex;
  int size;
} Hashbucket;

typedef struct sKeys {
  struct sHashBucket *head;
  struct sHashBucket *tail; 
  int size;
} Keys;

Keys* createKeys(int);
void printKeys(Keys*);
int hash(int);
int charToAscii(char*);
void insert(Keys*, char*);
void handleFile(Keys*);
void freeLists(Keys*);
void printBucket(Hashbucket*);

/*QUICK SORT*/

HashNode* partition(HashNode*, HashNode*, int);
void sortBucket(int bucket, Keys*);
void swap ( HashNode*, HashNode*) ;
void quickSortAlgorithm(HashNode*, HashNode*, int);
void quickSort(Hashbucket*);
void quickSubLetters(HashNode*, Hashbucket*, int);


int main() {
  int size = M;
  int option;
  int menuController = 0;


  Keys* keys = createKeys(size);
  printf("CARREGANDO NOMES DOS ARQUIVOS NA ESTRUTURA HASH\n");
  handleFile(keys);
  printf("------ CARREGADO COM SUCESSO ------\n");
  printKeys(keys);
  sortBucket(0, keys);
  // sortBucket(1, keys);
  // sortBucket(2, keys);
  // sortBucket(3, keys);
  // sortBucket(4, keys);
  // sortBucket(5, keys);
  // sortBucket(6, keys);
  // sortBucket(7, keys);
  // sortBucket(8, keys);
  // sortBucket(9, keys);
  // sortBucket(10, keys);
  // sortBucket(11, keys);
  // sortBucket(0, keys);
  freeLists(keys);
  return 1;
}

/**
 *  FUNÇÃO PARA CRIAR UMA ESTRUTURA DE HASH BASEADA NO TAMANHO M
 */

Keys* createKeys(int size){
  Keys* keys = (Keys*)malloc(sizeof(Keys));
  keys->size = size -1;

  Hashbucket* hb = (Hashbucket*)malloc(sizeof(Hashbucket));

  hb->bucketIndex = 0;
  hb->size = 0;
  keys->head = hb;
  keys->tail = hb;
  keys->size = 1;

  Hashbucket* aux = hb;

  for(int i = 1; i < M; i++) {
    Hashbucket* newHashBucket = (Hashbucket*)malloc(sizeof(Hashbucket));
    if(i == 1 ){
      aux->next = newHashBucket;
      newHashBucket->prev = hb;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      aux = newHashBucket;
    }else if(i == size) {
      aux->next = newHashBucket;
      newHashBucket->prev = aux;
      newHashBucket->next = NULL;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      keys->tail = newHashBucket;
      free(aux);
    }else {
      aux->next = newHashBucket;

      newHashBucket->prev = aux;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      aux = newHashBucket;
    }

  }

  return keys;
}

/**
 *  FUNÇÃO PARA INSERIR UM NOME NA ESTRUTURA HASH CRIADA 
 */

void insert(Keys* keys, char* name){
  int asciiValue = charToAscii(name);
  int hashed = hash(asciiValue);

  Hashbucket* aux = keys->head;
  
  for(int i = 0 ; i < M ; i++){
    if(hashed == aux->bucketIndex) {
      //aqui será inserido
      if(aux->size == 0)  {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));

        char* new = (char*)malloc(sizeof(char) * 40 + 1);
        strcpy(new, name);

        hn->name = new;
        hn->next = NULL;
        hn->prev = NULL;  
        aux->front = hn;
        aux->tail = hn;

        aux->size++;
      }else {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));

        char* new = (char*)malloc(sizeof(char) * 40 + 1);
        strcpy(new, name);

        hn->name = new;
        hn->next = NULL;  
        hn->prev = aux->tail;

        aux->tail->next = hn;
        aux->tail = hn;

        aux->size++;
      }
      break;
    }else {
      aux = aux->next;
    }
  }

}

/**
 *  FUNÇÃO UTILITÁRIA PARA ORDENAR E EXIBIR O BUCKET X 
 */

void sortBucket(int bucket, Keys * keys) {
    Hashbucket* aux = keys->head;

    for(int i = 0 ; i <= bucket; i++){
      if(i == bucket) {
        quickSort(aux);
        printBucket(aux);
        break;
      }
      aux= aux->next;
    }
}

/**
 *  FUNÇÃO UTILITÁRIA PARA EXIBIR TODOS OS BUCKETS E SEUS RESPECTIVOS TAMANHOS
 */

void printKeys(Keys * keys) {
  Hashbucket *aux; 
  HashNode *nodeAux;  
  int qtd =0;
  aux=keys->head;

  for(int i = 0; i <= M-1 ; i++){
    printf("\n%d -> ",aux->bucketIndex);
    printf("%d\n",aux->size); 

    if(aux->size > 0) {
      nodeAux = aux->front;
      // printf("%D",nodeAux->);
      for(int l = 0; l < aux->size; l++) {
      //   printf(nodeAux->name);
        qtd++;
      //   nodeAux = nodeAux->next;
      }
    }
   
    printf("\n\n");
    aux=aux->next;
  }
  printf("\nQTD TOTAL: %d",qtd);
}

/**
 *  FUNÇÃO UTILITÁRIA IMPRIMIR O BUCKET PASSADO 
 */

void printBucket(Hashbucket* hb){
  HashNode* aux = hb->front;
  int qtd = 0;
  for(int i= 0; i< hb->size; i++){
    // printf("\n%d    ", aux->ascii);
    printf("%s", aux->name);
    qtd++;
    aux = aux->next;
  }

  printf("\nQTD: %d", qtd);
  printf("\n\n\n\n");
  
}

/**
 *  FUNÇÃO UTILITÁRIA PARA GERAR A SOMA DOS VALORES ASCII DAS 4 PRIMEIRAS LETRAS DE CADA NOME
 */

int charToAscii(char* name) {
  return (int) (name[0]+name[1]+name[2]+name[3]+name[4]);
}

/**
 *  FUNÇÃO HASH MODULAR (RESTO DA DIVISÃO POR M) 
 */

int hash(int asciiValue) {
  return asciiValue % M;
}

/**
 *  FUNÇÃO UTILITÁRIA PARA ABRIR E ITERAR AS LINHAS DO ARQUIVO DE DADOS 
 */

void handleFile(Keys* keys){
  size_t line_size = 30;

  char* path = "nomes.txt";
  FILE* file = fopen(path, "r");

  char *line = (char*)malloc(sizeof(char)*line_size+1);
  int i =0;

  while(getline(&line, &line_size, file) > 0){
    if(i == 100788) {
      break;
    }
    insert(keys, line);  
    i++;
  }

  if (line)
    free(line);

  fclose(file);

} 

/**
 *  FUNÇÃO UTILITÁRIA PARA LIBERAR A MEMÓRIA DE TODAS AS LISTAS E SEUS ELEMENTOS
 */

void freeLists(Keys* keys) {
  Hashbucket *aux; 
  HashNode *nodeAux;  

  aux=keys->head;

  for(int i = 0; i < M ; i++){
    nodeAux = aux->front;

    for(int l = 0; l < aux->size; l++) {
      HashNode *freeNode = nodeAux ; 
      nodeAux = nodeAux->next;
      free(freeNode->name); 
      free(freeNode);
    }

    Hashbucket *freeHb = aux; 
    aux=aux->next;
    free(freeHb);
  }

  free(keys);
}

/**
 *  FUNÇÃO QUE GERENCIA A ORDENAÇÃO DE UM BUCKET
 */

void quickSort(Hashbucket *hb) { 
  HashNode *h = hb->tail; 
  HashNode *head = hb->front;

  head->prev =NULL;
  h->next = NULL;

  /*PRIMEIRA ORDENAÇÃO*/
  quickSortAlgorithm(head, h, 0);

  /* ORDENAÇÃO DE 2º AO 4º NÍVEL */
  quickSubLetters(hb->front, hb, 0);

}

/**
 *  FUNÇÃO QUE ORDENA BASEANDO-SE NO INICIO E FIM PASSADOS COMO PARÂMETRO
 */

void quickSortAlgorithm(HashNode* l, HashNode *h, int letter) { 
    if (h != NULL && l != h && l != h->next){ 
        HashNode *p = partition(l, h, letter); 
        quickSortAlgorithm(l, p->prev, letter); 
        quickSortAlgorithm(p->next, h, letter); 
    } 
} 

/**
 *  FUNÇÃO PARTIÇÃO DO METÓDO QUICKSORT
 */

HashNode* partition(HashNode *l, HashNode *h, int letter) { 
    int x = h->name[letter]; 
    HashNode *i = l->prev; 
  
    for (HashNode *j = l; j != h; j = j->next){ 

      if (j->name[letter] <= x){ 
        i = (i == NULL) ? l : i->next; 
        swap(i, j); 
      } 
    } 
    i = (i == NULL) ? l : i->next;

    swap(i, h); 
    return i; 
} 

/**
 *  FUNÇÃO RECURSIVA RESPONSÁVEL POR ORDENAR AS LETRAS PARTINDO DO 2º NIVEL, OU SEJA DA SEGUNDA LETRA DE UM AGLOMERADO
 */

void quickSubLetters(HashNode* start, Hashbucket* hb, int letter) {
  /*DADOS MUITO GRANDES NÃO FUNCIONAM COM UMA ORDENAÇÃO DE NÍVEL 4*/
  /*COMO ELE JA FOI ORDENADO UTILIZANDO A PRIMEIRA LETRA, O LETTER == 2 EQUIVALE AO 3 NÍVEL DE ORDENAÇÃO*/
  /*(1) + (LETTER = 0) + (LETTER = 1)  = NÍVEL 3*/

  /*OBS: COM UM M VALENDO 41 CONSIGO NO MEU COMPUTADOR RODAR A ORDENAÇÃO DE NÍVEL 4 EM PRATICAMENTE TODOS OS BUCKETS*/
  
  if(letter == 2) return;
  int flag =0;
  HashNode *h; 

  HashNode *head = start; 
  HashNode* aux = head;

  int anterior = head->name[letter];

  while(flag == 0) {  
      if(!(aux == NULL)){
        if(anterior != aux->name[letter]){
          quickSortAlgorithm(head, h, letter+1 );
          quickSubLetters(head, hb, letter+1);
          quickSubLetters(h->next, hb, letter);

          flag = 1;
        }else {
          h = aux;
          aux = aux->next;
        }   
    } else {
      quickSortAlgorithm(head, h, letter+1 );
      quickSubLetters(head, hb, letter+1);

      flag =1;
    }
  }
}

/**
 *  FUNÇÃO UTILITÁRIA RESPONSÁVEL POR TROCAR OS NOMES DE DOIS "LOCAIS" NA MEMÓRIA
 */

void swap (HashNode * A, HashNode * B ) { 
  char* auxA = (char*)malloc(sizeof(char) * 40 + 1);
  char* auxB = (char*)malloc(sizeof(char) * 40 + 1);

  strcpy(auxA, A->name);
  strcpy(auxB, B->name);
  free(A->name);
  free(B->name);
  A->name = auxB;
  B->name = auxA;
} 


