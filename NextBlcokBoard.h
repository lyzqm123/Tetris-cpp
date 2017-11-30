#pragma once
#include "Board.h"
#include "Block.h"
class NextBlcokBoard :public Board{
public:
	NextBlcokBoard();
	NextBlcokBoard(int b_ysize, int b_xsize, int c_ypos, int c_xpos);
	~NextBlcokBoard();
	void BasicPrint();
	void DataPrint();
	void SetBlockInfo(Block &);
private:
	const int data_ypos, data_xpos;
	Block block;
};

