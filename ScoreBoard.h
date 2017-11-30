#pragma once
#include "Board.h"
class ScoreBoard : public Board{
public:
	ScoreBoard();
	ScoreBoard(int b_ysize, int b_xsize, int c_ypos, int c_xpos);
	~ScoreBoard();
	void BasicPrint();
	void SetScore(int data);
	int GetScore();
	void DataPrint();
private:
	int score = 0;
	const int data_ypos, data_xpos;
};

