#include "../headers/view.h"
#include "../headers/globals.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

void initialize_view() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        "Drone Simulation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return;
    }

    // Test için başlangıç verileri
    if (drones && drones->size(drones) == 0) {
        // Test drone'ları oluştur
        for (int i = 0; i < 5; i++) {
            Drone* drone = malloc(sizeof(Drone));
            if (drone) {
                drone->id = i + 1;
                drone->status = IDLE;
                drone->coord.x = rand() % (WINDOW_WIDTH / CELL_SIZE);
                drone->coord.y = rand() % (WINDOW_HEIGHT / CELL_SIZE);
                drones->add(drones, drone);
            }
        }
    }

    if (survivors && survivors->size(survivors) == 0) {
        // Test kurtulanları oluştur
        for (int i = 0; i < 3; i++) {
            Coord location = {
                .x = rand() % (WINDOW_WIDTH / CELL_SIZE),
                .y = rand() % (WINDOW_HEIGHT / CELL_SIZE)
            };
            time_t now = time(NULL);
            struct tm *current_time = localtime(&now);
            Survivor* survivor = create_survivor(&location, "Emergency", current_time);
            if (survivor) {
                survivors->add(survivors, survivor);
            }
        }
    }
}

void update_view() {
    if (!renderer) return;

    // Ekranı temizle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Izgara çiz
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int x = 0; x < WINDOW_WIDTH; x += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int y = 0; y < WINDOW_HEIGHT; y += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    // Drone'ları çiz
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Yeşil
    for (int i = 0; i < drones->size(drones); i++) {
        Drone* drone = drones->get(drones, i);
        if (drone) {
            SDL_Rect rect = {
                drone->coord.x * CELL_SIZE,
                drone->coord.y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Kurtulanları çiz
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Kırmızı
    for (int i = 0; i < survivors->size(survivors); i++) {
        Survivor* survivor = survivors->get(survivors, i);
        if (survivor) {
            SDL_Rect rect = {
                survivor->coord.x * CELL_SIZE,
                survivor->coord.y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Yardım edilmiş kurtulanları çiz
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Mavi
    for (int i = 0; i < helpedsurvivors->size(helpedsurvivors); i++) {
        Survivor* survivor = helpedsurvivors->get(helpedsurvivors, i);
        if (survivor) {
            SDL_Rect rect = {
                survivor->coord.x * CELL_SIZE,
                survivor->coord.y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Ekranı güncelle
    SDL_RenderPresent(renderer);
}

void cleanup_view() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
}
