#ifndef DRONE_H
#define DRONE_H

#include "coord.h"
#include "list.h"
#include <time.h>
#include <pthread.h>

typedef enum {
    IDLE,
    ON_MISSION,
    DISCONNECTED
} DroneStatus;

typedef struct drone {
    int id;
    pthread_t thread_id;
    int status;
    Coord coord;
    Coord target;
    struct tm last_update;
    pthread_mutex_t lock;
    pthread_cond_t mission_cond;
} Drone;

// Fonksiyon prototipleri
void initialize_drones();
void* drone_behavior(void *arg);

#endif
