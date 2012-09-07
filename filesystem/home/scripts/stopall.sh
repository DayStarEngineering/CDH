#!/bin/bash

# Kills all daystar processes.
killallproc.sh

# Run sync twice to ensure buffers have been written to disk.
sync
sync
