
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arraylist.h"

#define MAXSIZE 8000

list *list_init()
{
    list *pl;
    pl = (list *)ncalloc(sizeof(list), 1);
    if(pl == NULL)
    {
        return NULL;
    }
    pl->string = (char **)ncalloc(sizeof(char *)* MAXSIZE, 1);
    pl->cur = 0;
    pl->size = 0;

    return pl;
}

bool list_insert(list * pl, char * str)
{
    int length = (int)strlen(str);
    if (pl->size == MAXSIZE - 1)
    {
        printf("List Full!\n");
        return false;
    }
    
    pl->string[pl->size] = (char *)ncalloc(sizeof(char) * (length + 1), 1);
    strcpy(pl->string[pl->size], str);
    pl->size++;
    return true;
}

bool list_free(list *pl)
{
    int i;
    if(pl == NULL)
    {
        return false;
    }
    
    for (i = 0; i < pl->size; i++)
    {
        free(pl->string[i]);
    }
    free(pl->string);
    free(pl);

    return true;
}