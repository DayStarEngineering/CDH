#!/bin/bash

LOGDIR=/home/log
rm -f $LOGDIR/*
touch $LOGDIR/stimg.log $LOGDIR/sched.log $LOGDIR/pdog.log $LOGDIR/dcol.log $LOGDIR/ssm.log $LOGDIR/startup_shutdown.log $LOGDIR/sched_control.log

exit 1
