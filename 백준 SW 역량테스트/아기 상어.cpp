#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 20;

struct Shark {
	int y, x;
	int size;
	int eatCnt;
	int time;
}s;

struct Fish {
	int y, x;
	int dist;
};

int n;
int m[MAX][MAX];
bool discovered[MAX][MAX];
vector<Fish> v;

int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1 };

void input() {
	cin >> n;
	for(int i = 0; i < n; ++i) 
		for(int j = 0; j < n; ++j) {
			cin >> m[i][j];
			if(m[i][j] == 9) {
				s.y = i;
				s.x = j;
				s.size = 2;
				s.eatCnt = 0;
				s.time = 0;
			}
		}
}

void init() {
	v.clear();
	memset(discovered, false, sizeof(discovered));
}

void bfs(int a, int b) {
	queue<pair<pair<int, int>, int> > q;
	q.push(make_pair(make_pair(a, b), 0));
	discovered[a][b] = true;
	while(!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int dist = q.front().second;
		q.pop();
		for(int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if(ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if(discovered[ny][nx])
				continue;
			if(m[ny][nx] == 0 || m[ny][nx] == s.size) {
				discovered[ny][nx] = true;
				q.push(make_pair(make_pair(ny, nx), dist+1));
			}
			else if(m[ny][nx] < s.size) {
				Fish temp;
				temp.y = ny;
				temp.x = nx;
				temp.dist = dist+1;
				v.push_back(temp);
				discovered[ny][nx] = true;
				q.push(make_pair(make_pair(ny, nx), dist+1));
			}
		}
	}
}

void eatFish() {
	m[v.front().y][v.front().x] = 9;
	m[s.y][s.x] = 0;
	s.y = v.front().y;
	s.x = v.front().x;
	s.eatCnt++;
	s.time += v.front().dist;
	if(s.eatCnt == s.size) {
		s.eatCnt = 0;
		s.size++;
	}
}

bool cmp(Fish a, Fish b) {
	if(a.dist == b.dist) {
		if(a.y == b.y) {
			return a.x < b.x;
		}
		return a.y < b.y;
	}
	return a.dist < b.dist;
}

void solution() {
	while(true) {
		init();
		bfs(s.y, s.x);
		if(v.size() == 0) {
			cout << s.time << endl;
			break;
		}
		else if(v.size() == 1) 
			eatFish();			
		else {
			sort(v.begin(), v.end(), cmp);
			eatFish();
		}
	}
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
