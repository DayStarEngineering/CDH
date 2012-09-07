#!/bin/bash

# Kill harshly twice:
killall -9 ssm
killall -9 ssm

# Destroy all message queues:

# Restart process:
ssm /home/conf/ssm.xml > /dev/null &
