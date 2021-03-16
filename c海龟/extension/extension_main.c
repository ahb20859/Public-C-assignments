#include <stdio.h>
#include"./stack.h"
#include "arraylist.h"
#include "extension.h"

int main(int argc, char *argv[])
{
    sdl d;
    list *pl;
    char bmp_file[1024];

    if (argc != 2)
    {
        on_error("Only 1 argument is required.\n");
    }

    /*
    argc  = 2;
    argv[1] = "./simp_c.ttl";
    argv[1] = "./simp.ttl";
    argv[1] = "./spiral2_c.ttl";
    argv[1] = "./spiral1_c.ttl";
    */

    pl = extension_read_file(argv[1]);
    initSDL(&d);
    pl->draw_handle = (void*)d.rend;
    pl->PI = acos(-1.0);
    pl->start.x = WIDTH / 2.;
    pl->start.y = HEIGHT / 2.;

    extension_main(pl);
    SDL_RenderPresent(d.rend);

    do
    {
        SDL_Loops(&d);
    } while (d.quit == 0);

    strcpy(bmp_file, argv[1]);
    strcat(bmp_file, ".bmp");
    save_screenshot(bmp_file, d.win, d.rend);

    list_free(pl);

     SDL_Quit();

    return 0;
}
