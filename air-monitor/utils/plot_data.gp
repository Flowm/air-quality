set datafile separator ","
ftail = '< tail -n 2048 air_data.log'

set terminal canvas size 1280,900
set output "air_data.html"

#set terminal png size 1920,1080
#set output "air_data.png"

set xrange [0:2048]
set yrange [0:150]
set xlabel "Time"
set ylabel "Value"

plot \
	ftail using 1:2 with lines title "Temperature", \
	ftail using 1:3 with lines title "Humidity", \
	ftail using 1:4 with lines title "Pressure", \
	ftail using 1:5 with lines title "Altitude", \
	ftail using 1:6 with lines title "Gas"
pause 1
reread
