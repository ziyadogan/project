<<<<<<< HEAD
#ifndef VIEW_H
#define VIEW_H

// Pencere ve hücre boyutları
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define CELL_SIZE 10

void initialize_view();
void update_view();
void cleanup_view();

#endif
=======

#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
/*view.c*/
extern int init_sdl_window();
extern void draw_cell(int x, int y, SDL_Color color);
extern void draw_drones();
extern void draw_survivors();
extern void draw_grid();
extern int draw_map();
extern int check_events();
extern int quit_all();

#endif
>>>>>>> 21daf67f026eb1dc7dd2fa47e2d384885b6f0ea5
