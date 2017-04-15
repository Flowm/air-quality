#!/usr/bin/env bash

fname=aq

# Create DB without -c (continue)
if [ "$1" != "-c" ]; then
	echo "create table sensors(id INTEGER PRIMARY KEY NOT NULL, temperature REAL, humidity REAL, pressure REAL, mq135 INTEGER, iaqs INTEGER, co2 INTEGER, tvoc INTEGER, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL);" | sqlite3 $fname.sqlite
fi

# Read serial
picocom -b 115200 /dev/tty.usbmodem2477801 | tee $fname.log &
sleep 1

# Write to sqlite
tail -f $fname.log | while read LINE; do
	echo $LINE |
	perl -lne 'm/counter=.+,temperature=(?<t>.+),humidity=(?<h>.+),pressure=(?<p>.+),mq135=(?<m>.+),iaqs=(?<i>.+),co2=(?<c>.+),tvoc=(?<v>.+),chk=.+/; print "INSERT INTO sensors (temperature, humidity, pressure, mq135, iaqs, co2, tvoc) VALUES ($+{t},$+{h},$+{p},$+{m},$+{i},$+{c},$+{v});"' |
	sqlite3 $fname.sqlite
done
