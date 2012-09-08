#!/bin/bash

# Kill specified process
killall $1 >/dev/null 2>/dev/null #send output and errors to /dev/null
sleep 2s #wait for execution

# Rip memory if inactive
killall -9 $1 >/dev/null 2>/dev/null #send output and errors to /dev/null

exit 1
