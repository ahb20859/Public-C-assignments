
#include "parser.h"
#include<ctype.h>
#include "stack.h"

list *read_file(char *path)
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
    }

    fclose(fr);

    return pl;
}
bool Main(list *pl)
{
    bool flag;

    if (strcmp(pl->string[pl->cur], "{") == 0)
    {
        /*printf("{\n");*/
        flag = true;
        pl->cur++;
        instrctlst(pl, &flag);
        if (flag)
        {
            return true;
        }
    }
    return false;
}
void instrctlst(list *pl, bool *flag)
{
    if (pl->cur < pl->size - 1)
    {
        if (instruction(pl))
        {
            instrctlst(pl, flag);
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

bool instruction(list *pl)
{
    return lt(pl) || fd(pl) || rt(pl) || do_(pl) || set_(pl);
}

bool fd(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "FD") && varnum(pl->string[pl->cur + 1]);
    if (ret)
    {
        /*printf("%s %s\n", pl->string[pl->cur], pl->string[pl->cur + 1]);*/
        pl->cur += 2;
    }
    return ret;
}

bool lt(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "LT") && varnum(pl->string[pl->cur + 1]);
    if(ret)
    {
        /*printf("%s %s\n", pl->string[pl->cur], pl->string[pl->cur + 1]);*/
        pl->cur += 2;
    }
    return ret;
}
bool var(char *str)
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

bool varnum(char *str)
{
    return var(str) || num(str);
}

bool rt(list *pl)
{
    bool ret;
    ret = !strcmp(pl->string[pl->cur], "RT") && varnum(pl->string[pl->cur + 1]);
    if (ret)
    {
        /*printf("%s %s\n", pl->string[pl->cur], pl->string[pl->cur + 1]);*/
        pl->cur += 2;
    }
    return ret;
}

bool do_(list *pl)
{
    bool flag;
    bool ret;

    flag = true;
    ret = !strcmp(pl->string[pl->cur], "DO") \
        && varnum(pl->string[pl->cur + 1]) \
        && !strcmp(pl->string[pl->cur + 2], "FROM") \
        && varnum(pl->string[pl->cur + 3]) \
        && !strcmp(pl->string[pl->cur + 4], "TO") \
        && varnum(pl->string[pl->cur + 5]) \
        && !strcmp(pl->string[pl->cur + 6], "{");

    if (ret)
    {
        /*printf("%s %s %s %s %s %s %s\n", pl->string[pl->cur],
            pl->string[pl->cur + 1], pl->string[pl->cur + 2],
            pl->string[pl->cur + 3], pl->string[pl->cur + 4],
            pl->string[pl->cur + 5], pl->string[pl->cur + 6]);*/
        pl->cur += 7;
        instrctlst(pl, &flag);
    }
    else
    {
        return false;
    }
    return flag;
}

bool set_(list *pl)
{
    bool ret;
    bool flag;
    flag = false;

    ret = !strcmp(pl->string[pl->cur], "SET") \
        && var(pl->string[pl->cur + 1]) \
        && !strcmp(pl->string[pl->cur + 2], ":=");
    if (ret)
    {
        /*printf("%s %s %s ", pl->string[pl->cur],
            pl->string[pl->cur + 1], pl->string[pl->cur + 2]);*/
        pl->cur += 3;
        return polish(pl);
    }
    return flag;
}

bool op(char *str)
{
    return strcmp(str, "+") == 0 ||
        strcmp(str, "-") == 0 ||
        strcmp(str, "*") == 0 ||
        strcmp(str, "/") == 0;
}

bool polish(list *pl)
{
    bool ret;
    ret = varnum(pl->string[pl->cur]) | op(pl->string[pl->cur]);
    if (ret)
    {
        /*printf("%s ", pl->string[pl->cur]);*/
        pl->cur++;
        return polish(pl);
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

