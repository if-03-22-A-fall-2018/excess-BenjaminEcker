#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  struct winsize ws;
  if (ioctl(0,TIOCGWINSZ,&ws)!=0)
  {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}

  int col=ws.ws_col;
  int row=ws.ws_row;

  FILE* fd =fopen("text.txt", "r");
  int current_char=fgetc(fd);

  int line =0;
  int chars_of_lines=0;

  while(current_char!= -1)
  {
    while(line<row-1)
    {
      while(chars_of_lines<=col)
      {
        if(current_char=='\n')
        {
          chars_of_lines=col+1;
        }
        else
        {
          printf("%c", current_char);
          chars_of_lines++;
        }
        current_char=fgetc(fd);
      }
      printf("\n");
      chars_of_lines=0;
      line++;
    }
    current_char=-1;
  }
  return 0;
}
