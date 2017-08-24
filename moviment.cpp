#include "globals.h"
using namespace std;

void drop_piece(int signum) {
    update_board();
    for (int y = 0; y < piece.size(); ++y) {
	for (int x = 0; x < piece[0].size(); ++x) {
	    if (piece[y][x] == 'M')
		if ((board[y_piece+1+y][x_piece+x] == 'x') || (y_piece+1 + piece.size() > board_height)) {
		    can_go = false;
		}
	}
    }  
    if (can_go == true) {
	++y_piece;
	for (int y = 0; y < piece.size(); ++y) {
	    for (int x = 0; x < piece[0].size(); ++x) {
		if (piece[y][x] == 'M') {
		    mvwaddch(childwin,y_piece+y,x_piece+x,'M');
		}	
	    }
	}
	touchwin(mainwin);
	refresh();
        
    } else {
	if (y_piece == -1) {
	    game_over(0);
	} else {
    	transform_M_to_x();
    	check_full_row();
    	update_board();
    	y_piece = -1;
    	x_piece = board_width/2 - 1;
    	random_piece();
    	score_integer = score_integer + 2;
    	update_score();
        can_go = true;
	}
    }
}

void turn_left() {
    bool can_go_left = true;
    for (size_t y = 0; y < piece.size(); ++y) {
        for (size_t x = 0; x < piece[0].size(); ++x) {
           if (piece[y][x] == 'M') {
               if ((board[y_piece+y][x_piece+x-1] == 'x') || (x_piece+x == 0)) {
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
               if ((board[y_piece+y][x_piece+x+1] == 'x') || (x_piece + x == board_width - 1)) {
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

vector< vector<char> > rotate_90degrees(vector < vector<char> > &piece_original) {

    int height_ = piece_original.size();
    int width_ = piece_original[0].size();
    vector < vector<char> > piece_l_temp(width_,vector<char>(height_)); //  = piece_l_temp[3][2]

    // Put 2D array into 1D array
    int piece_in_1_row[width_*height_];
    int j = 0;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            piece_in_1_row[j] = piece_original[y][x];
            ++j;
          }
      }
    --j;
    // Transfer 1D array into new rotated array
    for (int x = 0; x < piece_l_temp[0].size(); ++x) {
        for (int y = piece_l_temp.size() - 1; y >= 0; --y) {
            piece_l_temp[y][x] = piece_in_1_row[j];
            --j;
          }
      }
    return piece_l_temp;
  }


void update_rotated() {
    bool can_rotate = true;
    int x_rot = 0;
    int y_rot = 0;
    
    if (p_rotate < 3) { ++p_rotate; } else { p_rotate = 0; }
    if ((actual_piece != 'S') && (actual_piece != 'Z') && (actual_piece != 'O')) {
	if ((actual_piece == 'L') || (actual_piece == 'J') || (actual_piece == 'T')) {
	    switch (p_rotate) {
	    case 0:
		break;
	    case 1:
		x_rot = 1;
		break;
	    case 2:
		x_rot = -1;
		y_rot = 1;    
		break;
	    case 3:
		x_rot = 0;
		y_rot = -1;
		break;
	    }
	}
	if (actual_piece == 'I') {
	    switch (p_rotate) {
	    case 0:
		x_rot = -2;
		y_rot = 2;  
		break;
	    case 1:
		x_rot = 2;
		y_rot = -2;
		break;
	    case 2:
		x_rot = -2;
		y_rot = 2;    
		break;
	    case 3:
		x_rot = 2;
		y_rot = -2;
		break;
	    }   
	}
    }
    for (int y = 0; y < piece_tmp.size(); ++y) {
        for (int x = 0; x < piece_tmp[0].size(); ++x) {
            if (piece_tmp[y][x] == 'M') {
                if ((board[y_piece + y + y_rot][x_piece + x + x_rot] == 'x') || (x_piece+x+x_rot > board_width - 1) || (x_piece+x+x_rot < 0) || (y_piece+y+y_rot > board_height - 1)) {
                    can_rotate = false;
                  }
              }
          }
      }
    if (can_rotate == true) {
	update_board();		
        piece = piece_tmp;
	x_piece = x_piece + x_rot;
	y_piece = y_piece + y_rot;
        for (int y = 0; y < piece.size(); ++y) {
            for (int x = 0; x < piece[0].size(); ++x) {
                if (piece[y][x] == 'M') {
                    mvwaddch(childwin,y_piece+y,x_piece+x,'M');
                  }
              }
          }
        touchwin(mainwin);
        refresh();
    } else {
      --p_rotate;
    }
  }
