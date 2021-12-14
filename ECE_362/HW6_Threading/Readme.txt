Threaddit
***

	@inputs
        -t <num> number of threads
        -s <num> Random seed. Uses srand() initialize randomization with seed
	@outputs
		Completely sorted array
   "Sort Complete" printed or an error message
	
	@assumptions
		This program breaks array into equally sized partitions
   Sorts the partitions in different threads
   Merge results back together, multistep process multiple threads merge partitions then those partitions merged after
   Simple routine at end checks final array in sorted order and prints "Sort Complete"
	Uses array size of 64,000 elements	
   
	@errorchecking
        Checks for valid # of threads and random seed
        Prints out error message if otherwise
*/