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
	delete next_block_board;
}
void Tetris::BasicPrint() {
	goCursor(0, 0);
	for (int n = 0;n < map_ysize;n++) {
		printf("¢È"); 
		for (int m = 0;m < map_xsize;m++) printf(" ");
		printf("¢È\n");
	}
	printf("¢È");
	for (int m = 0;m < map_xsize / 2;m++) printf("¢È");
	printf("¢È");
}
bool Tetris::PossibleToMove(Dir dir) {
	if(!curr_block.isPossibleToMove(dir)) return false;
	vector<pair<int, int>> &pos = curr_block.GetPos();
	for (auto &n : pos) {
		int y = n.first + dy[dir];
		int x = n.second + dx[dir];
		if (map[y][x]) return false; 
	}
	return true;
}
bool Tetris::PossibleToRotate() {
	if (!curr_block.isPossibleToRotate()) return false;
	vector<pair<int, int>> &pos = curr_block.GetRotatePos();
	for (auto &n : pos) {
		int y = n.first;
		int x = n.second;
		if (map[y][x]) return false;
	}
	return true;
}
void Tetris::ArrayPaint() {
	vector<pair<int, int>> &pos = curr_block.GetPos();
	for (auto const &n : pos) {
		map[n.first][n.second] = true;
	}
}
void Tetris::BlinkBlock(int cursor_y, int cursor_x) {
	for (int n = 0;n < 4;n++) {
		goCursor(cursor_y, cursor_x);
		for (int m = 0;m < BASE_X_SIZE / 2;m++) printf("¢Ì");
		Sleep(BLINK_VELOCITY);
		goCursor(cursor_y, cursor_x);
		for (int m = 0;m < BASE_X_SIZE / 2;m++) printf("¡á");
		Sleep(BLINK_VELOCITY);
	}
}
void Tetris::MapErase() {
	for (int n = 0;n < BASE_Y_SIZE;n++) for (int m = 1;m <= BASE_X_SIZE / 2;m++) {
		if (map[n][m]) {
			goCursor(n, m * 2);
			printf("  ");
		}
	}
}
void Tetris::MapPrint() {
	for (int n = 0;n < BASE_Y_SIZE;n++) for (int m = 1;m <= BASE_X_SIZE / 2;m++) {
		if (map[n][m]) {
			goCursor(n, m * 2);
			printf("¡á");
		}
	}
}
void Tetris::ArrayEraseAndPull(int y) {
	for (int m = 1;m <= BASE_X_SIZE / 2;m++) map[y][m] = false;
	for (int m = 1;m <= BASE_X_SIZE / 2;m++) for (int n = y;n > 0;n--) {
		swap(map[n][m], map[n - 1][m]);
	}
}
bool Tetris::ArrayHorizon() {
	for (int n = BASE_Y_SIZE - 1; n >= 0;n--) {
		int cnt = 0;
		for (int m = 1;m <= BASE_X_SIZE / 2;m++) cnt += (map[n][m] ? 1 : 0);
		if (cnt == BASE_X_SIZE / 2) {
			BlinkBlock(n, 2);
			MapErase();
			ArrayEraseAndPull(n);
			MapPrint();
			return true;
		}
	}
	return false;
}
bool Tetris::isGameEnd() {
	if (map[1][4] || map[1][5] || map[1][6] || map[1][7] || map[1][8] || map[1][9]) return true;
	return false;
}
int Tetris::start() {
	double plus = 0;
	curr_block.SetKind(GetRandomData(0, 6));
	next_block.SetKind(GetRandomData(0, 6));
	dynamic_cast<NextBlcokBoard*>(next_block_board)->SetBlockInfo(next_block);
	next_block_board->BasicPrint();
	score_board->BasicPrint();
	BasicPrint();
	curr_block.Print();
	auto start_time = clock();
	while (dynamic_cast<ScoreBoard*>(score_board)->GetScore() < LIMIT_SCORE) {
		int key = 0;
		for (int n = 0;n < 5;n++) {
			if (_kbhit()) {
				key = _getch();
				if (key == 224) {
					key = _getch();
					switch (key) {
					case LEFT:
						if (PossibleToMove(Dir::Left)) curr_block.Move(Dir::Left);
						break;
					case RIGHT:
						if (PossibleToMove(Dir::Right)) curr_block.Move(Dir::Right);
						break;
					case DOWN:
						if (PossibleToMove(Dir::Down)) curr_block.Move(Dir::Down);
						break;
					case UP:
						if (PossibleToRotate()) curr_block.Rotate();
						break;
					default: break;
					}
				}
				else if (key == SPACE) {
					while (PossibleToMove(Dir::Down)) curr_block.Move(Dir::Down);
					while (_kbhit()) _getch();
					break;
				}
				while (_kbhit()) _getch();
			}
		}
		auto end_time = clock();
		if ((long double)(end_time - start_time) / (long double)CLOCKS_PER_SEC >= GAME_VELOCITY - plus) {
			start_time = clock();
			if (PossibleToMove(Dir::Down)) {
				curr_block.Move(Dir::Down);
			}
			else if (isGameEnd()) return dynamic_cast<ScoreBoard*>(score_board)->GetScore();
			else {
				curr_block.Print(1);
				ArrayPaint();
				while (ArrayHorizon()) {
					dynamic_cast<ScoreBoard*>(score_board)->SetScore(PLUS_SCORE);
					plus += DIFFICULTY_WEIGHT;
				}
				curr_block.SetKind(next_block.GetKind());
				next_block.SetKind(GetRandomData(0, 6));
				dynamic_cast<NextBlcokBoard*>(next_block_board)->SetBlockInfo(next_block);
				next_block_board->DataPrint();
			}
		}
	}
	return LIMIT_SCORE;
}