#!/bin/bash

config=/home/conf

# Start specified process:
$1 $config/$1.xml >/dev/null 2>/dev/null & #send output and errors to /dev/null

exit 1
