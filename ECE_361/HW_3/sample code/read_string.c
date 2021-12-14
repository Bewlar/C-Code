/**
 * read_string.c - Sample code for how to read a string from a file
 *
 * Source:  "C in a Nutshell:2e" by Peter P. and Tony C. page 429
 * Example is under the C library call fgets()
 *
 *
 */

 #include <stdio.h>

 FILE *titlefile;
 char title[256];
 int counter = 0;

 if((titlefile = fopen("titles.txt", "r")) == NULL)
	 perror("Opening title file");
 else {
	 while (fgets(title, 256, titlefile) != NULL){
		 title[strlen(title) - 1] = `0; // trim off newline character
		 printf("%3d: \"%s\"\n", ++counter, title);
	 }
	 // fgets() returned NULL: either EOF or an error occurred
	 if (feof(titlefile))
		 printf("Total: %d titles.\n", counter);
 }
