
#include "globals.h"


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

void new_game() {
    werase(mainwin);
    mvderwin(childwin,0,0);
    box(childwin,0,0);
    mvderwin(childwin,1,1);
    werase(msgwin);
    werase(scorewin);
    box(scorewin,0,0);
    refresh();
    
    y_piece = -1;
    x_piece = board_width/2 - 1;
    score_integer = 0;
    lines = 0;
    
    can_go = true;
    menu = false;

    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = speed;
    it.it_interval = it.it_value;
    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM,drop_piece);

    random_piece();
    make_board(); 
    update_score();
    update_lines();
}

void pause_game() {
    paused = !paused;
    if (paused == true){
	mvwaddstr(msgwin,1,1,"> PAUSED <");
	touchwin(mainwin);
	refresh();

	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 0;
	it.it_interval = it.it_value;
	setitimer(ITIMER_REAL, &it, NULL);
    } else {
	werase(msgwin);
	touchwin(mainwin);
	refresh();
	
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = speed;
	it.it_interval = it.it_value;
	setitimer(ITIMER_REAL, &it, NULL);
    }
}
//---------------------------------------------------//
void options() {
    WINDOW * options_win;
    options_win = subwin(mainwin, 10 ,25 , 1 , 20);
    wclear(options_win);
    mvwprintw(options_win,1,1,"Speed:");
    mvwprintw(options_win,2,1,"1. Easy (constant)");
    mvwprintw(options_win,3,1,"2. Normal (speeds up)");
    mvwprintw(options_win,4,1,"3. Hard");
    mvwprintw(options_win,6,1,"q: Cancel");
    mvwprintw(options_win,7,1,"s: Save and exit");
    box(options_win,0,0);
    touchwin(mainwin);
    refresh();

    char ch;
    ch = 1;
    while (1) {
	ch = getch();
	if (ch == 'q') { break; }
	if (ch == '\n') {
	    mvwprintw(options_win,8,10,"*SAVED*");
	    touchwin(mainwin);
	    refresh();
	}
        switch ( ch ) {
	case '1':
	    wattron(options_win,A_BOLD);
	    mvwprintw(options_win,2,1,"1. Easy (constant)");
	    wattroff(options_win,A_BOLD);
	    mvwprintw(options_win,3,1,"2. Normal (speeds up)");
	    mvwprintw(options_win,4,1,"3. Hard");
	    touchwin(mainwin);
	    refresh();
	    break;
	case '2':	    
	    mvwprintw(options_win,2,1,"1. Easy (constant)");
	    wattron(options_win,A_BOLD);
	    mvwprintw(options_win,3,1,"2. Normal (speeds up)");
	    wattroff(options_win,A_BOLD);
	    mvwprintw(options_win,4,1,"3. Hard");
	    touchwin(mainwin);
	    refresh();
	    break;
	case '3':
	    mvwprintw(options_win,2,1,"1. Easy (constant)");
	    mvwprintw(options_win,3,1,"2. Normal (speeds up)");
	    wattron(options_win,A_BOLD);
	    mvwprintw(options_win,4,1,"3. Hard");
	    wattroff(options_win,A_BOLD);
	    touchwin(mainwin);
	    refresh();
	    break;
	}
    }
    wclear(options_win);
    delwin(options_win);
    refresh();
}

int main() {
    int ch;
    int width = board_width + 2;
    int height = board_height + 2;
    int row;
    int col;
 
    mainwin = initscr();
    noecho();
    keypad(mainwin, TRUE);

    childwin = subwin(mainwin, height, width, 0, 0);
    scorewin = subwin(mainwin,5,15,0,board_width + 3);
    msgwin = subwin(mainwin,10,25,10,board_width + 3);
    getmaxyx(stdscr,row,col);
    // start_color();
    // init_pair(1,COLOR_YELLOW
    // 	      , COLOR_BLACK);
    // wbkgd(mainwin, COLOR_PAIR(1));
    
    box(mainwin,0,0);
    mvwaddstr(mainwin , 1,  2 ,"Cave Tetris");
    mvwaddstr(mainwin , 3 , 2 ,"n: new game");
    mvwaddstr(mainwin , 4 , 2 ,"p: pause");
    mvwaddstr(mainwin , 5 , 2 ,"s: speed config");
    mvwaddstr(mainwin , 6 , 2 ,"b: board config");   
    mvwaddstr(mainwin , 7 , 2 ,"q: quit");
    mvwaddstr(mainwin , 9 , 2 ,"Controllers:");
    mvwaddstr(mainwin , 10 , 2 ,"<: move left");
    mvwaddstr(mainwin , 11 , 2 ,">: move right");
    mvwaddstr(mainwin , 12 , 2 ,"^: rotate");
    mvwaddstr(mainwin , 13 , 2 ,"V: drop faster");

    while ( (ch = getch()) != 'q' ) {
        switch ( ch ) {
	case KEY_LEFT:
	    if ((paused == false) && (menu == false)){
		turn) {
	case KEY_LEFT:
	    if ((pau_left();
	    }
		break;
	case KEY_RIGHT:
	    if ((paused == false) && (menu == false)){
		turn_right();
	    }
		break;
	case KEY_DOWN:
	    if ((paused == false) && (menu == false)){
		drop_piece(0);
	    }
		break;
	case KEY_UP:
	    if ((paused == false) && (menu == false)){
		piece_tmp = rotate_90degrees(piece);
		update_rotated();
	    }
		break;
	case 'n':
	    new_game();
	    break;
	case 'p':
	    if (menu == false) {
		pause_game();		
	    }
	    break;
	case 'o':
	    if (menu == true) {
		options();
	    }
	    break;
	}
    }
    delwin(msgwin);
    delwin(scorewin);
    delwin(childwin);
    delwin(mainwin);
    refresh();
    endwin();
    cout << "BYE";
  }
