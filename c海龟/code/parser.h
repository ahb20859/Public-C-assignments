
#include "arraylist.h"

list *read_file(char *path);
bool Main(list *pl);
bool fd(list *pl);
bool lt(list *pl);
void instrctlst(list *pl, bool *flag);
bool instruction(list *pl);
bool do_(list *pl);
bool var(char *str);
bool varnum(char *str);
bool op(char *str);
bool polish(list *pl);
bool set_(list *pl);
bool rt(list *pl);