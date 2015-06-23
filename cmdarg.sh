#!/bin/sh
# cmdarg.sh - written by Pat OKeefe
# for use by csce215 students.
# 
# for use , in some  project.....

if [ $# -eq 1 ]; then
# if there is exactly one command line arg used with the command
# do something(s).
    echo "Your command line entry is: $1" > test
    if [ -s ./test ]; then
	cat test
    else
        echo "You should not see this line as output....."
    fi
else
										# tell the user how to use the command and exit the script
    echo "usage: `basename $0` [only_one_argument]"
    exit 1
fi
