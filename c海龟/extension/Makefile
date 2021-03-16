CC=gcc
COMMON= `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =  `sdl2-config --libs` -lm

all: extension extension_s extension_v

extension : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c extension.c extension.h extension.c extension_main.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/parser.c extension.c extension_main.c -o extension -I../code/ -I./ $(PRODUCTION) $(LDLIBS)

extension_s : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c extension.c extension.h extension.c extension_main.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/parser.c extension.c extension_main.c -o extension_s -I../code/ -I./ $(SANITIZE) $(LDLIBS)

extension_v : ../code/stack.h ../code/stack.c ../code/general.h ../code/general.c ../code/bool.h ../code/arraylist.h ../code/arraylist.c extension.c extension.h extension.c extension_main.c
	$(CC) ../code/stack.c ../code/general.c ../code/arraylist.c ../code/parser.c extension.c extension_main.c -o extension_v -I../code/ -I./ $(VALGRIND) $(LDLIBS)

clean:
	rm -f extension extension_s extension_v

run: all
	./extension
	valgrind ./extension_v
