all:
	gcc -o forking forking.c

run: all
	./forking
