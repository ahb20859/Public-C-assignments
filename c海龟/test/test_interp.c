#include <stdio.h>
#include <assert.h>
#include"../code/stack.h"
#include "../code/arraylist.h"
#include "../code/interp.h"

int main(int argc, char *argv[])
{
    sdl d;
    list *pl;
    char bmp_file[1024];
    stack *s;
    int i;
    double val;

    /*
      if I do not like this, I will get  unused parameter ‘argc’ error.
      if I do not use argc argv param, it do not math when use SDL.
    */
    argc = 2;
    argv[1] = "../data/spiral2_c.ttl";
    if (argc != 2)
    {
        on_error("Only 1 argument is required.\n");
    }
    
    pl = list_init();
    assert(pl != NULL);
    for(i = 0; i < 1000; i++)
    {
        assert(list_insert(pl, "test_list") == true);
    }
    assert(pl->size == 1000);
    assert(list_free(pl));
    printf("array_list test pass\n");
    
    s = stack_init();
    assert(s != NULL);
    for(i = 0; i < 1000; i++)
    {
        stack_push(s, 30.3);
    }
    assert(s->size == 1000);
    assert(stack_pop(s, &val));
    assert(val - 30.3 < 1e-6);
    assert(stack_free(s));
    printf("stack test pass\n");

    pl = interp_read_file(argv[1]);
    assert(pl);
    i = 0;
    assert(!strcmp(pl->string[i++], "{"));
    assert(!strcmp(pl->string[i++], "DO"));
    assert(!strcmp(pl->string[i++], "A"));
    assert(!strcmp(pl->string[i++], "FROM"));
    assert(!strcmp(pl->string[i++], "1"));
    assert(!strcmp(pl->string[i++], "TO"));
    assert(!strcmp(pl->string[i++], "50"));
    assert(!strcmp(pl->string[i++], "{"));
    assert(!strcmp(pl->string[i++], "FD"));
    assert(!strcmp(pl->string[i++], "A"));
    assert(!strcmp(pl->string[i++], "RT"));
    assert(!strcmp(pl->string[i++], "30"));
    
    assert(!strcmp(pl->string[i++], "DO"));
    assert(!strcmp(pl->string[i++], "B"));
    assert(!strcmp(pl->string[i++], "FROM"));
    assert(!strcmp(pl->string[i++], "1"));
    assert(!strcmp(pl->string[i++], "TO"));
    assert(!strcmp(pl->string[i++], "8"));
    assert(!strcmp(pl->string[i++], "{"));
    assert(!strcmp(pl->string[i++], "SET"));
    assert(!strcmp(pl->string[i++], "C"));
    assert(!strcmp(pl->string[i++], ":="));
    assert(!strcmp(pl->string[i++], "A"));
    
    assert(!strcmp(pl->string[i++], "5"));
    assert(!strcmp(pl->string[i++], "/"));
    assert(!strcmp(pl->string[i++], ";"));
    assert(!strcmp(pl->string[i++], "FD"));
    assert(!strcmp(pl->string[i++], "C"));
    assert(!strcmp(pl->string[i++], "RT"));
    assert(!strcmp(pl->string[i++], "45"));
    assert(!strcmp(pl->string[i++], "}"));
    assert(!strcmp(pl->string[i++], "}"));
    assert(!strcmp(pl->string[i++], "}"));
    assert(!strcmp(pl->string[pl->size - 1], "}"));
	assert(i == pl->size);
    assert(pl->cur < pl->size);
    printf("interp_read_file test pass\n");

    initSDL(&d);
    pl->draw_handle = (void*)d.rend;
    
    /*pi = 3.1415926...*/
    pl->PI = acos(-1.0);
    /*pen in the center of screen*/
    pl->start.x = WIDTH / 2.;
    pl->start.y = HEIGHT / 2.;

    assert(interp_main(pl));
    printf("interp_main test pass\n");

    SDL_RenderPresent(d.rend);

    do
    {
        SDL_Loops(&d);
    } while (d.quit == 0);

    /*save screen to bmp file*/
    strcpy(bmp_file, argv[1]);
    strcat(bmp_file, ".bmp");
    save_screenshot(bmp_file, d.win, d.rend);

    assert(list_free(pl));

    SDL_Quit();

    return 0;
}
