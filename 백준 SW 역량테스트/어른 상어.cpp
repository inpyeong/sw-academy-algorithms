#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 25;

struct Shark {
	int y, x;
	int dir;
	bool alive;
	vector<int> priority[5];
};

struct MapInfo {
	vector<int> v;
	int smellTime;
	int smellHost;
};

int n, m, k;
MapInfo M[MAX][MAX];
Shark shark[410];

int dy[] = { 0, -1, 1,  0, 0 };
int dx[] = { 0,  0, 0, -1, 1 };

void input() {
	cin >> n >> m >> k;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			int a;
			cin >> a;
			if(a != 0) {
				M[i][j].v.push_back(a);
				shark[a].y = i;
				shark[a].x = j;
			}
			M[i][j].smellTime = 0;
			M[i][j].smellHost = 0;
		}
	for(int i = 1; i <= m; ++i) {
		int d;
		cin >> d;
		shark[i].dir = d;
		shark[i].alive = true;
	}
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= 4; ++j) {
			int arr[4];
			cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
			for(int k = 0; k < 4; ++k)
				shark[i].priority[j].push_back(arr[k]);
		}
}

bool check() {
	for(int i = 2; i <= m; ++i)
		if(shark[i].alive == true)
			return false;
	return true;
}

void setSmell(int time) {
	for(int i = 1; i <= m; ++i) {
		if(shark[i].alive == false)
			continue;
		int y = shark[i].y;
		int x = shark[i].x;
		M[y][x].smellTime = time + k;
		M[y][x].smellHost = i;
	}
}

void moveShark(int time) {
	for(int i = 1; i <= m; ++i) {
		if(shark[i].alive == false)
			continue;
		M[shark[i].y][shark[i].x].v.clear();
	}
	for(int i = 1; i <= m; ++i) {
		if(shark[i].alive == false)
			continue;
		int y = shark[i].y;
		int x = shark[i].x;
		int dir = shark[i].dir;
		int xx, yy, dd;
		xx = yy = dd = -1;
		bool flag = false;

		for(int j = 0; j < shark[i].priority[dir].size(); ++j) {
			int nDir = shark[i].priority[dir][j];
			int ny = y + dy[nDir];
			int nx = x + dx[nDir];
			if(ny >= 0 && nx >= 0 && ny < n && nx < n) {
				if(M[ny][nx].smellTime <= time) {
					flag = true;
					M[ny][nx].v.push_back(i);
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].dir = nDir;
					break;
				}
				else {
					if(M[ny][nx].smellHost == i) {
						if(yy == -1) {
							yy = ny;
							xx = nx;
							dd = nDir;
						}
					}
				}
			}
		}
		if(flag == false) {
			M[yy][xx].v.push_back(i);
			shark[i].y = yy;
			shark[i].x = xx;
			shark[i].dir = dd;
		}
	}
}

void killShark() {
	for(int i = 1; i <= m; ++i) {
		if(shark[i].alive == false)
			continue;
		int y = shark[i].y;
		int x = shark[i].x;
		if(M[y][x].v.size() >= 2) {
			sort(M[y][x].v.begin(), M[y][x].v.end());
			int liveNum = M[y][x].v[0];
			for(int j = 1; j < M[y][x].v.size(); ++j) 
				shark[M[y][x].v[j]].alive = false;
			M[y][x].v.clear();
			M[y][x].v.push_back(liveNum);
			M[y][x].smellHost = liveNum;
		}
	}
}

void solution() {
	for(int time = 0; time < 1001; ++time) {
		if(check() == true) {
			cout << time << endl;
			return;
		}
		setSmell(time);
		moveShark(time);
		killShark();
	}
	cout << -1 << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
