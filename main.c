  
#include <stdio.h>
#include <stdlib.h>

typedef struct sHashNode {
  struct sHashNode *next;
  struct sHashNode *prev;

  int name;
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
void printKeys(Keys * keys);
int hash(int);
int charToAscii(char* name);

int main() {
  int size = 41;
  Keys* keys = createKeys(size);

  // int value = charToAscii("Adi");


  printKeys(keys);

  return 1;
}


Keys* createKeys(int size){
  Keys* keys = (Keys*)malloc(sizeof(Keys));
  keys->size = 0;

  Hashbucket* hb = (Hashbucket*)malloc(sizeof(Hashbucket));
  hb->bucketIndex = 0;
  hb->size = 0;
  keys->head = hb;
  keys->tail = hb;
  keys->size = 1;

  Hashbucket* aux = hb;

  for(int i = 1; i <= size; i++) {
    Hashbucket* newHashBucket = (Hashbucket*)malloc(sizeof(Hashbucket));

    if(i == 1 ){
      hb->next = newHashBucket;
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

    keys->size++;
  }

  return keys;
}

void printKeys(Keys * keys) {
  Hashbucket *aux;  
  aux=keys->head;
  for(int i = 0; i < keys->size ; i++){
    printf("\n%d -> ",aux->bucketIndex);
    printf("%d\n",aux->size); 
    aux=aux->next;
  }
}

int charToAscii(char* name) {
  return (int) name[0];
}

int hash(int value) {
  return value % 41;
}

// int hash(int key) {
//   return key % 
// }

