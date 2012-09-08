#!/bin/bash

s=8

# Kills all daystar processes:
killall pdog `ls /home/bin/ | grep -v stcl | grep -v stch` `ls /home/scripts | grep -v killallproc.sh | grep -v killsomeproc.sh | grep -v shutdown.sh` >/dev/null 2>/dev/null &

sleep $s

killall -9 pdog `ls /home/bin/ | grep -v  stcl | grep -v stch` `ls /home/scripts | grep -v killallproc.sh | grep -v killsomeproc.sh | grep -v shutdown.sh` >/dev/null 2>/dev/null &

exit 1
