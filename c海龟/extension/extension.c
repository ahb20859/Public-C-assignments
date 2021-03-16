
#include "extension.h"
#include "../code/interp.h"
#include<ctype.h>
#include "../code/stack.h"

list *extension_read_file(char *path)
{
    FILE *fr;
    list *pl;
    char str[1024];
    int ret;

    pl = list_init();
    fr = (FILE*)nfopen(path, "r");
    while ((ret = fscanf(fr, "%s", str)) != EOF)
    {
        list_insert(pl, str);
    };

    fclose(fr);

    return pl;
}
bool extension_main(list *pl)
{
    bool flag;

    if (strcmp(pl->string[pl->cur], "{") == 0)
    {
        printf("{\n");
        flag = true;
        pl->cur++;
        extension_instrctlst(pl, &flag);
        if (flag)
        {
            return true;
        }
    }
    return false;
}
void extension_instrctlst(list *pl, bool *flag)
{
    if (pl->cur < pl->size - 1)
    {
        if (extension_instruction(pl))
        {
            extension_instrctlst(pl, flag);
        }
        else
        {
            if (strcmp(pl->string[pl->cur], "}") == 0)
            {
                pl->cur++;
                /*printf("}\n");*/
            }
            else
            {
                *flag = false;
                return;
            }
        }
    }
    else if (pl->cur == pl->size - 1)
    {
        if (strcmp(pl->string[pl->cur], "}") == 0)
        {
            pl->cur++;
            /*printf("}\n");*/
        }
        else
        {
            *flag = false;
            return;
        }
    }
    else
    {
        return;
    }
}

bool extension_instruction(list *pl)
{
    return extension_move(pl) || extension_lt(pl) || extension_fd(pl) || extension_rt(pl) || extension_do_(pl) || extension_set_(pl);
}

bool extension_move(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "MOVE") && extension_varnum(pl->string[pl->cur + 1]) && extension_varnum(pl->string[pl->cur + 2]);
    if (ret)
    {
        if (extension_var(pl->string[pl->cur + 1]))
        {
            printf("%s %f\n", pl->string[pl->cur], pl->var_table[pl->string[pl->cur + 1][0] - 'A']);
            pl->start.x = pl->var_table[pl->string[pl->cur + 1][0] - 'A'];
        }
        else
        {
            printf("%s %f\n", pl->string[pl->cur], atof(pl->string[pl->cur + 1]));
            pl->start.x = atof(pl->string[pl->cur + 1]);
        }
        if (extension_var(pl->string[pl->cur + 2]))
        {
            printf("%f\n", pl->var_table[pl->string[pl->cur + 2][0] - 'A']);
            pl->start.y = pl->var_table[pl->string[pl->cur + 2][0] - 'A'];
        }
        else
        {
            printf("%f\n", atof(pl->string[pl->cur + 2]));
            pl->start.y = atof(pl->string[pl->cur + 2]);
        }
        pl->cur += 3;
    }
    return ret;
}
bool extension_fd(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "FD") && extension_varnum(pl->string[pl->cur + 1]);
    if (ret)
    {
        if (extension_var(pl->string[pl->cur + 1]))
        {
            printf("%s %f\n", pl->string[pl->cur], pl->var_table[pl->string[pl->cur + 1][0] - 'A']);
            pl->end.x = pl->start.x + cos(pl->theta * pl->PI / 180.0) * pl->var_table[pl->string[pl->cur + 1][0] - 'A'];
            pl->end.y = pl->start.y - sin(pl->theta * pl->PI / 180.0) * pl->var_table[pl->string[pl->cur + 1][0] - 'A'];
            SDL_RenderDrawLine((SDL_Renderer *)pl->draw_handle, pl->start.x, pl->start.y, pl->end.x, pl->end.y);
            printf("----- start(%f, %f) -----end(%f, %f)\n", pl->start.x, pl->start.y, pl->end.x, pl->end.y);
            SDL_RenderPresent(pl->draw_handle);
            pl->start = pl->end;
        }
        else
        {
            printf("%s %f\n", pl->string[pl->cur], atof(pl->string[pl->cur + 1]));

            pl->end.x = pl->start.x + cos(pl->theta * pl->PI / 180.0) * atof(pl->string[pl->cur + 1]);
            pl->end.y = pl->start.y - sin(pl->theta * pl->PI / 180.0) * atof(pl->string[pl->cur + 1]);
            SDL_RenderDrawLine((SDL_Renderer *)pl->draw_handle, pl->start.x, pl->start.y, pl->end.x, pl->end.y);
            printf("----- start(%f, %f) -----end(%f, %f)\n", pl->start.x, pl->start.y, pl->end.x, pl->end.y);
            SDL_RenderPresent(pl->draw_handle);
            pl->start = pl->end;
        }
        pl->cur += 2;
    }
    return ret;
}

bool extension_lt(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "LT") && extension_varnum(pl->string[pl->cur + 1]);
    if (ret)
    {
        if (extension_var(pl->string[pl->cur + 1]))
        {
            printf("%s %f\n", pl->string[pl->cur], pl->var_table[pl->string[pl->cur + 1][0] - 'A']);
            pl->theta += pl->var_table[pl->string[pl->cur + 1][0] - 'A'];
        }
        else
        {
            printf("%s %f\n", pl->string[pl->cur], atof(pl->string[pl->cur + 1]));
            pl->theta += atof(pl->string[pl->cur + 1]);
        }
        pl->cur += 2;
    }
    return ret;
}
bool extension_var(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] < 'A' || str[i] > 'Z')
        {
            return false;
        }
    }
    return true;
}

static bool num(char *str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
        {
            return false;
        }
    }

    return true;
}

bool extension_varnum(char *str)
{
    return extension_var(str) || num(str);
}

bool extension_rt(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "RT") && extension_varnum(pl->string[pl->cur + 1]);
    if (ret)
    {
        if (extension_var(pl->string[pl->cur + 1]))
        {
            printf("%s %f\n", pl->string[pl->cur], pl->var_table[pl->string[pl->cur + 1][0] - 'A']);
            /*pl->theta += (360 - pl->var_table[pl->string[pl->cur + 1][0] - 'A']);*/
            pl->theta -= pl->var_table[pl->string[pl->cur + 1][0] - 'A'];
        }
        else
        {
            printf("%s %f\n", pl->string[pl->cur], atof(pl->string[pl->cur + 1]));
            /*pl->theta += (360-atof(pl->string[pl->cur + 1]));*/
            pl->theta -= atof(pl->string[pl->cur + 1]);
        }
        pl->cur += 2;
    }
    return ret;
}

bool extension_do_(list *pl)
{
    bool flag;
    bool ret;
    int from, to, id, i;

    flag = true;
    ret = !strcmp(pl->string[pl->cur], "DO") \
        && extension_var(pl->string[pl->cur + 1]) \
        && !strcmp(pl->string[pl->cur + 2], "FROM") \
        && extension_varnum(pl->string[pl->cur + 3]) \
        && !strcmp(pl->string[pl->cur + 4], "TO") \
        && extension_varnum(pl->string[pl->cur + 5]) \
        && !strcmp(pl->string[pl->cur + 6], "{");

    if (ret)
    {
        printf("%s %s %s %s %s %s %s\n", pl->string[pl->cur],
            pl->string[pl->cur + 1], pl->string[pl->cur + 2],
            pl->string[pl->cur + 3], pl->string[pl->cur + 4],
            pl->string[pl->cur + 5], pl->string[pl->cur + 6]);
        from = atoi(pl->string[pl->cur + 3]);
        to = atoi(pl->string[pl->cur + 5]);
        pl->cur += 7;
        id = pl->cur;
        for (i = 0; i <= to - from; i++)
        {
            pl->var_table[pl->string[pl->cur - 7 + 1][0] - 'A'] = i + 1;
            extension_instrctlst(pl, &flag);
            if (i < to - from)
            {
                pl->cur = id;
            }
        }
    }
    else
    {
        return false;
    }
    return flag;
}

bool extension_set_(list *pl)
{
    bool ret;
    bool flag;
    stack *s;
    stacktype d;
    flag = false;

    ret = !strcmp(pl->string[pl->cur], "SET") \
        && extension_var(pl->string[pl->cur + 1]) \
        && !strcmp(pl->string[pl->cur + 2], ":=");
    if (ret)
    {
        pl->cur += 3;
        s = stack_init();
        ret = extension_polish(pl, s);
        stack_pop(s, &d);
        pl->var_table[pl->string[pl->cur + 1][0] - 'A'] = d;
        stack_free(s);
        printf("SET C := %f\n", d);
        return ret;
    }
    return flag;
}

bool extension_op(char *str)
{
    return strcmp(str, "+") == 0 || \
        strcmp(str, "-") == 0 || \
        strcmp(str, "*") == 0 || \
        strcmp(str, "/") == 0;
}

bool extension_polish(list *pl, stack *s)
{
    bool ret;
    stacktype a, b;
    ret = extension_varnum(pl->string[pl->cur]) | extension_op(pl->string[pl->cur]);
    if (ret)
    {
        if (!extension_op(pl->string[pl->cur]))
        {
            if (num(pl->string[pl->cur]))
            {
                stack_push(s, atof(pl->string[pl->cur]));
            }
            else
            {
                stack_push(s, pl->var_table[pl->string[pl->cur][0] - 'A']);
            }
        }
        else
        {
            stack_pop(s, &b);
            stack_pop(s, &a);
            if (!strcmp(pl->string[pl->cur], "+"))
            {
                stack_push(s, a + b);
            }
            else if (!strcmp(pl->string[pl->cur], "-"))
            {
                stack_push(s, a - b);
            }
            else if (!strcmp(pl->string[pl->cur], "*"))
            {
                stack_push(s, a * b);
            }
            else
            {
                stack_push(s, a / b);
            }
        }

        pl->cur++;
        return extension_polish(pl, s);
    }
    else
    {
        ret = !strcmp(pl->string[pl->cur], ";");
        if (ret)
        {
            /*printf("%s\n", pl->string[pl->cur]);*/
            pl->cur++;
        }
        return ret;
    }
}

void initSDL(sdl *d)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        fprintf(stderr, "failed to initialize SDL: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    d->quit = 0;
    d->win = SDL_CreateWindow("turtle graph",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);
    if (d->win == NULL)
    {
        fprintf(stderr, "failed to initialize SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    d->rend = SDL_CreateRenderer(d->win, -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_TARGETTEXTURE);
    if (d->rend == NULL)
    {
        fprintf(stderr, "failed to initialize SDL Renderer: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(d->rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(d->rend);
    SDL_SetRenderDrawColor(d->rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
}


void SDL_Loops(sdl *d)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_KEYDOWN:
            d->quit = 1;
            break;
        }
    }
}

bool save_screenshot(const char * filepath, SDL_Window * SDLWindow, SDL_Renderer *SDLRenderer)
{
    SDL_Surface * saveSurface = NULL;
    SDL_Surface * infoSurface = NULL;
    unsigned char * pixels = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL)
    {
        on_error("SDL_GetWindowSurface failed\n");
    }
    else
    {
        pixels = (unsigned char*)ncalloc(infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel, 1);
        if (pixels == 0)
        {
            on_error("ncalloc failed\n");
        }
        else
        {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
            {
                on_error("SDL_RenderReadPixels failed\n");
            }
            else
            {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel,
                    infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
                    infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL)
                {
                    on_error("SDL_CreateRGBSurfaceFrom failed\n");
                }
                SDL_SaveBMP(saveSurface, filepath);
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            free(pixels);
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }

    return true;
}
