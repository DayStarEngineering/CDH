#!/bin/bash

cp /etc/network/interfaces.dhcp /etc/network/interfaces
ifup eth0

exit 1
