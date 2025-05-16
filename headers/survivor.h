#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "coord.h"
#include <time.h>
<<<<<<< HEAD

=======
#include "list.h"
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
typedef struct survivor {
    int status;
    Coord coord;
    struct tm discovery_time;
    struct tm helped_time;
    char info[25];
} Survivor;

<<<<<<< HEAD
Survivor* create_survivor(Coord *coord, char *info, struct tm *discovery_time);
void* survivor_generator(void *args);

#endif
=======
// Global survivor lists (extern)
extern List *survivors;          // Survivors awaiting help
extern List *helpedsurvivors;    // Helped survivors

// Functions
Survivor* create_survivor(Coord *coord, char *info, struct tm *discovery_time);
void *survivor_generator(void *args);

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
