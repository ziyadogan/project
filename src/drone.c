#include "../headers/drone.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Global drone listesi
static List* drone_list = NULL;

void initialize_drones() {
    // Drone listesini oluştur
    drone_list = create_list(sizeof(Drone), 100);  // 100 drone kapasitesi
    
    // İlk drone'u oluştur ve başlat
    Drone* drone = malloc(sizeof(Drone));
    if (drone) {
        memset(drone, 0, sizeof(Drone));
        drone->id = 1;
        drone->status = IDLE;
        drone->coord.x = 0;
        drone->coord.y = 0;
        drone->target.x = 0;
        drone->target.y = 0;
        
        // Mutex ve condition variable'ları başlat
        pthread_mutex_init(&drone->lock, NULL);
        pthread_cond_init(&drone->mission_cond, NULL);
        
        // Drone'u listeye ekle
        drone_list->add(drone_list, drone);
        
        // Drone thread'ini başlat
        pthread_create(&drone->thread_id, NULL, drone_behavior, drone);
    }
}

void* drone_behavior(void *arg) {
    Drone* drone = (Drone*)arg;
    if (!drone) return NULL;
    
    while (1) {
        pthread_mutex_lock(&drone->lock);
        
        // Drone durumuna göre davranış
        switch (drone->status) {
            case IDLE:
                // Boşta bekle
                pthread_cond_wait(&drone->mission_cond, &drone->lock);
                break;
                
            case ON_MISSION:
                // Hedefe doğru hareket et
                if (drone->coord.x < drone->target.x) drone->coord.x++;
                if (drone->coord.x > drone->target.x) drone->coord.x--;
                if (drone->coord.y < drone->target.y) drone->coord.y++;
                if (drone->coord.y > drone->target.y) drone->coord.y--;
                
                // Hedefe ulaşıldı mı kontrol et
                if (drone->coord.x == drone->target.x && 
                    drone->coord.y == drone->target.y) {
                    drone->status = IDLE;
                }
                break;
                
            case DISCONNECTED:
                // Bağlantı kesildi, yeniden bağlanmayı dene
                // TODO: Implement reconnection logic
                break;
        }
        
        // Son güncelleme zamanını kaydet
        time_t now = time(NULL);
        drone->last_update = *localtime(&now);
        
        pthread_mutex_unlock(&drone->lock);
        sleep(1);  // 1 saniye bekle
    }
    
    return NULL;
}
