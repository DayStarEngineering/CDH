#!/bin/bash

# Check on state of specified process
value=$(ps aux | grep $1 | grep -v grep | grep -v stcl | grep -v status.sh | grep -v .log | wc -l)
exit $value
