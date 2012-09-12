#!/bin/bash

##################################
# Basic Data:
##################################
# Current time:
TIME=$(date +%s)

# Uptime:
UTIME=$(cat /proc/uptime)

# CPU Usage:
CPU=$(mpstat | grep all | awk '{print $4" "$5" "$6" "$7" "$8" "$9" "$10" "$11" "$12}')
# Mem Usage:
MEM=$(free | grep Mem | awk '{print $2" "$3" "$4}')
# Load Average:
LOADAVE=$(cat /proc/loadavg | awk '{print $1" "$2" "$3}')

# System Data Usage:
DF=$(df | grep /dev/sda1 | awk '{print $3" "$4}')
DFDATA=$(df | grep /dev/sda3 | awk '{print $3" "$4}')
DFDATA1=$(df | grep /dev/sdb1 | awk '{print $3" "$4}')
DFDATA2=$(df | grep /dev/sdc1 | awk '{print $3" "$4}')

# Number of files:
IMGFC0=$(ls -l /data/img | wc -l)
IMGFC0=$(($IMGFC0-1))
IMGFC1=$(ls -l /data1/img | wc -l)
IMGFC1=$(($IMGFC1-1))
IMGFC2=$(ls -l /data2/img | wc -l)
IMGFC2=$(($IMGFC2-1))
HEALTHFC=$(ls -l /data/health | wc -l)
HEALTHFC=$(($HEALTHFC-1))
DONEFC=$(ls -l /data/eps/done | wc -l)
DONEFC=$(($DONEFC-1))
PARTSFC=$(ls -l /data/eps/parts | wc -l)
PARTSFC=$(($PARTSFC-1))

# Zombie Processes:
NUMZOMB=$(ps aux | grep Z | grep -v grep | grep -v PID -c)

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
STIMG5=$(stcl stimg get 4)
STIMG5=${STIMG4:12:8}

# SCHED:
SCHED0=$(stcl sched get 0)
SCHED0=${SCHED0:12:8}
SCHED1=$(stcl sched get 1)
SCHED1=${SCHED1:12:8}
SCHED2=$(stcl sched get 2)
SCHED2=${SCHED2:12:8}

####################################
# Write Health and Status to File:
####################################

echo $TIME $UTIME $CPU $MEM $LOADAVE $DF $DFDATA $DFDATA1 $DFDATA2 $IMGFC0 $IMGFC1 $IMGFC2 $HEALTHFC $DONEFC $PARTSFC $NUMZOMB $NUMPDOG $NUMSTIMG $NUMDCOL $NUMSCHED $NUMSSM $STIMG0 $STIMG1 $STIMG2 $STIMG3 $STIMG4 $STIMG5 $SCHED0 $SCHED1 $SCHED2

####################################
# END
####################################
exit 1
