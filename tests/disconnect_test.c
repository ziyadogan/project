#include "../headers/globals.h"
#include "../headers/drone.h"
#include "../headers/survivor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TEST_DURATION 20  // saniye

int main() {
    printf("Starting disconnect test...\n");
    
    // Global değişkenleri başlat
    initialize_globals();
    
    // Rastgele sayı üretecini başlat
    srand(time(NULL));
    
    // Test drone'u oluştur
    Drone* drone = malloc(sizeof(Drone));
    if (drone) {
        memset(drone, 0, sizeof(Drone));
        drone->id = 1;
        drone->status = IDLE;
        drone->coord.x = 500;
        drone->coord.y = 500;
        
        pthread_mutex_init(&drone->lock, NULL);
        pthread_cond_init(&drone->mission_cond, NULL);
        
        drones->add(drones, drone);
        
        // Drone thread'ini başlat
        pthread_create(&drone->thread_id, NULL, drone_behavior, drone);
    }
    
    printf("Created test drone\n");
    
    // Test süresi boyunca çalış
    time_t start_time = time(NULL);
    while (difftime(time(NULL), start_time) < TEST_DURATION) {
        // Drone'u bağlantısını kes
        if (drone) {
            pthread_mutex_lock(&drone->lock);
            drone->status = DISCONNECTED;
            pthread_mutex_unlock(&drone->lock);
            printf("Drone disconnected\n");
        }
        
        sleep(5);
        
        // Drone'u yeniden bağla
        if (drone) {
            pthread_mutex_lock(&drone->lock);
            drone->status = IDLE;
            pthread_mutex_unlock(&drone->lock);
            printf("Drone reconnected\n");
        }
        
        sleep(5);
    }
    
    // Test sonuçlarını yazdır
    printf("\nTest Results:\n");
    printf("Drone status: %d\n", drone ? drone->status : -1);
    
    // Global değişkenleri temizle
    cleanup_globals();
    
    printf("Disconnect test completed successfully\n");
    return 0;
}
