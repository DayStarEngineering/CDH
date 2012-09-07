#!/bin/bash

# Make semaphores:
touch /tmp/stpro.sem
touch /tmp/stch.sem
touch /tmp/hskpr.sem
touch /tmp/pdog.sem
touch /tmp/dcol.sem
touch /tmp/cmd.sem
touch /tmp/stimg.sem
touch /tmp/sched.sem
touch /tmp/kick.sem

# Start pdog:
cdh_hs_run.sh &
pdog /home/conf/pdog.xml >/dev/null 2>/dev/null &

exit 1

