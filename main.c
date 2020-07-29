  
#include <stdio.h>
#include <stdlib.h>
// #define _GNU_SOURCE

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


int main() {
  int size = 41;
  Keys* keys = createKeys(size);
  handleFile(keys);

  // char n1[] = "amanda";
  // char n2[] = "bruno";
  // char n3[] = "Carlos";
  // char n4[] = "Fabio";
  // char n5[] = "Gabriela";
  // char n6[] = "Heloisa";
  // char n7[] = "Igor";
  // char n8[] = "Yuri";
  // char n9[] = "Tiago";
  // char n10[] = "Kaio";
  // char n11[] = "kathleen";
  
  

  // insert(keys, n1);
  // insert(keys, n2);
  // insert(keys, n3);
  // insert(keys, n4);
  // insert(keys, n5);
  // insert(keys, n6);
  // insert(keys, n7);
  // insert(keys, n8);
  // insert(keys, n9);
  // insert(keys, n10);
  // insert(keys, n11);


  

  printKeys(keys);

  return 1;
}

void insert(Keys* keys, char* name){
  // se eu quero inserir algo, preciso saber em qual bucket esse algo se encaixa!
  int asciiValue = charToAscii(name);
  int hashed = hash(asciiValue);

  // printf("%d", hashed);


  Hashbucket* aux = keys->head;
  
  for(int i = 0 ; i < 41 ; i++){
    if(hashed == aux->bucketIndex) {
      //aqui será inserido
      if(aux->size == 0)  {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));
        hn->name = name;
        
        aux->front = hn;
        aux->tail = hn;

        aux->size++;
      }else {
        HashNode* hn = (HashNode*)malloc(sizeof(HashNode));
        hn->name = name;
        hn->prev = aux->tail;

        aux->tail->next = hn;
        aux->tail = hn;

        aux->size++;
      }
      break;
      // flag = 1;
    }else {
      aux = aux->next;
    }
  }

}


Keys* createKeys(int size){
  Keys* keys = (Keys*)malloc(sizeof(Keys));
  keys->size = 0;

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

  for(int i = 1; i <= size; i++) {
    Hashbucket* newHashBucket = (Hashbucket*)malloc(sizeof(Hashbucket));
    // HashNode* newHashNode = (HashNode*)malloc(sizeof(HashNode));


    if(i == 1 ){
      hb->next = newHashBucket;
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

    keys->size++;
  }

  return keys;
}

void printKeys(Keys * keys) {
  Hashbucket *aux; 
  HashNode *nodeAux;  

  aux=keys->head;

  for(int i = 0; i < keys->size ; i++){
    printf("\n%d -> ",aux->bucketIndex);
    printf("%d\n",aux->size); 

    // if(aux->size != 0) {
    //   nodeAux = aux->front;
    //   for(int l = 0; l<aux->size; l++) {
    //     printf("%s, ", nodeAux->name);
    //     nodeAux = nodeAux->next;
    //   }
    // }
   
    printf("\n\n");
    aux=aux->next;
  }
}

int charToAscii(char* name) {
  return (int) name[0];
}

int hash(int asciiValue) {
  return asciiValue % 41;
}

void handleFile(Keys* keys){
  size_t line_size = 20;

  char* path = "nomes.txt";
  FILE* file = fopen(path, "r");

  char *line = malloc(line_size);
  int i =0;

  while(getline(&line, &line_size, file) > 0){
    if(i == 100) {
      break;
    }
    // printf("%s", line);

    insert(keys, line);
    
    i++;
  }

  if (line)
    free(line);
  fclose(file);

} 
