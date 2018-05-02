#include "tictactoe.h"
#include <stdio.h>

int main(){
  FILE *fp;
  unsigned short us;
  struct strategy_struct record;
  record.best_move = -1;
  record.winner = ' ';
  fp = fopen("strategyfile.txt","wb");
  for(us = 0; us < 19683; us++){
    fwrite(&record,sizeof(record),1,fp);
  }
  fclose(fp);
  return 0;  
}
