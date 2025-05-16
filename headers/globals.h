#ifndef GLOBALS_H
#define GLOBALS_H

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
