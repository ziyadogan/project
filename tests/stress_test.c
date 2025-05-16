#include "../headers/globals.h"
#include "../headers/drone.h"
#include "../headers/survivor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_DRONES 50
#define TEST_DURATION 30  // saniye

int main() {
    printf("Starting stress test with %d drones...\n", NUM_DRONES);
    
    // Global değişkenleri başlat
    initialize_globals();
    
    // Rastgele sayı üretecini başlat
    srand(time(NULL));
    
    // Drone'ları oluştur
    for (int i = 0; i < NUM_DRONES; i++) {
        Drone* drone = malloc(sizeof(Drone));
        if (drone) {
            memset(drone, 0, sizeof(Drone));
            drone->id = i + 1;
            drone->status = IDLE;
            drone->coord.x = rand() % 1000;
            drone->coord.y = rand() % 1000;
            
            pthread_mutex_init(&drone->lock, NULL);
            pthread_cond_init(&drone->mission_cond, NULL);
            
            drones->add(drones, drone);
            
            // Drone thread'ini başlat
            pthread_create(&drone->thread_id, NULL, drone_behavior, drone);
        }
    }
    
    printf("Created %d drones\n", NUM_DRONES);
    
    // Test süresi boyunca çalış
    time_t start_time = time(NULL);
    while (difftime(time(NULL), start_time) < TEST_DURATION) {
        // Rastgele kurtulan oluştur
        Coord location = {
            .x = rand() % 1000,
            .y = rand() % 1000
        };
        
        time_t now = time(NULL);
        struct tm *current_time = localtime(&now);
        
        Survivor* survivor = create_survivor(&location, "Emergency", current_time);
        if (survivor) {
            survivors->add(survivors, survivor);
            printf("Created survivor at (%d, %d)\n", location.x, location.y);
        }
        
        // Her 2 saniyede bir kurtulan oluştur
        sleep(2);
    }
    
    // Test sonuçlarını yazdır
    printf("\nTest Results:\n");
    printf("Total survivors created: %d\n", survivors->size(survivors));
    printf("Total survivors helped: %d\n", helpedsurvivors->size(helpedsurvivors));
    printf("Active drones: %d\n", drones->size(drones));
    
    // Global değişkenleri temizle
    cleanup_globals();
    
    printf("Stress test completed successfully\n");
    return 0;
}
