#!/bin/bash

# Remove .svn files
for file in $(find /* | grep .svn)
do
    rm -r $file >/dev/null
done

# Remove .removeme files
for file in $(find /* | grep .removeme)
do
    rm -r $file >/dev/null
done

# Remove "~"s:
rm -f /home/bin/*~
rm -f /home/scripts/*~
rm -f /home/conf/*~
rm -f /etc/network/*~
rm -f /etc/init.d/*~
rm -f /etc/rc0.d/*~
rm -f /etc/*~

# Set permissions
chmod +x /home/bin/*
chmod +x /home/scripts/*

# Create links:
for file in $(ls /home/bin/)
do
	ln -s /home/bin/$file /usr/bin/$file
done 

for file in $(ls /home/scripts/ | grep -v update.sh)
do
	ln -s /home/scripts/$file /usr/bin/$file
done

# Link start-up script:
cp /etc/rc0.d/K99daystar /etc/rc6.d/K99daystar

# Start sat in default mode:
startvital.sh &

# Remove this script:
rm -f /home/scripts/update.sh

exit
