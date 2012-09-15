#!/bin/bash

log=/home/log/sched_control.log

echo "Pausing sched at "`date +%s`" : "`stcl sched set 1 0` >> $log

exit 1
