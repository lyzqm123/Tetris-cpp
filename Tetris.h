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
	int start();
	bool PossibleToMove(Dir dir);		//방향키 입력받았을 때 가능한 지
	bool PossibleToRotate();			//현재 블록을 회전시킬 때 가능한 지
	void ArrayPaint();
	bool ArrayHorizon();
	void BlinkBlock(int cursor_y, int cursor_x);
	void ArrayEraseAndPull(int y);
	void MapErase();
	void MapPrint();
	bool isGameEnd();
private:
	const int map_ysize, map_xsize;
	void BasicPrint();
	Board *score_board;
	Board *next_block_board;
	Block curr_block, next_block;
	bool map[BASE_Y_SIZE][BASE_X_SIZE / 2 + 1];
};

