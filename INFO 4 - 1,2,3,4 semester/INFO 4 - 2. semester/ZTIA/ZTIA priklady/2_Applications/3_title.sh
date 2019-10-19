#!/bin/bash
# This simple BASH[1] shell script[2] is an example that demonstrates another ANSI escape code[3] functionality. When called from commandline the title of the terminal will be set to the first argument passed into the script.
#
# Use:
#	chmod +x ./3_title.sh # Make the file executable in Linux/OSX/Unix
# 	./3_title.sh "Hello World"
#
# Links:
#	[1] https://en.wikipedia.org/wiki/Bash_%28Unix_shell%29
#	[2] https://en.wikipedia.org/wiki/Shell_script
#	[3] https://en.wikipedia.org/wiki/ANSI_X3.64

echo -e "\033]0;${1}\007" 
