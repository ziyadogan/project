#include "../headers/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *create_list(size_t datasize, int capacity) {
    List *list = malloc(sizeof(List));
    memset(list, 0, sizeof(List));

    list->datasize = datasize;
    list->nodesize = sizeof(Node) + datasize;
    list->startaddress = malloc(list->nodesize * capacity);
    list->endaddress = list->startaddress + (list->nodesize * capacity);
    list->lastprocessed = (Node *)list->startaddress;
    list->number_of_elements = 0;
    list->capacity = capacity;

    pthread_mutex_init(&list->lock, NULL);
    sem_init(&list->elements_sem, 0, capacity);
    sem_init(&list->empty_sem, 0, 0);

    // Fonksiyon pointerlarını ayarla
    list->add = list_add;
    list->remove = list_remove;
    list->get = list_get;
    list->size = list_size;
    list->destroy = list_destroy;

    return list;
}

void list_add(List *self, void *data) {
    sem_wait(&self->elements_sem);
    pthread_mutex_lock(&self->lock);

    Node *node = (Node *)self->lastprocessed;
    node->data = malloc(self->datasize);
    memcpy(node->data, data, self->datasize);
    self->lastprocessed = (char *)self->lastprocessed + self->nodesize;
    self->number_of_elements++;

    pthread_mutex_unlock(&self->lock);
    sem_post(&self->empty_sem);
}

void list_remove(List *self, void *data) {
    (void)data; // Unused parameter warning suppression
    
    sem_wait(&self->empty_sem);
    pthread_mutex_lock(&self->lock);

    // Basit implementasyon - gerçek uygulamada daha karmaşık olabilir
    self->number_of_elements--;

    pthread_mutex_unlock(&self->lock);
    sem_post(&self->elements_sem);
}

void* list_get(List *self, int index) {
    if (index < 0 || index >= self->number_of_elements) {
        return NULL;
    }

    pthread_mutex_lock(&self->lock);
    Node *node = (Node *)((char *)self->startaddress + (index * self->nodesize));
    void *data = node->data;
    pthread_mutex_unlock(&self->lock);

    return data;
}

int list_size(List *self) {
    return self->number_of_elements;
}

void list_destroy(List *self) {
    pthread_mutex_destroy(&self->lock);
    sem_destroy(&self->elements_sem);
    sem_destroy(&self->empty_sem);
    free(self->startaddress);
    free(self);
}
