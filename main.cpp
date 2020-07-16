  
#include <stdio.h>
#include <stdlib.h>

typedef struct sHashNode {
  struct sHashNode *next;
  struct sHashNode *prev;

  int name;
} HashNode;

typedef struct sHashBucket {
  struct sHashNode *head;
  struct sHashNode *tail;
  int index;
  int bucketSize;
} Hashbucket;

typedef struct sKeys {
  struct sHashBucket *head;
  struct sHashBucket *tail; 
  int size;
} Keys;

int main() {
  Keys* keys = (Keys*)malloc(sizeof(Keys));
  keys->size = 41;

  printf("%i", keys->size );


  return 1;
}