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
//------------ VARIABLES -----------------//

extern WINDOW * mainwin;
extern WINDOW * childwin;
extern WINDOW * scorewin;
extern WINDOW * msgwin;
extern const int board_height;
extern const int board_width;
extern char board[20][10];
extern int x_piece;
extern int y_piece;

extern vector < vector <char> > piece;
extern vector < vector <char> > T_piece;
extern vector < vector <char> > L_piece;
extern vector < vector <char> > J_piece;
extern vector < vector <char> > S_piece;
extern vector < vector <char> > Z_piece;
extern vector < vector <char> > I_piece;
extern vector < vector <char> > O_piece;
extern vector < vector <char> > piece_tmp;

extern char actual_piece;
extern bool can_go;
extern int p_rotate;
extern int score_integer;
extern int lines;
extern struct itimerval it;
extern int speed;
extern bool paused;
extern bool menu;

// -------------- FUNCTIONS DECLARATIONS --------------//

vector < vector<char> > rotate_90degrees(vector<vector<char> > &piece_original);
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
void pause_game();
void options();
