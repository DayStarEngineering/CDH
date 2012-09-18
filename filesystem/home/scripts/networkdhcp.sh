#!/bin/bash

cp -f /etc/network/interfaces.dhcp /etc/network/interfaces
ifup eth0

exit 1
