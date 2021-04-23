#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 4;

struct Fish {
	int y, x;
	int d;
	bool alive;
};

int answer;
int M[MAX][MAX];
Fish fish[20];

int dy[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

void input() {
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j) {
			int a, b;
			cin >> a >> b;
			M[i][j] = a;
			fish[a] = { i, j, b, true };
		}
}

void copyState(int A[][4], int B[][4], Fish C[], Fish D[]) {
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			A[i][j] = B[i][j];
	for(int i = 1; i <= 16; ++i)
		C[i] = D[i];
}

void swapFish(int idx, int iidx) {
	Fish tmp = fish[idx];
	fish[idx].y = fish[iidx].y;
	fish[idx].x = fish[iidx].x;
	fish[iidx].y = tmp.y;
	fish[iidx].x = tmp.x;
}

void moveFish() {
	for(int i = 1; i <= 16; ++i) {
		if(fish[i].alive == false) 
			continue;
		int y = fish[i].y;
		int x = fish[i].x;
		int dir = fish[i].d;

		int ny = y + dy[dir];
		int nx = x + dx[dir];
		bool flag = false;
		if(ny >= 0 && nx >= 0 && ny < 4 && nx < 4) {
			if(M[ny][nx] == 0) {
				flag = true;
				fish[i].y = ny;
				fish[i].x = nx;
				M[ny][nx] = i;
				M[y][x] = 0;
			}
			else if(M[ny][nx] != -1) {
				flag = true;
				swapFish(i, M[ny][nx]);
				swap(M[y][x], M[ny][nx]);
			}
		}
		if(flag == false) {
			int nDir = dir + 1;
			if(nDir == 9) nDir = 1;
			int ny = y + dy[nDir];
			int nx = x + dx[nDir];
			while(nDir != dir) {
				if(ny >= 0 && nx >= 0 && ny < 4 && nx < 4) {
					if(M[ny][nx] == 0) {
						fish[i].y = ny;
						fish[i].x = nx;
						M[ny][nx] = i;
						M[y][x] = 0;
						fish[i].d = nDir;
						break;
					}
					else if(M[ny][nx] != -1) {
						swapFish(i, M[ny][nx]);
						swap(M[y][x], M[ny][nx]);
						fish[i].d = nDir;
						break;
					}
				}
				nDir++;
				if(nDir == 9) nDir = 1;
				ny = y + dy[nDir];
				nx = x + dx[nDir];
			}
		}
	}
}

void makeState(int y, int x, int ny, int nx, int fishNum, bool T) {
	if(T == true) {
		M[y][x] = 0;
		M[ny][nx] = -1;
		fish[fishNum].alive = false;
	}
	else {
		M[y][x] = -1;
		M[ny][nx] = fishNum;
		fish[fishNum].alive = true;
	}
}


void dfs(int y, int x, int dir, int sum) {
	answer = max(answer, sum);
	int CM[4][4];
	Fish cFish[20];
	copyState(CM, M, cFish, fish);
	moveFish();

	for(int i = 1; i <= 3; ++i) {
		int ny = y + dy[dir] * i;
		int nx = x + dx[dir] * i;
		if(nx >= 0 && ny >= 0 && nx < 4 && ny < 4) {
			if(M[ny][nx] == 0) continue;
			int fishNum = M[ny][nx];
			int nDir = fish[fishNum].d;
			makeState(y, x, ny, nx, fishNum, true);
			dfs(ny, nx, nDir, sum + fishNum);
			makeState(y, x, ny, nx, fishNum, false);
		}
		else break;
	}
	copyState(M, CM, fish, cFish);
}

void solution() {
	int fishNum = M[0][0];
	int dir = fish[fishNum].d;
	fish[fishNum].alive = false;
	M[0][0] = -1;
	dfs(0, 0, dir, fishNum);
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
