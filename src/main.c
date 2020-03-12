#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/*FUNCTION PROTOTYPES*/
void puttag(FILE *fp, char *tag);
void closetag(FILE *fp, char *tag);
void addchar(char *str, char ch);


int main()
{
  /*VARIABLE DECLARATIONS*/
  int x; /*general-purpose int*/
  char ch; /*general-purpose char*/
  char txtname[256] = ""; /*handles name of file to be converted. 255 characters is Linux max filename*/
  char htmlname[256] = ""; /*handles name of converted file*/
  char title[128] = ""; /*handles the title of the webpage*/
  char errormsg[256] = "Hey, there's been an error. The program will be stopped and there should be a message below.";
  char css[256] = ""; /*handles the filepath to the CSS, found in the config file.*/
  FILE *txt; /*file pointer for text file*/
  FILE *html; /*file pointer for html file*/

  /*BEGINNING OF INSTRUCTIONS*/
  /*asks user for name of file and opens it into txt for reading*/
  printf("Enter name of file to convert: ");
  scanf("%s", txtname);
  txt = fopen(txtname, "r");
  if (txt == NULL)
  {
    printf("\n%s", errormsg);
    printf("Error code 2: File %s returned null. It may not exist.", htmlname);
  }
  /*sets x to position of '.' in txtname*/
  x = 0;
  for (int i = 0; txtname[i] != '\0'; i++)
  {
    if (txtname[i] == '.')
    {
      x = i;
    }
  }
  /*copies txtname to htmlname and changes the extension to .html*/
  strcpy(htmlname, txtname);
  htmlname[x + 1] = 'h';
  htmlname[x + 2] = 't';
  htmlname[x + 3] = 'm';
  htmlname[x + 4] = 'l';
  htmlname[x + 5] = '\0';
  /*creates <originalfilename>.html and opens it into html; begins creating html*/
  html = fopen(htmlname, "w");
  printf("\nCreating file %s...", htmlname);
  /*begins creating the first open-tags, from the doctype to <title>*/
  fprintf(html, "<!DOCTYPE html>");
  puttag(html, "html");
  puttag(html, "head");
  confcss(css, "/etc/tth/tth.conf"); /*gets the filepath for the css from tth.conf*/
  fprintf(html, "\n<link rel=\"stylesheet\" type=\"text/css\" href=\"%s\">\n", css); /*prints the external css link*/
  puttag(html, "title");
  /*reads the start of txt until it finds a newline; prints all characters it finds along the way*/
  ch = fgetc(txt);
  while (ch != '\n')
  {
    fprintf(html, "%c", ch);
    addchar(title, ch);
    ch = fgetc(txt);
  }
  /*closes <title> and <head>; opens <body>*/
  closetag(html, "title");
  closetag(html, "head");
  puttag(html, "body");
  /*puts string "title" in <h1> tags*/
  puttag(html, "h1");
  fprintf(html, "%s", title);
  closetag(html, "h1");
  /*if there is not another (2nd) newline after the Title, the page is formatted incorrectly. Return 1.*/
  ch = fgetc(txt);
  if (ch != '\n')
  {
    printf("\n%s", errormsg);
    printf("\nError code 1: Your page is formatted incorrectly. See the manual for details.");
    return 1;
  }
  /*get first character of actual stuff. Open the first <p> tag.*/
  ch = fgetc(txt);
  puttag(html, "p");

  /*OK, so...*/
  while (ch != EOF) /*while the current character is not the end of the file...*/
  {
    if(ch == '\n') /*If the current character is a newline, get the next character and...*/
    {
      ch = fgetc(txt);
      if (ch =='\n') /*if this next character is a newline, close the current <p> and open a new one, get the next character*/
      {
        closetag(html, "p");
        puttag(html, "p");
        ch = fgetc(txt);

      }
      else if (ch == EOF) /*if this next character is the end of the file, close off the tags.*/
      {
        closetag(html, "p");
        closetag(html, "body");
        closetag(html, "html");
      }
      else /*if this next character is something else, make a <br>, print that character, and get the next character*/
      {
        puttag(html, "br");
        fprintf(html, "%c", ch);
        ch = fgetc(txt);
      }

    }
    else if (ch == EOF) /*If the current character is the end of the file, close off the tags*/
    {
      closetag(html, "p");
      closetag(html, "body");
      closetag(html, "html");
    }
    else /*If the current character is something else, print it and get the next character*/
    {
      fprintf(html, "%c", ch);
      ch = fgetc(txt);
    }
  }


  /*Close the FILE pointers, announce the success, and return 0*/
  fclose(txt);
  fclose(html);

  printf("\nHTML file %s created from text file %s. Enjoy!\n", htmlname, txtname);

  return 0;
}


/*FUNCTION DEFINITIONS*/
/*puts string "tag" in <> brackets and prints it into fp*/
void puttag(FILE *fp, char *tag)
{
  fprintf(fp, "\n<%s>\n", tag);
}

/*puts string "tag" in </> brackets and prints it into fp*/
void closetag(FILE *fp, char *tag)
{
  fprintf(fp, "\n</%s>\n", tag);
}
