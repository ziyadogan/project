#ifndef GLOBALS_H
#define GLOBALS_H

<<<<<<< HEAD
#include "list.h"
#include "drone.h"
#include "survivor.h"

// Global listeler
extern List* drones;
extern List* survivors;
extern List* helpedsurvivors;

// Global değişkenleri başlat
void initialize_globals();

// Global değişkenleri temizle
void cleanup_globals();

#endif
=======
#include "map.h"
#include "drone.h"
#include "survivor.h"
#include "list.h"
#include "coord.h"

extern Map map;
extern List *survivors, *helpedsurvivors, *drones;

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
