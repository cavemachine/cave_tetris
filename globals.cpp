#include "globals.h"

using namespace std;

WINDOW * mainwin;
WINDOW * childwin;
WINDOW * scorewin;
WINDOW * msgwin;
const int board_height = 20;
const int board_width = 10;
char board[board_height][board_width];
int x_piece = (board_width / 2) - 1;
int y_piece = -1;

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

char actual_piece;
bool can_go = true;
bool menu = true;
int p_rotate = 0;
int score_integer = 0;
int lines = 0;
struct itimerval it;
int speed = 500000;
bool paused = false;
