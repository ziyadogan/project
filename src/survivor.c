#include "../headers/survivor.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

Survivor* create_survivor(Coord *coord, char *info, struct tm *discovery_time) {
    Survivor* s = malloc(sizeof(Survivor));
    if (!s) return NULL;

    s->status = 0; // Initial status
    if (coord) {
        s->coord = *coord;
    }
    if (discovery_time) {
        s->discovery_time = *discovery_time;
    } else {
        time_t now = time(NULL);
        s->discovery_time = *localtime(&now);
    }
    memset(&s->helped_time, 0, sizeof(struct tm));
    
    if (info) {
        strncpy(s->info, info, sizeof(s->info) - 1);
        s->info[sizeof(s->info) - 1] = '\0';
    } else {
        s->info[0] = '\0';
    }
    
    return s;
}

void* survivor_generator(void *args) {
    (void)args; // Unused parameter warning suppression
    
    while (1) {
        // Rastgele koordinatlar oluştur
        Coord location = {
            .x = rand() % 1000,
            .y = rand() % 1000
        };
        
        // Şu anki zamanı al
        time_t now = time(NULL);
        struct tm *current_time = localtime(&now);
        
        // Yeni kurtulan oluştur
        Survivor* survivor = create_survivor(&location, "Emergency", current_time);
        if (survivor) {
            // TODO: Implement survivor list management
            // For now, just free the survivor
            free(survivor);
        }
        
        sleep(5); // 5 saniye bekle
    }
    return NULL;
}
