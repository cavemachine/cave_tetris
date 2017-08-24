#include "globals.h"

void new_game() {
    y_piece = -1;
    x_piece = board_width/2 - 1;
    score_integer = 0;
    lines = 0;
    can_go = true;

    struct itimerval it;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 500000;
    it.it_interval = it.it_value;
    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM,drop_piece);

    werase(msgwin);
    werase(scorewin);
    box(scorewin,0,0);
    update_score();
    update_lines();

    random_piece();
    make_board(); 
}

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


void update_board() { 
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            mvwaddch(childwin,y,x,board[y][x]);
          }
      }
    touchwin(mainwin);
    refresh();
  }

void update_lines() {
    char line_tmp[10];
    char line_string[30] = "Lines: ";
    sprintf(line_tmp,"%d",lines);
    strcat(line_string,line_tmp);
    mvwaddstr(scorewin,2,1,line_string);

    touchwin(mainwin);
    refresh(); 
}

void update_score() {
    char score_tmp[10];
    char score_string[30] = "Score: ";
    sprintf(score_tmp,"%d",score_integer);
    strcat(score_string,score_tmp);
    mvwaddstr(scorewin,1,1,score_string);

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

void check_full_row() {
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            if (board[y][x] == '.') { break; }
            if ((x == board_width - 1) && (board[y][x] == 'x')) {
		clear_row(y);
	    }
	}

    }
}

void clear_row(int full_row) {
    for (int y = full_row; y >= 0; --y) {
	for (int x = board_width - 1; x >= 0; --x) {
	    if (y > 0) {
		board[y][x] = board[y-1][x];	       
	    } else {
		board[y][x] = '.';
	    }
	}
    }
    update_board();
    score_integer = score_integer + 10;
    update_score();
    ++lines;
    update_lines();
}

void random_piece() {
    srand (time(NULL));
    int v = rand() % 7;
    switch (v) {
    case 0: 
	piece = T_piece;
	actual_piece = 'T';
	break;
    case 1: 
	piece = L_piece;
	actual_piece = 'L';
	break;
    case 2: 
	piece = J_piece;
	actual_piece = 'J';
	break;
    case 3: 
        piece = S_piece;
	actual_piece = 'S';
	break;
    case 4: 
	piece = Z_piece;
	actual_piece = 'Z';
	break;
    case 5: 
        piece = I_piece;
	actual_piece = 'I';
	break;
    case 6:
	piece = O_piece;
	actual_piece = 'O';
	break;
    }
    p_rotate = 0;
    
}

void game_over(int signum) {
    signal(SIGALRM,game_over);
    mvwaddstr(msgwin,1,1,"GAME OVER");
    mvwaddstr(msgwin,3,1,"n: new game");
    mvwaddstr(msgwin,4,1,"q: quit");
    touchwin(mainwin);
    refresh();
}

//---------------------------------------------------//

int main() {
    int width = board_width + 2;
    int height = board_height + 2;
    int x_childwin = 0;
    int y_childwin = 0;
    int ch;
    
    // Initialize ncurses windows
    mainwin = initscr();
    noecho();
    keypad(mainwin, TRUE);
    childwin = subwin(mainwin, height, width, y_childwin, x_childwin);
    scorewin = subwin(mainwin,5,15,0,board_width + 3);
    msgwin = subwin(mainwin,10,25,10
		    ,board_width + 3);
   
    // Create tetris board array and show on window;
    box(childwin,0,0);
    box(scorewin,0,0);
    //box(msgwin,0,0);
    mvderwin(childwin,1,1);

    new_game();

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
	  break;
	case 'n':
	    new_game();
          }
      }
    delwin(msgwin);
    delwin(scorewin);
    delwin(childwin);
    delwin(mainwin);
    refresh();
    endwin();
    cout << "BYE\n";
  }
