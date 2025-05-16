#include "../headers/globals.h"
#include "../headers/drone.h"
#include "../headers/survivor.h"
#include "../headers/ai.h"
#include "../headers/view.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <time.h>

int main() {
    printf("Starting drone simulator...\n");
    
    // Rastgele sayı üretecini başlat
    srand(time(NULL));
    
    // Global değişkenleri başlat
    initialize_globals();
    
    // Görüntüleme sistemini başlat
    initialize_view();
    
    // Drone'ları başlat
    initialize_drones();
    
    // Ana döngü
    SDL_Event event;
    int running = 1;
    
    while (running) {
        // SDL olaylarını işle
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                else if (event.key.keysym.sym == SDLK_SPACE) {
                    // Yeni kurtulan oluştur
                    Coord location = {
                        .x = rand() % (WINDOW_WIDTH / CELL_SIZE),
                        .y = rand() % (WINDOW_HEIGHT / CELL_SIZE)
                    };
                    time_t now = time(NULL);
                    struct tm *current_time = localtime(&now);
                    Survivor* survivor = create_survivor(&location, "Emergency", current_time);
                    if (survivor) {
                        survivors->add(survivors, survivor);
                        printf("Created new survivor at (%d, %d)\n", location.x, location.y);
                    }
                }
            }
        }
        
        // Yeni kurtulanları kontrol et
        for (int i = 0; i < survivors->size(survivors); i++) {
            Survivor* survivor = survivors->get(survivors, i);
            if (survivor) {
                // En yakın boşta olan drone'u bul
                Drone* drone = find_closest_idle_drone(survivor->coord);
                if (drone) {
                    // Drone'a görev ata
                    assign_mission(drone, survivor->coord);
                }
            }
        }
        
        // Görüntüyü güncelle
        update_view();
        
        // 100ms bekle
        SDL_Delay(100);
    }
    
    // Görüntüleme sistemini temizle
    cleanup_view();
    
    // Global değişkenleri temizle
    cleanup_globals();
    
    return 0;
}
