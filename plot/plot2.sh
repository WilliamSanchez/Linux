#!/bin/bash
#rm plot.dat
gcc plot.c -o plot
./plot

gnuplot -persist -e "plot 'plot.dat'" loop.plt
