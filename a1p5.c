#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char name[60];
  char side;
  int move,random,player_move;
  unsigned short us;
  char board[60];
  char b3[10];
  char player_turn,cpu_turn,turn;
  us = 0;
  move = 0;
  printf("SHALL WE PLAY A GAME?\n");
  printf("PLEASE ENTER YOUR NAME: ");
  fgets(name,60,stdin);
  printf("GREETINGS %s\n",name);
  printf("Which side would you like to play (X/O)?");
  scanf("%c",&side);
  if(side == 'X'){
    printf("Ok,you will be X; I will be O.\n");
    player_turn = '2';
    cpu_turn = '1';
  }
  else if(side == 'O') {
    printf("Ok,you will be O; I will be X.\n");
    player_turn = '1';
    cpu_turn = '2';
  }
  do {
    b3fromus(b3,us);
    turn = get_turn(b3);
    if(player_turn == turn) {
      printf("Your turn; chose a move [0-8]: ");
      scanf("%d",&player_move);;
      b3[player_move] = player_turn;
      boardfromb3(board,b3);
      turn = get_turn(b3);
      move++;
      if(cpu_turn == turn) {
        random = rand() % 10;
        printf("My turn; my move is %d\n",random);
        b3[random] = cpu_turn;
        boardfromb3(board,b3);
        turn = get_turn(b3);
        move++;
      }
      else if(player_turn == turn){
        printf("Your turn; chose a move [0-8]: ");
        scanf("%d",&player_move);;
        b3[player_move] = player_turn;
        boardfromb3(board,b3);
        turn = get_turn(b3);
        move++;
      }
    }
    else if(cpu_turn == turn){
      random = rand() % 10;
      printf("My turn; my move is %d\n",random);
      b3[random] = cpu_turn;
      boardfromb3(board,b3);
      turn = get_turn(b3);
      move++;
      if(player_turn == turn){
        printf("Your turn; chose a move [0-8]: ");
        scanf("%d",&player_move);;
        b3[player_move] = player_turn;
        boardfromb3(board,b3);
        turn = get_turn(b3);
        move++;
      }
      else if(cpu_turn == turn) {
        random = rand() % 10;
        printf("My turn; my move is %d\n",random);
        b3[random] = cpu_turn;
        boardfromb3(board,b3);
        turn = get_turn(b3);
        move++;
      }
    }
  }while(move!=9);
  return 0;
}
