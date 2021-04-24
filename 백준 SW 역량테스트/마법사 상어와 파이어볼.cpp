#include <iostream>
#include <vector>

using namespace std;

const int MAX = 55;

struct FireBall {
	int y, x;
	int massive;
	int speed;
	int dir;
};

int n, m, k;
vector<FireBall> M[MAX][MAX];
vector<FireBall> fireBall;

int dy[] = { -1,-1,0,1,1,1,0,-1 };
int dx[] = { 0,1,1,1,0,-1,-1,-1 };
int TDir[] = { 0, 2, 4, 6 };
int FDir[] = { 1, 3, 5, 7 };

void input() {
	cin >> n >> m >> k;
	for(int i = 0; i < m; ++i) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		fireBall.push_back({ r, c, m, s, d });
		M[r][c].push_back({ r, c, m, s, d });
	}
}

void moveFireBall() {
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			M[i][j].clear();
	for(int i = 0; i < fireBall.size(); ++i) {
		int y = fireBall[i].y;
		int x = fireBall[i].x;
		int mass = fireBall[i].massive;
		int speed = fireBall[i].speed;
		int dir = fireBall[i].dir;

		int move = speed % n;
		int ny = y + dy[dir] * move;
		int nx = x + dx[dir] * move;
		if(ny > n) ny -= n;
		if(nx > n) nx -= n;
		if(ny < 1) ny += n;
		if(nx < 1) nx += n;
		M[ny][nx].push_back({ ny, nx, mass, speed, dir });
		fireBall[i].y = ny;
		fireBall[i].x = nx;
	}
}

void sumFireBall() {
	vector<FireBall> tmp;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(M[i][j].size() == 0) continue;
			if(M[i][j].size() == 1) {
				tmp.push_back(M[i][j][0]);
				continue;
			}
			int massiveSum = 0;
			int speedSum = 0;
			int cnt = M[i][j].size();

			bool even = true;
			bool odd = true;
			for(int k = 0; k < M[i][j].size(); ++k) {
				massiveSum += M[i][j][k].massive;
				speedSum += M[i][j][k].speed;
				if(M[i][j][k].dir % 2 == 0)
					odd = false;
				else
					even = false;
			}
			
			int mass = massiveSum / 5;
			int speed = speedSum / cnt;
			if(mass == 0)
				continue;
			if(even == true || odd == true)
				for(int k = 0; k < 4; ++k)
					tmp.push_back({ i, j, mass, speed, TDir[k] });
			else
				for(int k = 0; k < 4; ++k)
					tmp.push_back({ i, j, mass, speed, FDir[k] });
		}
	}
	fireBall = tmp;
}

void solution() {
	for(int i = 0; i < k; ++i) {
		moveFireBall();
		sumFireBall();
	}
	int answer = 0;
	for(int i = 0; i < fireBall.size(); ++i)
		answer += fireBall[i].massive;
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
