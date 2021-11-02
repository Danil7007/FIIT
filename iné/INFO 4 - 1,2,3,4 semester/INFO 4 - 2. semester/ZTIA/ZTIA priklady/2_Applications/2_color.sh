#!/bin/bash
# This simple BASH[1] shell script[2] is an example that demonstrates the ANSI
# escape code[3] functionality of text terminals. Note the first line of the
# file that uses the "shebang" notation[4] to point out what application to use
# to run this file.
#
# Use:
#	chmod +x ./2_color.sh # Make the text file executable in Linux/OSX/Unix
# 	./2_color.sh
#
# Links:
#	[1] https://en.wikipedia.org/wiki/Bash_%28Unix_shell%29
#	[2] https://en.wikipedia.org/wiki/Shell_script
#	[3] https://en.wikipedia.org/wiki/ANSI_X3.64
#	[4] https://en.wikipedia.org/wiki/Shebang_%28Unix%29

echo -e "\x1b[31;1mHello \x1b[30;1mWorld"
