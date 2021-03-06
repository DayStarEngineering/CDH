#!/bin/bash

# Make semaphores:
make_sems.sh

# Start low level programs to make sure eps does not reset us:
ssm /home/conf/ssm.xml > /dev/null &
stay_awake.sh > /dev/null &

# Start pdog:
cdh_hs_run.sh &
pdog /home/conf/pdog.xml >/dev/null 2>/dev/null &

exit 1

