#include "stdafx.h"
#include "NextBlcokBoard.h"


NextBlcokBoard::NextBlcokBoard() : data_ypos(0), data_xpos(0) {}
NextBlcokBoard::NextBlcokBoard(int b_ysize, int b_xsize, int c_ypos, int c_xpos) :
	Board(b_ysize, b_xsize, c_ypos, c_xpos), data_ypos(c_ypos + 1), data_xpos(c_xpos + 2) {}
NextBlcokBoard::~NextBlcokBoard() {}
void NextBlcokBoard::BasicPrint() {
	goCursor(cursor_ypos, cursor_xpos);
	printf("¦£");
	for (int m = 0;m < board_xsize / 2;m++) printf("¦¡");
	printf("¦¤");
	for (int n = 1;n <= board_ysize;n++) {
		goCursor(cursor_ypos + n, cursor_xpos);
		printf("¦¢");
		for (int m = 0;m < board_xsize;m++) printf(" ");
		printf("¦¢");
	}
	goCursor(cursor_ypos + board_ysize + 1, cursor_xpos);
	printf("¦¦");
	for (int m = 0;m < board_xsize / 2;m++) printf("¦¡");
	printf("¦¥");
	DataPrint();
}
void NextBlcokBoard::SetBlockInfo(Block &src) {
	block.SetKind(src.GetKind());
	block.SetDir(src.GetDir());
}
void NextBlcokBoard::DataPrint() {
	goCursor(data_ypos, data_xpos);
	printf("      <Next>");
	goCursor(data_ypos + 2, data_xpos);
	printf("kind : %d, dir : %d", block.GetKind(), block.GetDir());
}
