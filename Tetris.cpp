#include "Tetris.h"
#include "stdafx.h"
Tetris::Tetris() : Tetris(BASE_Y_SIZE, BASE_X_SIZE) {}
Tetris::Tetris(int ysize, int xsize) :map_ysize(ysize), map_xsize(xsize) {
	score_board = new ScoreBoard(1, 18, 20, 40);
	next_block_board = new NextBlcokBoard(6, 18, 10, 40);
	for (int n = 0;n < 30;n++) for (int m = 0;m < 16;m++) map[n][m] = false;
}
Tetris::~Tetris() {
	delete score_board;
}
void Tetris::BasicPrint() {
	goCursor(0, 0);
	for (int n = 0;n < map_ysize;n++) {
		printf("¦¢"); 
		for (int m = 0;m < map_xsize;m++) printf(" ");
		printf("¦¢\n");
	}
	printf("¦¦");
	for (int m = 0;m < map_xsize / 2;m++) printf("¦¡");
	printf("¦¥");
}
bool Tetris::Possible(Dir dir) {
	vector<pair<int, int>> &pos = curr_block.GetPos();
	if(!curr_block.isPossible(dir)) return false;
	for (auto &n : pos) {
		int y = n.first + dy[dir];
		int x = n.second + dx[dir];
		if (map[y][x]) return false; 
	}
	return true;
}
void Tetris::Paint() {
	vector<pair<int, int>> &pos = curr_block.GetPos();
	for (auto const &n : pos) {
		map[n.first][n.second] = true;
	}
}
void Tetris::run() {
	int down_cnt = 0;
	curr_block.SetKind(GetRandomData(0, 0));
	next_block.SetKind(GetRandomData(0, 0));
	dynamic_cast<NextBlcokBoard*>(next_block_board)->SetBlockInfo(next_block);
	next_block_board->BasicPrint();
	BasicPrint();
	score_board->BasicPrint();
	curr_block.Print();
	while (dynamic_cast<ScoreBoard*>(score_board)->GetScore() < LIMIT_SCORE) {
		int key = 0;
		for (int n = 0;n < 5;n++) {
			if (_kbhit()) {
				key = _getch();
				if (key == 224) {
					while ((key = _getch()) == 224);
					switch (key) {
					case LEFT:
						if(Possible(Dir::Left)) curr_block.Move(Dir::Left);
						break;
					case RIGHT:
						if (Possible(Dir::Right)) curr_block.Move(Dir::Right);
						break;
					case DOWN:
						if (Possible(Dir::Down)) curr_block.Move(Dir::Down);
						break;
					case UP:
						break;
					}
				}
				while (_kbhit()) _getch();
			}
		}
		if (++down_cnt >= GAME_VELOCITY) {
			down_cnt = 0;
			if (Possible(Dir::Down)) {
				curr_block.Move(Dir::Down);
			}
			else {
				curr_block.Print(1);
				Paint();
				curr_block.SetKind(next_block.GetKind());
				next_block.SetKind(GetRandomData(0, 0));
				next_block_board->BasicPrint();
				/*goCursor(0, 34);
				printf("curr : %d", curr_block.GetKind());*/
			}
		}
	}
}