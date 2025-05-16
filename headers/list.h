#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>

typedef struct list {
    void *startaddress;
    void *endaddress;
    void *lastprocessed;
    size_t datasize;
    size_t nodesize;
    int number_of_elements;
    int capacity;
    pthread_mutex_t lock;
    sem_t elements_sem;
    sem_t empty_sem;
    
    // Fonksiyon pointerları
    void (*add)(struct list *self, void *data);
    void (*remove)(struct list *self, void *data);
    void* (*get)(struct list *self, int index);
    int (*size)(struct list *self);
    void (*destroy)(struct list *self);
} List;

typedef struct node {
    struct node *next;
    void *data;
} Node;

// List fonksiyonları
List *create_list(size_t datasize, int capacity);
void list_add(List *self, void *data);
void list_remove(List *self, void *data);
void* list_get(List *self, int index);
int list_size(List *self);
void list_destroy(List *self);

#endif
