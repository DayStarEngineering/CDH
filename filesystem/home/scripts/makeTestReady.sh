#!/bin/bash

# Stop everything:
stopall.sh

# Clear all data and logs:
cleandata.sh
cleanlog.sh

# Clear any sched status:
resetSched.sh

# Make rc.local test ready:
rctest.sh

# Make crontab test ready:
crontest.sh

exit 1
