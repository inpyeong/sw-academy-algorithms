#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_RC = 100, MAX_M = MAX_RC*MAX_RC;

struct Shark {
	int idx;
	int r, c;
	int s;
	int d;
	int z;
	Shark(int _idx, int _r, int _c, int _s, int _d, int _z): 
		idx(_idx), r(_r), c(_c), s(_s), d(_d), z(_z) {};
};

int R, C, M, answer;
vector<int> Board[1+MAX_RC][1+MAX_RC];
vector<Shark> sharks;

int dr[] = {0,-1,1,0,0};
int dc[] = {0,0,0,1,-1};

void input() {
	cin >> R >> C >> M;
	for(int i = 0; i < M; ++i) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		Board[r][c].push_back(i);
		sharks.push_back(Shark(i, r, c, s, d, z));
	}
}

void printBoard(string s) {
	cout << "====" << s << "=====" << endl;
	for(int i = 1; i <= R; ++i) {
		for(int j = 1; j <= C; ++j) {
			if(Board[i][j].size() == 0) cout << 0 << " ";
			else cout << Board[i][j].front() << " ";
		}
		cout << endl;
	}
}

void catchShark(int pos) {
	for(int i = 1; i <= R; ++i)
		if(Board[i][pos].size()) {
			answer += sharks[Board[i][pos].front()].z;
			sharks[Board[i][pos].front()].z = 0;
			Board[i][pos].clear();
			break;
		}
}

int getOppositeDirection(int d) {
	if(d == 1)
		return 2;
	else if(d == 2)
		return 1;
	else if(d == 3)
		return 4;
	else if(d == 4)
		return 3;
}

void clearBoard() {
	for(int i = 1; i <= R; ++i)
		for(int j = 1; j <= C; ++j)
			Board[i][j].clear();
}

void moveSharks() {
	clearBoard();
	for(int i = 0; i < sharks.size(); ++i) {
		if(!sharks[i].z) 
			continue;
		
		int mod;
		if(sharks[i].d == 1 || sharks[i].d == 2)
			mod = (R-1) * 2;
		else
			mod = (C-1) * 2;

		int realS = sharks[i].s % mod;

		for(int j = 0; j < realS; ++j) {
			sharks[i].r += dr[sharks[i].d];
			sharks[i].c += dc[sharks[i].d];
			
			if(sharks[i].r < 1) {
				sharks[i].r = 2;
				sharks[i].d = getOppositeDirection(sharks[i].d);
			}
			if(sharks[i].r > R) {
				sharks[i].r = R-1;
				sharks[i].d = getOppositeDirection(sharks[i].d);
			}
			if(sharks[i].c < 1) {
				sharks[i].c = 2;
				sharks[i].d = getOppositeDirection(sharks[i].d);
			}
			if(sharks[i].c > C) {
				sharks[i].c = C-1;
				sharks[i].d = getOppositeDirection(sharks[i].d);
			}
		}
	}
}

bool cmp(Shark& a, Shark& b) {
	return a.z > b.z;
}

void killSharks() {
	clearBoard();
	for(int i = 0; i < sharks.size(); ++i) {
		if(!sharks[i].z)
			continue;
		Board[sharks[i].r][sharks[i].c].push_back(i);
	}

	vector<Shark> v;
	for(int i = 1; i <= R; ++i) {
		for(int j = 1; j <= C; ++j) {
			if(Board[i][j].size() <= 1)
				continue;
			for(int k = 0; k < Board[i][j].size(); ++k) 
				v.push_back(sharks[Board[i][j][k]]);
			sort(v.begin(), v.end(), cmp);
			for(int k = 1; k < v.size(); ++k)
				sharks[v[k].idx].z = 0;
			Board[i][j].clear();
			Board[i][j].push_back(v.front().idx);
			v.clear();
		}
	}
}

void solution() {
	for(int i = 1; i <= C; ++i) {
		// printBoard("Before catching");
		catchShark(i);
		moveSharks();
		killSharks();
		// printBoard("After killing");
	}
	cout << answer << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
