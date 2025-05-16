#ifndef AI_H
#define AI_H

#include "drone.h"
#include "coord.h"

void assign_mission(Drone *drone, Coord target);
Drone* find_closest_idle_drone(Coord target);
void* ai_controller(void *arg);

#endif
