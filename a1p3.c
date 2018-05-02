#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
  FILE *fp;
  unsigned short us;
  char b3[10];
  char move,movefromb3,win;
  fp = fopen("strategyfile.txt","rb+");
  struct strategy_struct record;
  move = atoi(argv[1]);
  move = move + '0';
  for(us = 0; us < 19683; us++) {
    b3fromus(b3,us);
    movefromb3 = get_move(b3);
    win = winner(us,b3);
    if(move == movefromb3){
      if(win == '1'||win == '2') {
        printf("[%d],",us);
        record.best_move = -1;
        record.winner = win;
        set_record(fp,us,record);
      }
      else {
        printf("%d,",us);
        evaluate_move(us,&record);
      }
    }
  }
  printf("\n");
  fclose(fp);
  return 0;
}
  

