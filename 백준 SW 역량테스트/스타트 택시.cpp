#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 25;

struct Customer {
	int y, x;
	int destY, destX;
};

struct Info {
	int y, x;
	int dist;
	int num;
};

int n, m, fuel;
int taxiY, taxiX;
int M[MAX][MAX];
bool visit[MAX][MAX];
Customer customers[MAX*MAX];

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

void input() {
	cin >> n >> m >> fuel;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			cin >> M[i][j];
			if(M[i][j] == 1)
				M[i][j] = -1;
		}
	cin >> taxiY >> taxiX;
	taxiY--;
	taxiX--;
	for(int i = 1; i <= m; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		c--;
		d--;
		customers[i] = { a, b, c, d };
		M[a][b] = i;
	}
}

bool cmp(Info a, Info b) {
	if(a.dist == b.dist) {
		if(a.y == b.y) 
			return a.x < b.x;
		return a.y < b.y;
	}
	return a.dist < b.dist;
}

int findShortestCustomer() {
	memset(visit, false, sizeof(visit));
	queue<pair<pair<int, int>, pair<int, int> > > q;
	q.push(make_pair(make_pair(taxiY, taxiX), make_pair(0, fuel)));
	visit[taxiY][taxiX] = true;
	vector<Info> v;
	while(!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int distance = q.front().second.first;
		int spareFuel = q.front().second.second;
		q.pop();
		if(M[y][x] >= 1)
			v.push_back({ y, x, distance, M[y][x] });
		if(spareFuel == 0)
			continue;
		for(int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if(ny >= 0 && nx >= 0 && ny < n && nx < n) {
				if(M[ny][nx] != -1 && visit[ny][nx] == false) {
					visit[ny][nx] = true;
					q.push(make_pair(make_pair(ny, nx), make_pair(distance+1, spareFuel-1)));
				}
			}
		}
	}
	if(v.size() == 0)
		return -1;
	sort(v.begin(), v.end(), cmp);
	M[v[0].y][v[0].x] = 0;
	fuel -= v[0].dist;
	return v[0].num;
}

bool bfs(int a, int b, int c, int d, int num) {
	memset(visit, false, sizeof(visit));
	queue<pair<pair<int, int>, pair<int, int> > > q;
	q.push(make_pair(make_pair(a, b), make_pair(0, fuel)));
	visit[a][b] = true;
	while(!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int distance = q.front().second.first;
		int spareFuel = q.front().second.second;
		q.pop();
		if(y == c && x == d) {
			fuel -= distance;
			fuel += distance * 2;
			taxiY = y;
			taxiX = x;
			return true;
		}
		if(spareFuel == 0)
			return false;
		for(int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if(ny >= 0 && nx >= 0 && ny < n && nx < n) {
				if(M[ny][nx] != -1 && visit[ny][nx] == false) {
					visit[ny][nx] = true;
					q.push(make_pair(make_pair(ny, nx), make_pair(distance+1, spareFuel-1)));
				}
			}
		}
	}
	return false;
}

void solution() {
	for(int i = 0; i < m; ++i) {
		int num = findShortestCustomer();
		if(num == -1) {
			cout << -1 << endl;
			return;
		}
		bool move = bfs(customers[num].y, customers[num].x, customers[num].destY, customers[num].destX, num);
		if(move == false) {
			cout << -1 << endl;
			return;
		}
	}
	cout << fuel << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
