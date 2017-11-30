#pragma once
#include "ScoreBoard.h"
#include "NextBlcokBoard.h"
#define BASE_Y_SIZE 30
#define BASE_X_SIZE 32
class Tetris {
public:
	Tetris();
	~Tetris();
	Tetris(int ysize, int xsize);
	void run();
	bool Possible(Dir dir);	//범위가 밖에 나가는지, 다른 블록이 막고있는지
	void Paint();
private:
	const int map_ysize, map_xsize;
	void BasicPrint();
	Board *score_board;
	Board *next_block_board;
	Block curr_block, next_block;
	bool map[BASE_Y_SIZE][BASE_X_SIZE / 2 + 1];
};

