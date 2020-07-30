  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 11

typedef struct sHashNode {
  struct sHashNode *next;
  struct sHashNode *prev;
  int ascii;
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
void printFirstBucket(Keys* keys);

/*QUICK SORT*/

HashNode* partition(HashNode *l, HashNode *h);
// void swap ( int* a, int* b, char * nameA, char * nameB) ;
void swap ( int* a, int* b, HashNode * A, HashNode * B ) ;
void _quickSort(HashNode* l, HashNode *h);
void quickSort(Hashbucket *hb);

int main() {
  int size = M;

  Keys* keys = createKeys(size);

  handleFile(keys);

  printFirstBucket(keys);

  quickSort(keys->head);
  
  printFirstBucket(keys);


  freeLists(keys);
  // printf("Front : %s\n", keys->head->front->name);
  // printf("Second : %s\n", keys->head->front->next->name);
  // swap(&(keys->head->front->ascii),&(keys->head->front->next->ascii), keys->head->front, keys->head->front->next);
  // printf("\n\nFront : %s\n", keys->head->front->name);
  // printf("Second : %s\n", keys->head->front->next->name); 
  // quickSort(keys->head);
  // printf("\n\n\nDEPOIS:\n");
  // printFirstBucket(keys);
  return 1;
}

void insert(Keys* keys, char* name){
  int asciiValue = charToAscii(name);
  int hashed = hash(asciiValue);

  // printf("\n%d", hashed);


  Hashbucket* aux = keys->head;
  
  for(int i = 0 ; i < M ; i++){
    if(hashed == aux->bucketIndex) {
      //aqui será inserido
      if(aux->size == 0)  {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));
        // hn->name = (char *)malloc(sizeof(name));
        // char new[20] ;
        char* new = (char*)malloc(sizeof(char) * 40 + 1);
        strcpy(new, name);

        hn->name = new;
        hn->ascii = asciiValue;

        
        aux->front = hn;
        aux->tail = hn;

        aux->size++;
      }else {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));
        // strcpy(hn->name, name);
        // hn->name = name;

        // hn->name = name;
        char* new = (char*)malloc(sizeof(char) * 40 + 1);
        strcpy(new, name);

        hn->name = new;
        hn->ascii = asciiValue;

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


Keys* createKeys(int size){
  Keys* keys = (Keys*)malloc(sizeof(Keys));
  keys->size = size -1;

  Hashbucket* hb = (Hashbucket*)malloc(sizeof(Hashbucket));
  // HashNode* hn = (HashNode*)malloc(sizeof(HashNode));

  hb->bucketIndex = 0;
  hb->size = 0;
  // hb->front = hn;
  // hb->tail = hn;
  keys->head = hb;
  keys->tail = hb;
  keys->size = 1;

  Hashbucket* aux = hb;

  for(int i = 1; i < M; i++) {
    Hashbucket* newHashBucket = (Hashbucket*)malloc(sizeof(Hashbucket));
    // HashNode* newHashNode = (HashNode*)malloc(sizeof(HashNode));
    if(i == 1 ){
      aux->next = newHashBucket;
      newHashBucket->prev = hb;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      // newHashBucket->front = newHashNode;
      // newHashBucket->tail = newHashNode;
      aux = newHashBucket;
    }else if(i == size) {
      aux->next = newHashBucket;
      newHashBucket->prev = aux;
      newHashBucket->next = NULL;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      // newHashBucket->front = newHashNode;
      // newHashBucket->tail = newHashNode;
      keys->tail = newHashBucket;

      free(aux);
    }else {
      aux->next = newHashBucket;

      newHashBucket->prev = aux;
      newHashBucket->size = 0;
      newHashBucket->bucketIndex = i;
      // newHashBucket->front = newHashNode;
      // newHashBucket->tail = newHashNode;
      aux = newHashBucket;
    }

  }

  return keys;
}

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

void printFirstBucket(Keys* keys){
  Hashbucket* hb = keys->head;
  HashNode* aux = hb->front;
  int qtd = 0;
  for(int i= 0; i< hb->size; i++){
    printf("\n%d    ", aux->ascii);
    printf("%s", aux->name);

    qtd++;
    aux = aux->next;
  }

  printf("\nQTD: %d", qtd);
  
}

int charToAscii(char* name) {
  return (int) name[0];
}

int hash(int asciiValue) {
  return asciiValue % M;
}

void handleFile(Keys* keys){
  size_t line_size = 30;

  char* path = "nomes.txt";
  FILE* file = fopen(path, "r");

  char *line = (char*)malloc(sizeof(char)*line_size+1);
  int i =0;

  while(getline(&line, &line_size, file) > 0){
    if(i == 1000) {
      break;
    }
    insert(keys, line);  
    i++;
  }

  if (line)
    free(line);

  fclose(file);

} 

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

void quickSort(Hashbucket *hb) { 
    // Find last node 
    HashNode *h = hb->tail; 
    HashNode *head = hb->front;

    _quickSort(head, h); 
}

void _quickSort(HashNode* l, HashNode *h) { 
    if (h != NULL && l != h && l != h->next){ 
        HashNode *p = partition(l, h); 
        _quickSort(l, p->prev); 
        _quickSort(p->next, h); 
    } 
} 

HashNode* partition(HashNode *l, HashNode *h) { 
    int x = h->ascii; 
    HashNode *i = l->prev; 
  
    for (HashNode *j = l; j != h; j = j->next){ 
      if (j->ascii <= x){ 
        i = (i->ascii < 0 || i->ascii > 121) ? l : i->next; 

        swap(&(i->ascii), &(j->ascii), i, j); 
      } 
    } 
    i = (i->ascii < 0 || i->ascii > 200) ? l : i->next; // Similar to i++ 
    swap(&(i->ascii), &(h->ascii), i, h); 
    return i; 
} 


void swap ( int* a, int* b, HashNode * A, HashNode * B ) { 
  int t = *a; *a = *b; *b = t;

  char* auxA = (char*)malloc(sizeof(char) * 40 + 1);
  char* auxB = (char*)malloc(sizeof(char) * 40 + 1);
  strcpy(auxA, A->name);
  strcpy(auxB, B->name);
  free(A->name);
  free(B->name);
  A->name = auxB;
  B->name = auxA;

  // free(A->);
  


} 


