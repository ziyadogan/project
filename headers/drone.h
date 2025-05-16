#ifndef DRONE_H
#define DRONE_H

#include "coord.h"
<<<<<<< HEAD
#include "list.h"
#include <time.h>
#include <pthread.h>
=======
#include <time.h>
#include <pthread.h>
#include "list.h"
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5

typedef enum {
    IDLE,
    ON_MISSION,
    DISCONNECTED
} DroneStatus;

<<<<<<< HEAD
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
=======

typedef struct drone {
    int id;
    pthread_t thread_id;
    int status;             // IDLE, ON_MISSION, DISCONNECTED
    Coord coord;
    Coord target;
    struct tm last_update;
    pthread_mutex_t lock;   // Per-drone mutex
} Drone;

// Global drone list (extern)
extern List *drones;
extern Drone *drone_fleet; // Array of drones
extern int num_drones;    // Number of drones in the fleet
// Functions
void initialize_drones();
void* drone_behavior(void *arg);

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
