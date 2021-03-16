#pragma once
#include <SDL.h>
#include "../code/arraylist.h"
#include "../code/stack.h"
#include "../code/interp.h"

#define WIDTH 280
#define HEIGHT 260

list *extension_read_file(char *path);
bool extension_main(list *pl);
bool extension_fd(list *pl);
bool extension_lt(list *pl);
void extension_instrctlst(list *pl, bool *flag);
bool extension_instruction(list *pl);
bool extension_do_(list *pl);
bool extension_var(char *str);
bool extension_varnum(char *str);
bool extension_op(char *str);
bool extension_polish(list *pl, stack *s);
bool extension_set_(list *pl);
bool extension_rt(list *pl);
bool extension_move(list *pl);
