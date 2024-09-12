#!/bin/sh

gcc -c  bill.c fred.c
ls *.o

gcc -c program.c

gcc -o program  program.o  bill.o
./program
rm -rf program

echo "Static library"

ar crv libfoo.a bill.o fred.o

ranlib libfoo.a

gcc -o program program.o libfoo.a
./program
rm -rf program program.o

echo "Shared library"
gcc -shared -o libfoo.so bill.o fred.o

gcc -L./ -Wl,-rpath=./ -Wall -o program program.c -lfoo
./program
