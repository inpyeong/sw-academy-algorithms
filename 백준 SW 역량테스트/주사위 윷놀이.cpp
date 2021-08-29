#include <iostream>

using namespace std;

const int Board[33][6] = {
		{0, 1, 2, 3, 4, 5},
		{2, 2, 3, 4, 5, 6},
		{4, 3, 4, 5, 6, 7},
		{6, 4, 5, 6, 7, 8},
		{8, 5, 6, 7, 8, 9},
		{10, 21, 22, 23, 24, 25},
		{12, 7, 8, 9, 10, 11},
		{14, 8, 9, 10, 11, 12},
		{16, 9, 10, 11, 12, 13},
		{18, 10, 11, 12, 13, 14},
		{20, 27, 28, 24, 25, 26},
		{22, 12, 13, 14, 15, 16},
		{24, 13, 14, 15, 16, 17},
		{26, 14, 15, 16, 17, 18},
		{28, 15, 16, 17, 18, 19},
		{30, 29, 30, 31, 24, 25},
		{32, 17, 18, 19, 20, 32},
		{34, 18, 19, 20, 32, 32},
		{36, 19, 20, 32, 32, 32},
		{38, 20, 32, 32, 32, 32},
		{40, 32, 32, 32, 32, 32},
		{13, 22, 23, 24, 25, 26},
		{16, 23, 24, 25, 26, 20},
		{19, 24, 25, 26, 20, 32},
		{25, 25, 26, 20, 32, 32},
		{30, 26, 20, 32, 32, 32},
		{35, 20, 32, 32, 32, 32},
		{22, 28, 24, 25, 26, 20},
		{24, 24, 25, 26, 20, 32},
		{28, 30, 31, 24, 25, 26},
		{27, 31, 24, 25, 26, 20},
		{26, 24, 25, 26, 20, 32},
		{0, 32, 32, 32, 32, 32}
};

int Answer;
int In[10];

void input() {
    for(int i = 0; i < 10; ++i)
        cin >> In[i];
}

int getScore(int state) {
    int ret = 0;
    bool visited[33] = { false, };
    int pos[4] = { 0, };
    for(int turn = 0; turn < 10; ++turn) {
        int move = In[turn];
        int horse = (state >> (turn * 2)) & 0x03;

        int& currPos = pos[horse];
        int nextPos = Board[currPos][move];
        int addScore = Board[nextPos][0];

        if(visited[nextPos] && nextPos != 32)
            return -1;
        
        ret += addScore;
        visited[currPos] = false;
        visited[nextPos] = true;
        currPos = nextPos;
    }
    return ret;
}

void solution() {
    for(int state = 0; state < (1 << 20); ++state) {
        int candi = getScore(state);
        if(Answer < candi)
            Answer = candi;
    }
    cout << Answer << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
