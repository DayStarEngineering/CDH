#!/bin/bash

# Make sure our sems exist:
make_sems.sh

# Start low level programs to make sure eps does not reset us:
ssm /home/conf/ssm.xml > /dev/null &
stay_awake.sh > /dev/null &

exit 1
