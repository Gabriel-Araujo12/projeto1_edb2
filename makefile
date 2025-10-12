TARGET = livraria

CC = gcc

CFLAGS = -Wall -std=c11

OBJS = main.o arvore.o heap.o categoria.o livro.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm

main.o: main.c arvore.h heap.h categoria.h livro.h
	$(CC) $(CFLAGS) -c main.c

arvore.o: arvore.c arvore.h
	$(CC) $(CFLAGS) -c arvore.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

categoria.o: categoria.c categoria.h
	$(CC) $(CFLAGS) -c categoria.c

livro.o: livro.c livro.h
	$(CC) $(CFLAGS) -c livro.c

clean:
	rm -f $(OBJS) $(TARGET)