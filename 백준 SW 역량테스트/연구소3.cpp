#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 50, MAX_M = 10, INF = 987654321;

int N, M, emptyPlace, answer = INF;
int m[MAX_N][MAX_N];
int time[MAX_N][MAX_N];
bool check[MAX_M];

vector<pair<int, int> > virus;

int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1 };

void input() {
	cin >> N >> M;
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j) {
			cin >> m[i][j];
			if(m[i][j] == 0)
				emptyPlace++;
			else if(m[i][j] == 2) 
				virus.push_back(make_pair(i, j));
		}
}

void spreadVirus(queue<pair<int, int> >& q) {
	int infectPlace = 0;
	int totalTime = 0;
	while(!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for(int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if(ny >= 0 && ny < N && nx >= 0 && nx < N) {
				if(m[ny][nx] != 1 && time[ny][nx] == -1) {
					time[ny][nx] = time[y][x] + 1;
					if(m[ny][nx] == 0) {
						infectPlace++;
						totalTime = time[ny][nx];
					}
					q.push(make_pair(ny, nx));
				}
			}
		}
	}
	if(infectPlace == emptyPlace)
		answer = min(answer, totalTime);
}

void selectVirus(int idx, int cnt) {
	if(cnt == M) {
		queue<pair<int, int> > q;
		memset(time, -1, sizeof(time));
		for(int i = 0; i < virus.size(); ++i)
			if(check[i]) {
				q.push(make_pair(virus[i].first, virus[i].second));
				time[virus[i].first][virus[i].second] = 0;
			}
		spreadVirus(q);
		return;
	}
	for(int i = idx; i < virus.size(); ++i) {
		if(!check[i]) {
			check[i] = true;
			selectVirus(i, cnt+1);
			check[i] = false;
		}
	}
}

void solution() {
	selectVirus(0, 0);
	if(answer == INF) 
		cout << -1 << endl;
	else
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
