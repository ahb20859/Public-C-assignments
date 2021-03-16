#pragma once
#include <SDL.h>
#include "arraylist.h"
#include "stack.h"

#define WIDTH 280
#define HEIGHT 260

struct sdl
{
    SDL_bool quit;
    SDL_Window *win;
    SDL_Renderer *rend;
};
typedef struct sdl sdl;

void SDL_Loops(sdl *d);
void initSDL(sdl *d);
bool save_screenshot(const char * filepath, SDL_Window * SDLWindow, SDL_Renderer *SDLRenderer);
list *interp_read_file(char *path);
bool interp_main(list *pl);
bool interp_fd(list *pl);
bool interp_lt(list *pl);
void interp_instrctlst(list *pl, bool *flag);
bool interp_instruction(list *pl);
bool interp_do_(list *pl);
bool interp_var(char *str);
bool interp_varnum(char *str);
bool interp_op(char *str);
bool interp_polish(list *pl, stack *s);
bool interp_set_(list *pl);
bool interp_rt(list *pl);