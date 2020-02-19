#
# PROGRAM:    assignment1.cc
# PROGRAMMER: Margaret Higginbotham
# LOGON ID:   Z1793581
# DATE DUE:   January 29, 2018
#

# Complier Variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assignment1.exe: assignment1.cc
	g++ $(CCFLAGS) assignment1.cc -o assignment1.exe

# Pseudo-target to remove object code and executable files
clean:
	-rm assignment1.exe
