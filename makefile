all: forking.c
	gcc -o forking forking.c

run: all
	./forking
