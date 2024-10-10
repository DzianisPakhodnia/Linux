CC = gcc
CFLAGS = -Wall -E # Опция -E для препроцессора
ASFLAGS = -S     # Опция -S для генерации ассемблера
OBJFLAGS = -c    # Опция -c для компиляции в объектный файл

all: prog1 prog2

prog1: prog1.o
	$(CC) -o prog1 prog1.o

prog2: prog2.o
	$(CC) -o prog2 prog2.o

prog1.o: prog1.c
	$(CC) $(CFLAGS) -o prog1.i prog1.c  # Создание файла препроцессора
	$(CC) $(ASFLAGS) -o prog1.s prog1.c  # Создание ассемблерного файла
	$(CC) $(OBJFLAGS) -o prog1.o prog1.c  # Создание объектного файла

prog2.o: prog2.c
	$(CC) $(CFLAGS) -o prog2.i prog2.c  # Создание файла препроцессора
	$(CC) $(ASFLAGS) -o prog2.s prog2.c  # Создание ассемблерного файла
	$(CC) $(OBJFLAGS) -o prog2.o prog2.c  # Создание объектного файла

clean:
	rm -f prog1 prog2 *.o *.i *.s
