#!/bin/sh

picocom -b 115200 $1 | tee air_data.log &
gnuplot -c plot_data.gp
