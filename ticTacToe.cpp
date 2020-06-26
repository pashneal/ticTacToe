#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <stack>
#include <unordered_map>
#include <math.h>
#include <functional>
using namespace std;

typedef std::pair<int, int> ipair;
typedef std::tuple<int, int, int> ituple;

unordered_map<string, ituple>dp;
unordered_map<int, string> symbols{{1,"X"},{2,"O"},{0,"."}};
vector<int> points{0,1,-1};
unordered_map <int, int> changeTurn{{1,2},{2,1}};

struct Board{
	string rep = "";
	Board(vector<vector<int>>&board , int turn){
		for (int i = 0 ; i < 3 ; i++){
			for (int  j = 0  ; j < 3 ; j++){
				rep += board[i][j];
			}
		}
		rep += turn;
	};
};
void print(vector<vector<int>>&board){
	for (auto v : board){
		for (auto i: v){
			cout << setw(5) << symbols[i];
		}
		cout << endl;
	}
}
int score (vector<vector<int>>&board){
	for (int i = 0; i < 3; i++){
		if (board[i][0] && board[i][0] == board[i][1] && board[i][2] == board[i][0])
			return points[board[i][0]];
		if (board[0][i] && board[0][i] == board[1][i] && board[2][i] == board[0][i])
			return points[board[0][i]];
	}
	if (board[0][0] && board[0][0] == board[1][1] && board[2][2] == board[0][0])
		return points[board[0][0]];
	if (board[2][0] && board[0][2] == board[1][1] && board[0][2] == board[2][0])
		return points[board[0][2]];
	return 0;
}
int dfs(vector<vector<int>>& board, int turn, int depth){
	Board b(board, turn);
	if (dp.find(b.rep) != dp.end())  return std::get<2>(dp[b.rep]);
	if (score(board)) return score(board);
	if (depth == 9) return 0;

	int bestValue = -10;
	if (turn == 2) {
		bestValue = 10;
	}
	for (int i = 0 ; i < 3; i++){
		for (int j = 0 ; j < 3; j++){
			if (!board[i][j]){
				board[i][j]=turn;
				int result = dfs(board, changeTurn[turn], depth+1);
				if (turn == 2){
					if (result < bestValue){
						dp[b.rep] = {i, j, result};
						bestValue = result;
					}
				} else {
					if (result > bestValue){
						dp[b.rep] = {i, j, result};
						bestValue = result;
					}
				}
				board[i][j] = 0;
			}
		}
	}
	return std::get<2>(dp[b.rep]);
}
int initialTurn = 1;
int main() {
	vector<vector<int>> board(3, vector<int>(3, 0));
	int depth = 0;
	int turn = 1;
	while (1){
		print(board);
		if (depth == 9 || score(board))  {
			cout << "============NEW GAME================" << endl;
			board = {{0,0,0},{0,0,0},{0,0,0}};
			turn = 1;
			depth = 0;
			print(board);
		}
		int x , y; cin >> x >> y;
		board[x][y] = turn;
		cout << "============" << endl;
		depth++;
		turn = changeTurn[turn];
		dfs(board, turn, depth++);
		auto t = dp[Board(board, turn).rep];
		board[get<0>(t)][get<1>(t)] = turn;
		turn = changeTurn[turn];
	}
}
