/*
 * word.h - header file for the read word function in the justify application
 *
 * Source:  C Programming: A Modern Approach:2e by K.N. King.  Section 15.3
 *
 */

#ifndef WORD_H
#define WORD_H

/********************************************************** 
 * read_word: Reads the next word from the input and      *
 *            stores it in word. Makes word empty if no   *
 *            word could be read because of end-of-file.  *
 *            Truncates the word if its length exceeds    *
 *            len.                                        *
 **********************************************************/
void read_word(char *word, int len);

#endif
