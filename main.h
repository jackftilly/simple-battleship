#ifndef BATTLESHIP
#define BATTLESHIP
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int full_game ( void );
void print_game_rules ( void );
void users_input ( char board[10][10], char hit_board[10][10], FILE *outfile );
void computer_input ( char board[10][10], char hit_board[10][10], FILE *outfile );
void initialize_board ( char board[10][10] );
void create_board ( char board[10][10] );
void rand_board ( char board[10][10] );
void play_game ( void );
#endif
