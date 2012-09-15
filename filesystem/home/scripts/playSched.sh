#!/bin/bash

log=/home/log/sched_control.log

echo "Playing sched at "`date +%s`" : "`stcl sched set 1 1` >> $log

exit 1
