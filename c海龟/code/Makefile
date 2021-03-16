CC=gcc
COMMON= `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =  `sdl2-config --libs` -lm
LDLIBSS =  -lm

all: parser parser_s parser_v interp interp_s interp_v

parser : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c parser.c parser.h parser_main.c
	$(CC) stack.c general.c arraylist.c parser.c parser_main.c -o parser -I./ $(PRODUCTION) $(LDLIBSS)

parser_s : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c parser.c parser.h parser_main.c
	$(CC) stack.c general.c arraylist.c parser.c parser_main.c -o parser_s -I./ $(SANITIZE) $(LDLIBSS)

parser_v : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c parser.c parser.h parser_main.c
	$(CC) stack.c general.c arraylist.c parser.c parser_main.c -o parser_v -I./ $(VALGRIND) $(LDLIBSS)
    
interp : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c interp.c interp.h interp_main.c
	$(CC) stack.c general.c arraylist.c interp.c interp_main.c -o interp -I./ $(PRODUCTION) $(LDLIBS)

interp_s : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c interp.c interp.h interp_main.c
	$(CC) stack.c general.c arraylist.c interp.c interp_main.c -o interp_s -I./ $(SANITIZE) $(LDLIBS)

interp_v : stack.h stack.c general.h general.c bool.h arraylist.h arraylist.c interp.c interp.h interp_main.c
	$(CC) stack.c general.c arraylist.c interp.c interp_main.c -o interp_v -I./ $(VALGRIND) $(LDLIBS)
clean:
	rm -f parser parser_s parser_v interp interp_s interp_v

run: all
	./parser
	./interp
	valgrind ./parser_v
	valgrind ./interp_v
