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


using namespace std;

void print_piece(vector < vector<char> > &piece_original);
vector<vector<char> > rotate_90degrees(vector<vector<char> > &piece_original);


#endif // ROTATION_H
