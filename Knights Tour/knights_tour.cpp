/*
Name: Anthony Giordano
Date: 03/27/21
File: knights_tour.cpp
Brief: This is the implementation file for knights_tour problem
*/


#include <iostream>
#include <iomanip>
#include "knights_tour.h"
using namespace std;

KnightsTour::KnightsTour(int board_size) {
  this->board_size = board_size;

  this->board.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    this->board[i].resize(board_size);
  }
}

void KnightsTour::print() {
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++)
      cout << setw(4) << this->board[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
}

// Function: get_moves()
//    Desc: Get the row and column indices of all valid
//          knight moves reachable from position row, col.
//          An invalid move would be one that sends the
//          knight off the edge of the board or
//          to a position that has already been visited.
//          
//    int row         - Current row position of knight.
//    int col         - Current column position of knight.
//    int row_moves[] - Array to store row indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int col_moves[] - Array to store column indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int num_moves -   Number of valid moves found. Corresponds
//                      to the sizes of row_moves and col_moves.

void KnightsTour::get_moves(
  int row, int col, 
  int row_moves[], int col_moves[], int& num_moves) 
{
    int temp_row_moves[8] = { 2, 1, -1, -2, -2, -1, 1, 2};
    int temp_col_moves[8] = { 1, 2, 2, 1, -1, -2, -2, -1};
    for (int i = 0; i < 8; i++) {
        int x = row + temp_row_moves[i];
        int y = col + temp_col_moves[i];
        if (x >= 0 && y >= 0 && x < 5 && y < 5 && board[x][y] == 0){
          row_moves[num_moves] = x;
          col_moves[num_moves] = y;
          num_moves++;
        }
    }
}

// Function: move() --> Recursive
//     int row        - Current row position of knight.
//     int col        - Current column position of knight.
//     int& m         - Current move id in tour.
//                      Stored in board at position
//                      row, col.
//     int& num_tours - Total number of tours found.

void KnightsTour::move(int row, int col, int& m, int& num_tours) {
  //initializes arrrays and variables to pass into get_moves
  int row_moves[8];
  int col_moves[8];
  int num_moves = 0;

  //since m starts at 0 add 1 to go from 1-25
  board[row][col] = m+1;
  //m starts at 0 so m=24 would be the highest value
  if(m >= 24){
    print();
    num_tours++;
    //backtracking
    m--;
    board[row][col] = 0;
    return;
  }
  //gets moves
  get_moves(row, col, row_moves, col_moves, num_moves);
  for(int i = 0; i<num_moves; i ++){
    m++;
    move(row_moves[i], col_moves[i], m, num_tours);
  }
  //backtracking for when there are no moves left or m=24
  board[row][col] = 0;
  m--;
}

int KnightsTour::generate(int row, int col) {
  int m = 0;
  int num_tours = 0;
  move(row, col, m, num_tours);
  return num_tours;
}
