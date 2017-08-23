#ifndef ROTATION_H
#define ROTATION_H
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

using namespace std;

void print_piece(vector < vector<char> > &piece_original);
vector<vector<char> > rotate_90degrees(vector<vector<char> > &piece_original);
void make_board();
void update_board();
void transform_M_to_x();
void drop_piece(int signum);
void turn_left();
void turn_right();
void update_rotated();
void check_full_row();
void clear_row(int full_row);
void random_piece();
void update_score();
void update_lines();
void game_over(int signum);
void new_game();

#endif // ROTATION_H
