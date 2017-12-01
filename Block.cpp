#include "stdafx.h"
#include "Block.h"
Block::Block() {}
Block::~Block() {}
void Block::SetKind(int kind) {
	pos.clear();
	curr_dir = 0;
	curr_kind = kind;
	for (int n = 0;n < SIZE;n++) {
		pos.push_back(shape[curr_kind][curr_dir][n]);
		pos.back().second += 6;
	}
}
int Block::GetKind() {
	return curr_kind;
}
int Block::GetDir() {
	return curr_dir;
}
void Block::Print(int color) {
	for (auto &n : pos) {
		goCursor(n.first, n.second * 2);
		if(!color) printf("бр");
		else printf("бс");
	}
}
void Block::Print(int plus_y, int plus_x) {
	for (int n = 0;n < SIZE;n++) {
		goCursor(plus_y + shape[curr_kind][curr_dir][n].first,
			plus_x + shape[curr_kind][curr_dir][n].second * 2);
		printf("бр");
	}
}
void Block::Erase() {
	for (auto &n : pos) {
		goCursor(n.first, n.second * 2);
		printf("  ");
	}
}
void Block::Erase(int plus_y, int plus_x) {
	for (int n = 0;n < 3;n++) for (int m = 0;m < 4;m++) {
		goCursor(n + plus_y, m * 2 + plus_x);
		printf("  ");
	}
}
bool Block::isPossibleToMove(Dir dir) {
	for (auto &n : pos) {
		int y = n.first + dy[dir];
		int x = n.second * 2 + dx[dir] * 2;
		if (y > BASE_Y_SIZE - 1 || x <= 0 || x > BASE_X_SIZE) return false;
	}
	return true;
}
bool Block::isPossibleToRotate() {
	pair<int, int> plus = pos[0];
	int rotate_dir = (curr_dir + 1) % SIZE;
	for (int n = 0;n < SIZE;n++) {
		int y = shape[curr_kind][rotate_dir][n].first + plus.first;
		int x = shape[curr_kind][rotate_dir][n].second * 2 + plus.second * 2;
		if (y > BASE_Y_SIZE - 1 || x <= 0 || x > BASE_X_SIZE) return false;
	}
	return true;
}
void Block::Move(Dir dir) {
	Erase();
	for (auto &n : pos) {
		n.first += dy[dir];
		n.second += dx[dir];
	}
	Print();
}
void Block::Rotate() {
	Erase();
	curr_dir += 1; curr_dir %= SIZE;
	pair<int, int> plus = pos[0];
	pos.clear();
	for (int n = 0;n < SIZE;n++) {
		int y = shape[curr_kind][curr_dir][n].first + plus.first;
		int x = shape[curr_kind][curr_dir][n].second + plus.second;
		pos.push_back({ y,x });
	}
	Print();
}
vector<pair<int, int>>& Block::GetPos() {
	return pos;
}
vector<pair<int, int>> Block::GetRotatePos() {
	vector<pair<int, int>> ret;
	pair<int, int> plus = pos[0];
	int rotate_dir = (curr_dir + 1) % SIZE;
	for (int n = 0;n < SIZE;n++) {
		int y = shape[curr_kind][rotate_dir][n].first + plus.first;
		int x = shape[curr_kind][rotate_dir][n].second + plus.second;
		ret.push_back({ y,x });
	}
	return ret;
}