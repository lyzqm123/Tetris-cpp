#include "stdafx.h"
#include "ScoreBoard.h"


ScoreBoard::ScoreBoard() : data_ypos(0), data_xpos(0) {}
ScoreBoard::ScoreBoard(int b_ysize, int b_xsize, int c_ypos, int c_xpos) :
	Board(b_ysize, b_xsize, c_ypos, c_xpos), data_ypos(c_ypos + 1), data_xpos(c_xpos + 2) {}
ScoreBoard::~ScoreBoard() {}
void ScoreBoard::BasicPrint() {
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
void ScoreBoard::DataPrint() {
	goCursor(data_ypos, data_xpos);
	printf("Score : %d", score);
}
void ScoreBoard::SetScore(int data) {
	this->score += data;
	DataPrint();
}
int ScoreBoard::GetScore() {
	return this->score;
}