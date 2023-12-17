#!/bin/bash

rhythmbox-client --play
cat ansi.txt
echo "Waiting for a key to be pressed..." 
./noEnter
rhythmbox-client --quit

clear 


exit 0
