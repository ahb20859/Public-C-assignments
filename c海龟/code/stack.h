#pragma once
#include "general.h"
#include "bool.h"

typedef double stacktype;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct dataframe {
    stacktype i;
    struct dataframe* next;
};
typedef struct dataframe dataframe;

struct stack {
    /* Underlying array */
    dataframe* start;
    int size;
};

typedef struct stack stack;

/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, stacktype i);
/* Take element from top */
bool stack_pop(stack* s, stacktype* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s, stacktype* d);
