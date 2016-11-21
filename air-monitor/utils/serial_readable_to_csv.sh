#!/bin/sh

picocom -b 115200 $1 | sed -E 's/ [^ ,.0-9]+,? {0,3}/,/g; s/,$//;'
