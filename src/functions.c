#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"


/*adds character "ch" to string "str"*/
void addchar(char *str, char ch)
{
  int i = strlen(str);
  str[i] = ch;
  str[i + 1] = '\0';
}
