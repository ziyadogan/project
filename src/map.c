#include "../headers/map.h"
#include <stdio.h>
#include <stdlib.h>

Map map;

void init_map(int height, int width) {
    printf("Initializing map %dx%d\n", height, width);
}

void freemap() {
    printf("Freeing map...\n");
}
