#!/bin/sh

if [ $# -ne 1 ]; then
	echo
	echo "Incorrect Usage!"
	echo ">> updateVM.sh [IP ADDRESS]"
	echo
	exit 1
fi

IP=root@$1

# Kill all processes:
echo
echo "."
echo "..."
echo "Killing all processes..."
echo "..."
echo "."
echo
ssh $IP killallproc.sh

# Copy over our files:
echo
echo "."
echo "..."
echo "Copying DayStar files..."
echo "..."
echo "."
echo 
scp -r filesystem/* $IP:/

# Run update script on VM:
echo
echo "."
echo "..."
echo "Configuring VM and cleaning up..."
echo "..."
echo "."
echo 
ssh $IP /home/scripts/update.sh

echo
echo
echo "VM updated successfully!"
echo
echo

exit 0
