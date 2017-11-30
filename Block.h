#pragma once
#include <vector>
#include <functional>
using namespace std;
enum Dir { Left, Right, Down };
#define SIZE 4
class Block{
public:
	Block();
	~Block();
	void SetKind(int kind);
	int GetKind();
	void SetDir(int dir);
	int GetDir();
	vector<pair<int, int>>& GetPos();
	void Erase();
	void Print(int color = 0);
	void Move(Dir dir);
	bool isPossible(Dir dir);
private:
	int curr_kind, curr_dir;
	vector<pair<int, int>> pos;
	const pair<int,int> shape[1][4][4] = {
		{
			{ { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 } },
			{ { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 } },
			{ { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 } },
			{ { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 } }
		}
	};
};

