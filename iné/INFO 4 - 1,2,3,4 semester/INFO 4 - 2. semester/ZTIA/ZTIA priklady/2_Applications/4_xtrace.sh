#!/bin/bash
# This simple script is used to demonstrate what messages are passed between the X11[1] graphical environment and an example clock application called xclock[2].
#
# Use:
#	chmod +x 4_xtrace.sh
#	./4_xtrace.sh
#
# Links:
#	[1] https://en.wikipedia.org/wiki/X_Window_System
#	[2] https://en.wikipedia.org/wiki/Xclock

xtrace xclock
