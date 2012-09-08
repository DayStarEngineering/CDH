#!/bin/bash

# Get commandline arguements:
SLEEPTIME=$1
NUM=$2
CNT=0

# Tell user what we are doing:
echo "Running fgcl -q grab2. Taking "$NUM" pictures at roughly ( 1 / "$RATE" ) Hz."


while [ 1 ]; do
	
	# Capture Image:
	fgcl -q grab2
	
	# Update Display:
	CNT=`expr $CNT + 1`
	clear
	echo "Captured " $CNT " of " $NUM " frames."
	
	# EXIT Condition:
	if [ $CNT -eq $NUM ]; then
		break
	fi
	
	# Take a nap:
	sleep $SLEEPTIME

done


