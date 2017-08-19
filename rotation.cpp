#include "rotation.h"

void print_piece(vector < vector<char> > &piece_original) {

    for (int y = 0; y < piece_original.size(); ++y) {
      cout << "\n";
        for (int x = 0; x < piece_original[0].size(); ++x) {
            std::cout << piece_original[y][x];
          }
      }
    cout << "\n";
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
