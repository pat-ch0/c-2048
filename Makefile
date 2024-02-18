CC = gcc
EXEC = prog

all : $(EXEC)

$(EXEC) : 2048.o
	$(CC) -o $(EXEC) 2048.o
2048.o : 2048.c
	$(CC) -o 2048.o -c 2048.c
clean :
	rm -rf *.o













