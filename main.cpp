  
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

int main() {
  int size = 41;

  Keys* keys = createKeys(size);

  printf("%d", keys->size);

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

  for(int i = 1; i<=size; i++) {
    Hashbucket* hb1 = (Hashbucket*)malloc(sizeof(Hashbucket));

    if(i == 1 ){
      hb->next = hb1;
      hb1->prev = hb;
      hb1->size = 0;
      hb1->bucketIndex = i;
      aux = hb1;
    }else if(i == size) {
      aux->next = hb1;

      hb1->prev = aux;
      hb1->next = NULL;
      hb1->size = 0;
      hb1->bucketIndex = i;

      keys->tail = hb1;

      free(aux);
    }else {
      aux->next = hb1;

      hb1->prev = aux;
      hb1->size = 0;
      hb1->bucketIndex = i;

      aux = hb1;
    }

    keys->size += 1;
  }

  return keys;
}