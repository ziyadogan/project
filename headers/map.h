#ifndef MAP_H
#define MAP_H

<<<<<<< HEAD
#include "coord.h"
#include "list.h"
#include "survivor.h"

typedef struct mapcell {
    Coord coord;
    List *survivors;
=======
#include "survivor.h"
#include "list.h"
#include "coord.h"

typedef struct mapcell {
    Coord coord;
    List *survivors;    // Survivors in this cell
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
} MapCell;

typedef struct map {
    int height, width;
    MapCell **cells;
} Map;

<<<<<<< HEAD
extern Map map;

void init_map(int height, int width);
void freemap();

#endif
=======
// Global map instance (extern)
extern Map map;

// Functions
void init_map(int height, int width);
void freemap();

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
