#include "../headers/globals.h"

// Global listelerin tanımları
List* drones = NULL;
List* survivors = NULL;
List* helpedsurvivors = NULL;

void initialize_globals() {
    // Listeleri oluştur
    drones = create_list(sizeof(Drone), 100);  // 100 drone kapasitesi
    survivors = create_list(sizeof(Survivor), 1000);  // 1000 kurtulan kapasitesi
    helpedsurvivors = create_list(sizeof(Survivor), 1000);  // 1000 yardım edilmiş kurtulan kapasitesi
}

void cleanup_globals() {
    // Listeleri temizle
    if (drones) {
        drones->destroy(drones);
        drones = NULL;
    }
    if (survivors) {
        survivors->destroy(survivors);
        survivors = NULL;
    }
    if (helpedsurvivors) {
        helpedsurvivors->destroy(helpedsurvivors);
        helpedsurvivors = NULL;
    }
}
