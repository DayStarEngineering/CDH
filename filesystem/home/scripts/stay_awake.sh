#!/bin/bash

while [ 1 ]; do

	# Ping eps so it doesn't reset us... this also keeps ssm active, so pdog does not restart it:
	stcl eps set 2 0 # Reset eps watchdog timer to 0 s
	
	# Take a nap:
	sleep 10
done

exit 1
