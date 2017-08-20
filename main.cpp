﻿#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <signal.h>
#include "rotation.h"

using namespace std;
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

WINDOW * mainwin;
WINDOW * childwin;
char board[20][10];
int board_height = 20;
int board_width = 10;
int x_piece = 5; 
int y_piece = 0;

vector < vector <char> > piece = {{'M'}};

vector < vector <char> > T_piece = {{'.','M', '.'},
				    {'M','M', 'M'}};
vector < vector <char> > L_piece = {{'.','.', 'M'},
				    {'M','M', 'M'}};
vector < vector <char> > J_piece = {{'M','.', '.'},
				    {'M','M', 'M'}};
vector < vector <char> > S_piece = {{'.','M', 'M'},
				    {'M','M', '.'}};
vector < vector <char> > Z_piece = {{'M','M', '.'},
				    {'.','M', 'M'}};
vector < vector <char> > I_piece = {{'M','M','M','M'}};
vector < vector <char> > O_piece = {{'M','M'},
				    {'M','M'}};

vector < vector <char> > piece_tmp;

//---------------------------------------------------//

void make_board() {
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            board[y][x] = '.';
            mvwaddch(childwin,y,x,board[y][x]);
          }
      }
    touchwin(mainwin);
    refresh();
  }

void update_rotated() {
    bool can_rotate = true;
    for (int y = 0; y < piece_tmp.size(); ++y) {
        for (int x = 0; x < piece_tmp[0].size(); ++x) {
            if (piece_tmp[y][x] == 'M') {
                if ((board[y_piece+y][x_piece+x] == 'x') || (x_piece+x > 9) || (x_piece+x < 0) || (y_piece+y > 19)) {
                    can_rotate = false;
                  }
              }
          }
      }
    if (can_rotate == true) {
        piece = piece_tmp;
        update_board();
        for (int y = 0; y < piece.size(); ++y) {
            for (int x = 0; x < piece[0].size(); ++x) {
                if (piece[y][x] == 'M') {
                    mvwaddch(childwin,y_piece+y,x_piece+x,'M');
                  }
              }
          }
        touchwin(mainwin);
        refresh();
      }
  }

void update_board() { 
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            mvwaddch(childwin,y,x,board[y][x]);
          }
      }
    touchwin(mainwin);
    refresh();
  }

void transform_M_to_x() { 
    for (int y = 0; y < piece.size(); ++y) {
        for (int x = 0; x < piece[0].size(); ++x) {
            if (piece[y][x] == 'M') {
                board[y_piece+y][x_piece+x] = 'x';

          }
      }
  }
}

void clear_row(int full_row) {
   mvwaddstr(mainwin,full_row+1,13,"<--FULL ROW");
   refresh();
  }

void check_full_row() {
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            if (board[y][x] == '.') { break; }
            if ((x == 9) && (board[y][x] == 'x')) { clear_row(y); }
          }

      }
  }

void random_piece() {
    srand (time(NULL));
    int v = rand() % 6;
    switch (v) {
    case 0: 
	piece = T_piece;
	break;
    case 1: 
	piece = L_piece;
	break;
    case 2: 
	piece = J_piece;
	break;
    case 3: 
        piece = S_piece;
	break;
    case 4: 
	piece = Z_piece;
	break;
    case 5: 
        piece = I_piece;
	break;
    case 6:
	piece = O_piece;
	break;
    }
}
void drop_piece(int signum) {
   bool can_go = true;
   for (size_t y = 0; y < piece.size(); ++y) {
       for (size_t x = 0; x < piece[0].size(); ++x) {
           if (piece[y][x] == 'M') {
               if ((board[y_piece+1+y][x_piece+x] == 'x') || (y_piece+1 + piece.size() > 20)) {
                   can_go = false;
             }
         }
     }
   }
   update_board();
   if (can_go == true) {
      for (int y = 0; y < piece.size(); ++y) {
          for (int x = 0; x < piece[0].size(); ++x) {
              if (piece[y][x] == 'M') {
                  mvwaddch(childwin,y_piece+y,x_piece+x,'M');
                }
            }
        }
      touchwin(mainwin);
      refresh();
      ++y_piece;
     } else {
       transform_M_to_x();
       check_full_row();
       update_board();
       y_piece = 0;
       x_piece = 5;
       random_piece();
     }
  }

void turn_left() {
    bool can_go_left = true;
    for (size_t y = 0; y < piece.size(); ++y) {
        for (size_t x = 0; x < piece[0].size(); ++x) {
           if (piece[y][x] == 'M') {
               if ((board[y_piece+y-1][x_piece+x-1] == 'x') || (x_piece+x == 0)) {
                   can_go_left = false; // DAMN
                   mvwaddch(mainwin,22,26,'P');
                   refresh();
                   break;
                 }
             }
          }
       }
    if (can_go_left == true) {
        update_board();
        for (int y = 0; y < piece.size(); ++y) {
            for (int x = 0; x < piece[0].size(); ++x) {
                if (piece[y][x] == 'M') {
                    mvwaddch(childwin,y_piece+y,x_piece+x-1,'M');
                  }
              }
          }
        touchwin(mainwin);
        refresh();
       --x_piece;
      }
  }

void turn_right() {
    bool can_go_right = true;
    for (size_t y = 0; y < piece.size(); ++y) {
        for (size_t x = 0; x < piece[0].size(); ++x) {
           if (piece[y][x] == 'M') {
               if ((board[y_piece+y-1][x_piece+x+1] == 'x') || (x_piece + x == 9)) {
                   can_go_right = false;
                   mvwaddch(mainwin,22,26,'P');
                   refresh();
                   break;
                 }
             }
          }
       }

    if (can_go_right == true) {
        update_board();
        for (int y = 0; y < piece.size(); ++y) {
            for (int x = 0; x < piece[0].size(); ++x) {
                if (piece[y][x] == 'M') {
                    mvwaddch(childwin,y_piece+y,x_piece+x+1,'M');
                  }
              }
          }
        touchwin(mainwin);
        refresh();
       ++x_piece;
      }
  }

//---------------------------------------------------//

int main() {
    int width = 12, height = 22;
    int x_childwin = 0;
    int y_childwin = 0;
    int ch;
    
    random_piece();
    // Setup Timer and Signal handler
    struct itimerval it;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 500000;
    it.it_interval = it.it_value;
    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM,drop_piece);

    // Initialize ncurses windows
    mainwin = initscr();
    noecho();
    keypad(mainwin, TRUE);
    childwin = subwin(mainwin, height, width, y_childwin, x_childwin);

    // Create tetris board array and show on window;
    box(childwin,0,0);
    mvderwin(childwin,1,1);
    make_board();

    while ( (ch = getch()) != 'q' ) {
        switch ( ch ) {
        case KEY_LEFT:
          turn_left();
          break;
        case KEY_RIGHT:
          turn_right();
          break;
        case KEY_DOWN:
          drop_piece(0);
          break;
        case KEY_UP:
          piece_tmp = rotate_90degrees(piece);
          update_rotated();
          }
      }

    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
  }


