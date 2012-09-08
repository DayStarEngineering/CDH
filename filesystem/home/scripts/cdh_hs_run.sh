#!/bin/bash

##################################
# Set-up:
##################################

# HS Binary:
HS=/home/scripts/cdh_hs_nice.sh

# HS_File:
DOWNDIR=/data/health/

# Sleep Time:
SLEEPTIME=20

# Data points per file:
#DP=180

####################################
# Write Health and Status to File:
####################################
while [ 1 ]
do
# Current Time:
TIME=$(date +%s)

# File Name:
FNAME=$DOWNDIR'hs_'$TIME.txt

# Create File:
touch $FNAME

# Header:
#echo FILE: 'hs_'$TIME.txt >> $FNAME
#echo TIME: $TIME >> $FNAME
#echo >> $FNAME

for i in {1..180}
do
   # Print Health and Status to File:
   $HS >> $FNAME
   
   # Sleep:
   sleep $SLEEPTIME
done

# Compress File:
#bzip2 -1 $FNAME

done

exit 1

