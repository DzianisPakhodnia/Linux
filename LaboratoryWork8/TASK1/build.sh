#!/bin/bash

# Очистка предыдущих файлов
rm -f output.txt writer.o reader.o writer reader

# Препроцессор
gcc -E writer.c -o writer.i
gcc -E reader.c -o reader.i

# Ассемблер
gcc -S writer.c -o writer.s
gcc -S reader.c -o reader.s

# Компиляция в объектные файлы
gcc -c writer.c -o writer.o
gcc -c reader.c -o reader.o

# Линковка в исполняемые файлы
gcc writer.o -o writer
gcc reader.o -o reader

# Вывод размеров файлов
echo "Размеры файлов:"
du -h writer.c reader.c writer.i reader.i writer.s reader.s writer.o reader.o writer reader
