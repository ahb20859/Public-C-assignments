#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "general.h"
#include "bool.h"

#define VAR    26

struct point 
{
    double x;
    double y;
};

typedef struct point point;

struct list
{
    char **string;
    int cur;
    int size;
    double var_table[VAR];
    void *draw_handle;
    point start;
    point end;
    double PI;
    double theta;
};

typedef struct list list;

list *list_init();
bool list_insert(list * pl, char * str);
bool list_free(list *pl);
