
#include <stdio.h>
#include <assert.h>
#include "../code/stack.h"
#include "../code/arraylist.h"
#include "../code/parser.h"

int main()
{
    list *pl;
    stack *s;
    int i;
    double val;
    
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

    pl = read_file("../data/spiral2_c.ttl");
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
    printf("read_file test pass\n");
    assert(Main(pl));
    printf("Main test pass\n");

    assert(list_free(pl));

    return 0;
}