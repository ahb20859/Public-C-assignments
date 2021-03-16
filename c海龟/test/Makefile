CC=gcc
COMMON= `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =  `sdl2-config --libs` -lm

all: test_parser test_parser_s test_interp test_interp_s

test_parser : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c ../code/parser.c ../code/parser.h test_parser.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/parser.c test_parser.c -o test_parser -I../code/ $(PRODUCTION) $(LDLIBS)

test_parser_s : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c ../code/parser.c ../code/parser.h test_parser.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/parser.c test_parser.c -o test_parser_s -I../code/ $(SANITIZE) $(LDLIBS)

test_interp : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c ../code/interp.c ../code/interp.h test_interp.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/interp.c test_interp.c -o test_interp -I../code/ $(PRODUCTION) $(LDLIBS)

test_interp_s : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c ../code/interp.c ../code/interp.h test_interp.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/interp.c test_interp.c -o test_interp_s -I../code/ $(SANITIZE) $(LDLIBS)

clean:
	rm -f test_parser test_parser_s test_interp test_interp_s

run: all
	./test_parser
	./test_interp
