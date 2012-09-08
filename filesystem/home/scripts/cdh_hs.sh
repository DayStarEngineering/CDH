#!/bin/bash

##################################
# Basic Data:
##################################

# Uptime:
UTIME=$(cat /proc/uptime)

# CPU Usage:
CPU=$(mpstat | grep all | awk '{print $4" "$5" "$6" "$7" "$8" "$9" "$10" "$11" "$12}')
# Mem Usage:
MEM=$(free | grep Mem | awk '{print $2" "$3" "$4}')

# System Data Usage:
DF=$(df | grep /dev/sda1 | awk '{print $3" "$4}')
DFDATA=$(df | grep /dev/sda3 | awk '{print $3" "$4}')
DFDATA1=$(df | grep /dev/sdb1 | awk '{print $3" "$4}')

# Number of files:
IMGFC=$(ls -l /data1/img | wc -l)
IMGFC=$(($IMGFC-1))
HEALTHFC=$(ls -l /data/health | wc -l)
HEALTHFC=$(($HEALTHFC-1))
DONEFC=$(ls -l /data/eps/done | wc -l)
DONEFC=$(($DONEFC-1))
PARTSFC=$(ls -l /data/eps/parts | wc -l)
PARTSFC=$(($PARTSFC-1))

# Load Average:
LOADAVE=$(cat /proc/loadavg | awk '{print $1" "$2" "$3}')

# Zombie Processes:
NUMZOMB=$(ps aux | grep Z | grep -v grep | grep -v PID -c)
if [ $NUMZOMB -gt 0 ] ; then
	LISTZOMB=$(ps aux | grep Z | grep -v grep | grep -v PID)
fi

####################################
# Process Running:
####################################

# Process Watchdog:
NUMPDOG=$(ps | grep pdog | grep -v grep -c)

# STIMG:
NUMSTIMG=$(ps | grep stimg | grep -v grep -c)

# DCOL:
NUMDCOL=$(ps | grep stimg | grep -v grep -c)

# SCHED:
NUMSCHED=$(ps | grep stimg | grep -v grep -c)

# SSM:
NUMSSM=$(ps | grep stimg | grep -v grep -c)

####################################
# Process Status:
####################################

# STIMG:
STIMG0=$(stcl stimg get 0)
STIMG0=${STIMG0:12:8}
STIMG1=$(stcl stimg get 1)
STIMG1=${STIMG1:12:8}
STIMG2=$(stcl stimg get 2)
STIMG2=${STIMG2:12:8}
STIMG3=$(stcl stimg get 3)
STIMG3=${STIMG3:12:8}
STIMG4=$(stcl stimg get 4)
STIMG4=${STIMG4:12:8}

# SCHED:
SCHED0=$(stcl sched get 0)
SCHED0=${SCHED0:12:8}
SCHED1=$(stcl sched get 1)
SCHED1=${SCHED1:12:8}
SCHED2=$(stcl sched get 2)
SCHED2=${SCHED2:12:8}

####################################
# Find Size of Error Logs:
####################################

#LOGDIR=/home/log/

# Create logfiles if they do not exist:
#touch $LOGDIR/pdog.log $LOGDIR/stpro.log

# Get size information:
#PDOGLOG=$(ls -l $LOGDIR/pdog.log | awk '{print $5}')
#STIMGLOG=$(ls -l $LOGDIR/stimg.log | awk '{print $5}')
#DCOLLOG=$(ls -l $LOGDIR/dcol.log | awk '{print $5}')
#SSMLOG=$(ls -l $LOGDIR/ssm.log | awk '{print $5}')
#SCHEDLOG=$(ls -l $LOGDIR/sched.log | awk '{print $5}')

####################################
# Write Health and Status to File:
####################################

# Uptime/CPU/Memory/Disk Usage/Load Average:
echo UPTIME: $UTIME
echo CPU USAGE: $CPU
echo MEM USAGE [TOTAL - USED - FREE]: $MEM
echo DISK USAGE [USED - AVAILABLE]:
echo "/:  "$DF
echo "/data:  "$DFDATA
echo "/data1:  "$DFDATA1
echo
echo LOAD AVERAGE [1,5,15 min]: $LOADAVE
echo
echo FILE COUNTS:
echo "/data1/img:      "$IMGFC
echo "/data/eps/done:  "$DONEFC
echo "/data/eps/parts: "$PARTSFC
echo "/data/health:    "$HEALTHFC
echo 

# Zombie Processes:
echo NUM ZOMBIES: $NUMZOMB
if [ $NUMZOMB -gt 0 ] ; then
	echo ZOMBIED PROCESSES: 
	echo $LISTZOMB
fi
echo

# Process Information:
echo "PROCCESSES Running:"
echo "pdog:       "$NUMPDOG
echo "stimg:      "$NUMSTIMG
echo "dcol:       "$NUMDCOL
echo "ssm:        "$NUMSSM
echo "sched:      "$NUMSCHED
echo

echo "STIMG Sems:"
echo "0 " $STIMG0
echo "1 " $STIMG1
echo "2 " $STIMG2
echo "3 " $STIMG3
echo "4 " $STIMG4

echo "SCHED Sems:"
echo "0 " $SCHED0
echo "1 " $SCHED1
echo "2 " $SCHED2

####################################
# END
####################################
exit 1
