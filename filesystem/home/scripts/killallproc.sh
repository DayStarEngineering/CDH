#!/bin/bash

s=2

# Kills all daystar processes:
killall pdog
sleep $s
killall -9 pdog

killall `ls /home/bin/` stay_awake.sh cdh_hs_run.sh cdh_hs_nice.sh cdh_hs.sh >/dev/null 2>/dev/null &
sleep $s
killall -9 `ls /home/bin/` stay_awake.sh cdh_hs_run.sh cdh_hs.sh cdh_hs_nice.sh >/dev/null 2>/dev/null &
