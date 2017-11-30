#include "stdafx.h"
#include "Block.h"
Block::Block() {}
Block::~Block() {}
void Block::SetKind(int kind) {
	pos.clear();
	SetDir(0);
	curr_kind = kind;
	//test
		
	for (int n = 0;n < SIZE;n++) {
		pos.push_back(shape[curr_kind][curr_dir][n]);
		pos.back().second += 6;
	}
}
int Block::GetKind() {
	return curr_kind;
}
void Block::SetDir(int dir) {
	curr_dir = dir;
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
void Block::Erase() {
	for (auto &n : pos) {
		goCursor(n.first, n.second * 2);
		printf("  ");
	}
}
bool Block::isPossible(Dir dir) {
	for (auto &n : pos) {
		int y = n.first + dy[dir];
		int x = n.second*2 + dx[dir]*2;
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
vector<pair<int, int>>& Block::GetPos() {
	return pos;
}