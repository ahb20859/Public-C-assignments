
#include <stdio.h>
#include "stack.h"
#include "arraylist.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    list *pl;
    /*
    argc = 2;
    argv[1] = "./simp_c.ttl";
    argv[1] = "./simp.ttl";
    argv[1] = "./spiral1_c.ttl";
    argv[1] = "./spiral2_c.ttl";
    argv[1] = "./spiral2_c.ttl";
    */
    
    if (argc != 2)
    {
        on_error("Only 1 argument is required.\n");
    }
    
    pl = read_file(argv[1]);

    if(!Main(pl))
    {
        /*printf("ERROR\n");*/
        list_free(pl);
        return -1;
    }
    /*printf("OK\n");*/
    
    list_free(pl);

    return 0;
}