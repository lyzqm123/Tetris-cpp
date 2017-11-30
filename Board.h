#pragma once
class Board{
public:
	Board();
	Board(int b_ysize, int b_xsize, int c_ypos, int c_xpos);
	~Board();
	virtual void BasicPrint();
	virtual void DataPrint();
protected:
	int board_ysize, board_xsize;
	int cursor_ypos, cursor_xpos;
};

