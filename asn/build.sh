#!/bin/bash

file=$(pwd)

echo "file $file"

cd e2sm_rc 

gcc -c -fPIC -Iheaders/ lib/*.c rcwrapper.c #-DASN_EMIT_DEBUG=1
gcc *.o -shared -o libe2smrcwrapper.so 

export LD_LIBRARY_PATH=$file/e2sm_rc:$LD_LIBRARY_PATH

cd ..
gcc main.c -I$file/e2sm_rc \
           -I$file/e2sm_rc/headers \
           -L$file/e2sm_rc \
           -le2smrcwrapper -o main -lm 

./main 