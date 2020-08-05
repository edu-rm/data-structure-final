  
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
void sortBucket(int, Keys*);
void swap (HashNode*, HashNode*) ;
void quickSortAlgorithm(HashNode*, HashNode*, int);
void quickSort(Hashbucket*);
void quickSubLetters(HashNode*, Hashbucket*, int);
void search(Keys*, char*);
void delete(Keys*, char*);
void removeStringTrailingNewline(char*);

int main() {
  system("cls");
  int size = M;
  int option = 0;
  int bucket = 0;
  int menuController = 0;
  char newName[25];
  char nameSearch[25];
  char deleteName[25];

  Keys* keys = createKeys(size);
  printf("CARREGANDO ARQUIVO...\n");
  handleFile(keys);
  printf("CARREGADO COM SUCESSO\n");

  for(;;) {
    // system("cls");
    printf("\n\n\n------------------TABELA HASH E QUICKSORT EM C------------------\n");
    printf("\n[1] INSERIR\n[2] ORDENAR E IMPRIMIR\n[3] DELETAR\n[4] PESQUISAR\n[5] IMPRIMIR QUANTIDADE DE NOMES POR BUCKET\n[6] SAIR\n");

	  scanf("%i", &option);

    switch(option) {
      case 1 : {
        printf("\nDIGITE O NOME A SER INSERIDO:  ");
        scanf("%s", &newName);
        insert(keys, newName);
        printf("\n%s inserido com sucesso\n", newName);
        break;
      }
       case 2 : {
        printf("\nDIGITE QUAL O BUCKET QUE VOCE DESEJA ORDENAR E EXIBIR:  ");
    	  scanf("%i", &bucket);
        sortBucket(bucket, keys);
        break;
      }
      case 3 : {
        printf("\nDIGITE O NOME A SER DELETADO:  ");
        scanf("%s", &deleteName);
        delete(keys, deleteName);
        break;
      }
      case 4 : {
        printf("\nDIGITE O NOME A SER PESQUISADO:  ");
        scanf("%s", &nameSearch);
        // getchar();
        search(keys, nameSearch);
        break;

      }
      case 5 : {
        printKeys(keys);
        break;
      }
      case 6 : {
        system("cls");
        freeLists(keys);
        exit(0);
        break;
      }
    }

  }

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
  int string_len = strlen(name);
  for(int i = 0 ; i < M ; i++){
    if(hashed == aux->bucketIndex) {
      //aqui será inserido
      if(aux->size == 0)  {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));
        // char* new = (char*)malloc(sizeof(char) * 40 + 1);

        char* new = (char*)malloc(sizeof(char)* string_len+2);
        strcpy(new, name);

        hn->name = new;
        hn->next = NULL;
        hn->prev = NULL;  
        aux->front = hn;
        aux->tail = hn;

        aux->size++;
      }else {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));

        // char* new = (char*)malloc(sizeof(char) * 40 + 1);
        char* new = (char*)malloc(sizeof(char)* string_len+2);
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
      for(int l = 0; l < aux->size; l++) {
        qtd++;
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
    printf("%s\n", aux->name);
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
  int ascii = 0;
  if(name[0] >= 0 ||name[0] <= 121  ){
    ascii += (int) name[0];
  }
  if(name[1] >= 0 ||name[1] <= 121  ){
    ascii += (int) name[1];
  }
  if(name[2] >= 0 ||name[2] <= 121  ){
    ascii += (int) name[2];
  }
  if(name[3] >= 0 ||name[3] <= 121  ){
    ascii += (int) name[3];
  }
  if(name[4] >= 0 ||name[4] <= 121  ){
    ascii += (int) name[4];
  }
  return (int) (ascii);
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
  size_t line_size = 40;

  char* path = "nomes.txt";
  FILE* file = fopen(path, "r");

  char *line = (char*)malloc(sizeof(char)*line_size+1);
  int i =0;

  while(getline(&line, &line_size, file) > 0){
    if(i == 100788) {
      break;
    }
    removeStringTrailingNewline(line);
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
  int string_lenA = strlen(A->name);
  int string_lenB = strlen(A->name);


  char* auxA = (char*)malloc(sizeof(char) * string_lenA + 2);
  char* auxB = (char*)malloc(sizeof(char) * string_lenB + 2);

  strcpy(auxA, A->name);
  strcpy(auxB, B->name);
  free(A->name);
  free(B->name);
  A->name = auxB;
  B->name = auxA;
} 

/**
 *  FUNÇÃO PARA PESQUISAR UM NOME
 */

void search(Keys* keys, char* name){
  int asciiValue = charToAscii(name);
  int hashed = hash(asciiValue);

  Hashbucket* aux = keys->head;

  for(int i = 0; i< M; i++) {
    if(aux->bucketIndex == hashed) {
      printf("\nPESQUISANDO NO BUCKET %i", aux->bucketIndex);
      HashNode* hn = aux->front;

      for(int i = 0; i < aux->size; i++) {
        int value = strcmp(name, hn->name);


        if(value == 0) {
          printf("\n%s", hn->name);
          return;
        }
       
        hn= hn->next;
      }
      break;
    }
    aux= aux->next;
  }
  printf("\nESSE NOME NAO EXISTE.\n");
}

/**
 *  FUNÇÃO PARA DELETAR UM NOME
 */

void delete(Keys* keys, char* name){
  int asciiValue = charToAscii(name);
  int hashed = hash(asciiValue);

  Hashbucket* aux = keys->head;

  for(int i = 0; i< M; i++) {
    if(aux->bucketIndex == hashed) {
      HashNode* hn = aux->front;

      for(int i = 0; i < aux->size; i++) {
        int value = strcmp(name, hn->name);
        if(value == 0) {
          HashNode* toDelete = hn;
          printf("\n%s", hn->name);
          hn->prev->next = hn->next;
          hn->next->prev = hn->prev;
          aux->size -= 1;
          free(toDelete);
          printf("\n%s deletado com sucesso\n", name);
          return;
        }
        hn= hn->next;
      }
      break;
    }
    aux= aux->next;
  }
  printf("\nFALHA AO DELETAR\n");
}

/**
 *  FUNÇÃO UTILITÁRIA PARA REMOVER \n DO FINAL DE UMA STRING
 */

void removeStringTrailingNewline(char *str) {
  if (str == NULL)
    return;

  int length = strlen(str);

  if (str[length-1] == '\n')
    str[length-1]  = '\0';
}
