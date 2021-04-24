#include <iostream>

using namespace std;

const int MAX = 510;

int n, answer;
int M[MAX][MAX];

int dy[] = { 0,  0, 1, -1 };
int dx[] = { 1, -1, 0,  0 };

int ydy[4][10] = { { -1, 1, -1, 1, -1, 1, -2, 2, 0, 0 },{ -1, 1, -1, 1, -1, 1, -2, 2, 0, 0 },
				  { 0, 0, 1, 1, 2, 2, 1, 1, 3, 2}, { 0, 0, -1, -1, -2, -2, -1, -1, -3, -2} };
int xdx[4][10] = { { 0, 0, 1, 1, 2, 2, 1, 1, 3, 2}, { 0, 0, -1, -1, -2, -2, -1, -1, -3, -2},
				  { -1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {-1, 1, -1, 1, -1, 1, -2, 2, 0, 0} };
int Percent[9] = { 1, 1, 7, 7, 10, 10, 2, 2, 5 };

void input() {
	cin >> n;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> M[i][j];
}

void spreadSand(int y, int x, int dir) {
	int yy = y + dy[dir];
	int xx = x + dx[dir];
	if(M[yy][xx] == 0)
		return;

	int sand = M[yy][xx];
	int temp = sand;
	for(int i = 0; i < 9; ++i) {
		int ny = y + ydy[dir][i];
		int nx = x + xdx[dir][i];
		int per = Percent[i];
		int plus = (temp * per) / 100;

		if(ny < 1 || nx < 1 || ny > n || nx > n)
			answer += plus;
		else M[ny][nx] += plus;
		sand -= plus;
	}
	int ny = y + ydy[dir][9];
	int nx = x + xdx[dir][9];

	if(ny < 1 || nx < 1 || ny > n || nx > n)
		answer += sand;
	else M[ny][nx] += sand;
	M[yy][xx] = 0;
}

int changeDir(int dir) {
	if(dir == 0) return 3;
	if(dir == 1) return 2;
	if(dir == 2) return 0;
	if(dir == 3) return 1;
}

void solution() {
	int y = (n+1) / 2;
	int x = (n+1) / 2;
	int dir = 1;
	int moveCnt = 1;
	while(true) {
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < moveCnt; ++j) {
				spreadSand(y, x, dir);
				y += dy[dir];
				x += dx[dir];
			}
			dir = changeDir(dir);
		}
		moveCnt++;
		if(moveCnt == n) {
			for(int j = 0; j < moveCnt; ++j) {
				spreadSand(y, x, dir);
				y += dy[dir];
				x += dx[dir];
			}
			break;
		}
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
