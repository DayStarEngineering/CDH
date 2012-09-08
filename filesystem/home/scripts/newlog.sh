#!/bin/bash

myFile=$1

rm -f $myFile
touch $myFile
tail -f $myFile

exit 1
