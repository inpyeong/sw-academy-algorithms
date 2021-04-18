#include <iostream>

using namespace std;

const int MAX = 50;

int r, c, t, answer;
int m[MAX][MAX];
int cm[MAX][MAX];
pair<int, int> cleaner[2];

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

void input() {
	cin >> r >> c >> t;
	int idx = 0;
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j) {
			cin >> m[i][j];
			if(m[i][j] == -1) {
				cleaner[idx].first = i;
				cleaner[idx++].second = j;
			}
		}
}

void copyMap(int a[][MAX], int b[][MAX]) {
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			a[i][j] = b[i][j];
}

void spreadDust() {
	copyMap(cm, m);
	for(int i = 0; i < r; ++i) 
		for(int j = 0; j < c; ++j) {
			int cnt = 0;
			int value = m[i][j] / 5;
			if(m[i][j] != 0 && m[i][j] != -1) {
				for(int k = 0; k < 4; ++k) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if(ny >= 0 && ny < r && nx >= 0 && nx < c) 
						if(m[ny][nx] != -1) {
							cm[ny][nx] += value;
							cnt++;
						}
				}
			}
			cm[i][j] -= (cnt * value);
		}
	copyMap(m, cm);
}

void clean() {
	for(int idx = 0; idx < 2; ++idx) {
		if(idx == 0) {
			for(int i = cleaner[idx].first - 1; i > 0; --i) 
				m[i][0] = m[i-1][0];
			for(int i = 0; i < c-1; ++i)
				m[0][i] = m[0][i+1];
			for(int i = 1; i <= cleaner[idx].first; ++i)
				m[i-1][c-1] = m[i][c-1];
			for(int i = c-1; i > 1; --i)
				m[cleaner[idx].first][i] = m[cleaner[idx].first][i-1];
			m[cleaner[idx].first][1] = 0;
		}
		else {
			for(int i = cleaner[idx].first+1; i < r-1; ++i)
				m[i][0] = m[i+1][0];
			for(int i = 0; i < c-1; ++i)
				m[r-1][i] = m[r-1][i+1];
			for(int i = r-1; i > cleaner[idx].first; --i)
				m[i][c-1] = m[i-1][c-1];
			for(int i = c-1; i > 1; --i)
				m[cleaner[idx].first][i] = m[cleaner[idx].first][i-1];
			m[cleaner[idx].first][1] = 0;
		}
	}
}

int getDust() {
	int ret = 0;
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			if(m[i][j] != -1)
				ret += m[i][j];
	return ret;
}

void solution() {
	for(int i = 0; i < t; ++i) {
		spreadDust();
		clean();
	}
	cout << getDust() << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
