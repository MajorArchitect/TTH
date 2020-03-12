#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/*finds CSS configuration in "filepath" and puts it in "str"*/
void confcss(char *str, char *filepath)
{
  FILE *fp;

  fp = fopen(filepath, "r");

  fgets(str, 255, fp);

  if (str[0] == '#')
  {
    str = NULL;
  }

  str[strlen(str) - 1] = '\0';

}
