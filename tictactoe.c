#include "tictactoe.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned short b3tous(char b3[10]) {
  unsigned short us = 0;
  int i;
  int value = 1;
  for(i = 8; i>=0; i--) {
    us+=(b3[i]-'0')*value;
    value = value * 3;
  }
  return us;
}

void b3fromus(char b3[10],unsigned short us) {
  int i;
  b3[9] = '\0';
  for(i = 8; i>=0; i--) {
    b3[i] = (us%3) + '0';
    us = us/3;
  }
}

void debug(unsigned short us,char b3[10],char board[60]) {
  char move,turn;
  int i;
  unsigned short newus;
  char win;
  b3fromus(b3,us);
  printf("Board number: %d\n",us);
  printf("Board b3: %s\n",b3);
  printf("Board pic:\n");
  boardfromb3(board,b3);
  move = get_move(b3);
  printf("Move: %c\n",move);
  turn = get_turn(b3);
  printf("Turn: %c\n",turn);
  win = winner(us,b3);
  if(win == ' ' && move == '9') {
    printf("Winner: The game is a tie\n");
  }
  else {
    printf("Winner: %c\n",win);
  }
  for(i = 0; i < 9; i++) {
    newus = next(us,i);
    printf("%d -> %d\n",i,newus);
  }
}

void debug2(unsigned short us,char b3[10],char board[60]){  
  FILE *fp;
  struct strategy_struct record;
  int i;
  unsigned short newus;
  b3fromus(b3,us);
  printf("Board number: %d\n",us);
  printf("Board b3: %s\n",b3);
  printf("Board pic:\n");
  boardfromb3(board,b3);
  fp = fopen("strategyfile.txt","rb");
  get_record(fp,us,&record);
  printf("best_move = %d,winner = %c\n",record.best_move,record.winner);
  for(i = 0; i < 9; i++) {
    newus = next(us,i);
    printf("%d -> %d\n",i,newus);
  }
  fclose(fp);
} 


void boardfromb3(char board[60],char b3[10]) {
  int m,b,index,piece;
  b = 1;
  strcpy(board, "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \n");
  for(piece = 0; piece < 9; piece++) {
    m = (piece/3)*12;
    index = m + b;
    b = b + 4;
    switch(b3[piece]) {
      case '0':
        board[index] = ' ';
        break;
      case '1':
        board[index] = 'O';
        break;
      case '2': 
        board[index] = 'X';
        break;
      default:
        fprintf(stderr,"Error:bad value in b3\n");
        exit(-1);
        break;
     }
  }
  printf("%s",board);
}

void boardtob3(char board[60],char b3[10]){
  int m,b,index,piece;
  b = 1;
  for(piece = 0; piece < 9; piece++) {
    m = (piece/3)*12;
    index = m + b;
    b = b + 4;
    switch(board[index]) {
      case ' ':
        b3[piece] = '0';
        break;
      case 'O':
        b3[piece] = '1';
        break;
      case 'X': 
        b3[piece] = '2';
        break;
      default:
        fprintf(stderr,"Error:bad value in board\n");
        exit(-1);
        break;
      }
  }
  printf("b3 = %s\n",b3);
}

char get_move(char b3[10]){
  int piece,count;
  count = 0;
  for(piece = 0; piece < 9; piece++) {
    if(b3[piece] == '0'){
      count++;
    }
  }
  count = 9 - count;
  count = count + '0';
  return count;
}

char get_turn(char b3[10]) {
  int piece,count,turn;
  count = 0;
  for(piece = 0; piece < 9; piece++) {
    if(b3[piece] == '1' || b3[piece] == '2'){
      count++;
    }
  }
  if(count % 2 == 0) {
    turn = '2';
  } 
  else if(count % 2 == 1) {
    turn = '1';
  }
  return turn;
}

char winner(unsigned short us,char b3[10]) {
  char win;
  b3fromus(b3,us);  
  if((b3[0] == '1' && b3[1] == '1' && b3[2] == '1')||(b3[0] == '1' && b3[3] == '1' && b3[6] == '1')
  ||(b3[1] == '1' && b3[4] == '1' && b3[7] == '1')||(b3[2] == '1' && b3[5] == '1' && b3[8] == '1')
  ||(b3[4] == '1' && b3[5] == '1' && b3[6] == '1')||(b3[6] == '1' && b3[7] == '1' && b3[8] == '1')
  ||(b3[0] == '1' && b3[4] == '1' && b3[8] == '1')||(b3[2] == '1' && b3[4] == '1' && b3[6] == '1')) {
    win = '1'; 
  }
  else if((b3[0] == '2' && b3[1] == '2' && b3[2] == '2')||(b3[0] == '2' && b3[3] =='2' && b3[6] == '2')
  ||(b3[1] == '2' && b3[4] == '2' && b3[7] == '2')||(b3[2] == '2' && b3[5] == '2' && b3[8] == '2')
  ||(b3[4] == '2' && b3[5] == '2' && b3[6] == '2')||(b3[6] == '2' && b3[7] == '2' && b3[8] == '2')
  ||(b3[0] == '2' && b3[4] == '2' && b3[8] == '2')||(b3[2] == '2' && b3[4] == '2' && b3[6] == '2')){
    win = '2'; 
  }
  else {
    win = ' ';
  }
  return win;
}

unsigned short next(unsigned short us,int pos) {
  char b3[10];
  char turn;
  b3fromus(b3,us);
  turn = get_turn(b3);
  turn = turn - '0';
  if(b3[pos]!='0') {
    return 0;
  }
  else if(turn == 2) {
    b3[pos] = '2';
  }
  else if(turn == 1) {
    b3[pos] = '1';
  }
  us = b3tous(b3);
  return us;
}

void get_record(FILE *fp,unsigned short us,struct strategy_struct *record){
  fseek(fp,sizeof(struct strategy_struct)*us,SEEK_SET);
  fread(record,sizeof(struct strategy_struct),1,fp);
}

void set_record(FILE *fp,unsigned short us,struct strategy_struct record){
  fseek(fp,sizeof(struct strategy_struct)*us,SEEK_SET);
  fwrite(&record,sizeof(struct strategy_struct),1,fp);
}

void evaluate_move(unsigned short us,struct strategy_struct *record){
  FILE *fp;  
  int position;
  unsigned short newus;
  char turn;
  char b3[10];
  struct strategy_struct newrecord;
  int tieposition,found_tie,legal_move;
  found_tie = 0;
  fp = fopen("strategyfile.txt","rb+");
  b3fromus(b3,us);
  turn = get_turn(b3);
  for(position = 0; position < 9; position++){
    newus = next(us,position);
    if(newus == 0){
      continue;
    }
    else if(newus!=0){
      get_record(fp,us,&newrecord);
    }
    else if(newrecord.winner == turn){
      position = position + '0';
      record->best_move = position;
    }
    else if(newrecord.winner == ' ') {
      tieposition = position;
      found_tie = 1;
      legal_move = position;
    }
  }
  if(found_tie == 1){
    record->best_move = tieposition;
  }
  else if(found_tie == 0){
    record->best_move = legal_move;
  }
}

