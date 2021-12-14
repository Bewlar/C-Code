/*
 * word.c - source code for the word processing functions in the justify application
 *
 * Source:  C Programming: A Modern Approach:2e by K.N. King.  Section 15.3
 *
 */
 
#include <stdio.h>
#include "word.h"

int read_char(void)
{
  int ch = getchar();

  if (ch == '\n' || ch == '\t')
    return ' ';
  return ch;
}


void read_word(char *word, int len)
{
  int ch, pos = 0;
  
  while ((ch = read_char()) == ' ')
    ;
  while (ch != ' ' && ch != EOF) {
    if (pos < len)
      word[pos++] = ch;
    ch = read_char();
  }
  word[pos] = '\0';
}
