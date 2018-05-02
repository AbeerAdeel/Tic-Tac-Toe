#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
  unsigned short us;
  char b3[10];
  char board[60];
  us = atoi(argv[1]);
  debug2(us,b3,board);
  return 0;
}

