#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getchar_noecho()
{
  int ch;
  struct termios oldattr;
  struct termios newattr;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

int main()
{
  int ch;
  
  while (1) {
    ch = getchar_noecho();
    printf("%d\n", ch);
  }
  return 0;
}
