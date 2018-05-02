#include <stdio.h>
#include "tictactoe.h"
#include <stdlib.h>

int main(int argc,char *argv[]){
  unsigned short us;
  char b3[10];
  char board[60];
  us = atoi(argv[1]);
  debug(us,b3,board);
  return 0;
}
