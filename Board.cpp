#include "stdafx.h"
#include "Board.h"


Board::Board() {}
Board::Board(int b_ysize, int b_xsize, int c_ypos, int c_xpos) :
	board_ysize(b_ysize), board_xsize(b_xsize), cursor_ypos(c_ypos), cursor_xpos(c_xpos) {}

Board::~Board() {}
void Board::BasicPrint() {}
void Board::DataPrint() {}
