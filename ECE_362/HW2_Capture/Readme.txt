Assignment 2 Readme 1/12/2021
Created by Alex Beaulier - Beaulier@pdx.edu

Capture and Select Program

Capture:
	Program accepts string argument to create a new file
	Checks for valid arg and doesn't already exist
	Filter program reads STDIN and writes to STDOUT and new file
	Any errors displayed should be on STDERR

Select:
	Program accepts name of file, enables user to view lines of text
	Interactively accepts input line numbers, can be sequence of numbers followed with enter key
	After reading file into buffer, program should prompt user for line and display text
	Continues until read call indiciates no more user data, ctl-D

	File has < 100 lines and total chars less than 8192

TestFile:
	File to test any user input for Select and also to input into Capture to test file generation. 