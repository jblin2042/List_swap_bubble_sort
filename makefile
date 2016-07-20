Target=list_swap_sort
CC=gcc
Flag=-Wall
Lib=
all:
	$(CC) $(Target).c -o $(Target)	$(Flag) $(Lib)
clean:
	rm $(Target)