#ifndef AI_H
#define AI_H

#include "drone.h"
<<<<<<< HEAD
#include "coord.h"

void assign_mission(Drone *drone, Coord target);
Drone* find_closest_idle_drone(Coord target);
void* ai_controller(void *arg);

#endif
=======
#include "survivor.h"

// AI Mission Assignment
void* ai_controller(void *args);

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
