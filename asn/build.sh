#!/bin/bash

cd e2sm_rc 
gcc -c -fPIC -Iheaders/ lib/*.c rcwrapper.c
gcc *.o -shared -o libe2smrcwrapper.so 

export LD_LIBRARY_PATH=/home/william/Documents/programming/ANSI_C/asn/e2sm_rc:$LD_LIBRARY_PATH

cd ..
gcc main.c -I/home/william/Documents/programming/ANSI_C/asn/e2sm_rc -I/home/william/Documents/programming/ANSI_C/asn/e2sm_rc/headers -L/home/william/Documents/programming/ANSI_C/asn/e2sm_rc -le2smrcwrapper -o main -lm

./main