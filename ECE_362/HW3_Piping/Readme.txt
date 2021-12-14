Flip
***

	@inputs
        1 flags(-l or -u or combination of both)
		2 Alphabetic characters(any ASCII value also)
	@outputs
		1 -l alphabetic characters output in lowercase
		2 -u alphabetic characters output in uppercase
		3 -l -u or -u -l uppercase -> lowercase output and lowercase -> uppercase output
	
	@assumptions
		1 input of -l and -u will be in argv[1] and argv[2] in either order
		2 character inputs may contain symbol ASCII. Need the range of a-z and A-Z in value. 
		3 character flipping will have 3 modes - mode 1 flip to lower, mode 2 flip to upper, mode 3 flip both
		
	@errorchecking
        1 Name of file validity
        2 Line sequence validity 0<value<=100, Non existent lines return 0
*/

Piper
***
Execute after compiling flip and piper. 
Input any characters in ASCII and outputs to lower and upper txt files.
Remaining output moves to STDOUT and uses both upper and lower config flags.