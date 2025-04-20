#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
    if (map == NULL || key == NULL) return;
    long indice = hash(key, map->capacity);
    long copiaindice = indice;

    do
    {
        Pair * currentPair = map->buckets[indice];
        if (currentPair == NULL || currentPair->key == NULL)
        {
            Pair * nuevoPair = (Pair*) malloc(sizeof(Pair));
            if (nuevoPair == NULL) return;

            nuevoPair->key = key;
            nuevoPair->value = value;
            map->buckets[indice] = nuevoPair;
            map->size++;
            map->current = indice;
            return;
        }  
        if (currentPair->key != NULL && strcmp(currentPair->key, key) == 0) return;

        indice = (indice + 1) % map->capacity;
    } while (indice != copiaindice);
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap* mapa = (HashMap*) malloc(sizeof(HashMap));
    mapa->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);
    for (int i = 0; i < capacity; i++) {
        mapa->buckets[i] = NULL;
    }
    mapa->size = 0;
    mapa->capacity = capacity;
    mapa->current = -1;
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {

    long indice = hash(key, map->capacity);
    long copiaindice = indice;

    do {
        Pair *currentPair = map->buckets[indice];
        if(currentPair->key != NULL && strcmp(currentPair->key, key) == 0)
        {
            currentPair->key = NULL;
        }
        indice = (indice + 1) % map->capacity;

    } while(indice != copiaindice);

}

Pair * searchMap(HashMap * map,  char * key) {
    long indice = hash(key, map->capacity);
    long copiaindice = indice;

    do {
        Pair *currentPair = map->buckets[indice];
        if (currentPair == NULL) return NULL;
        if(currentPair->key != NULL && strcmp(currentPair->key, key) == 0)
        {
            map->current = indice;
            return currentPair; 
        }
        indice = (indice + 1) % map->capacity;

    } while(indice != copiaindice);

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
