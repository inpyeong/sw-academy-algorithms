#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 20;

struct Seat {
	int y, x;
	int likey;
	int empty;
	Seat() : y(-1), x(-1), likey(0), empty(0) {}
};

int N;
int numOfStudents;
int Class[1+MAX_N][1+MAX_N];
int favoriteStudents[MAX_N*MAX_N][4];
vector<Seat> seats;

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

void input() {
	cin >> N;
	numOfStudents = N * N;
}

void printClass() {
	cout << "=====" << endl;
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			cout << Class[i][j] << " ";
		}
		cout << endl;
	}
}

bool cmp(Seat& a, Seat& b) {
	if(a.likey == b.likey) {
		if(a.empty == b.empty) {
			if(a.y == b.y) 
				return a.x < b.x;
			return a.y < b.y;
		}
		return a.empty > b.empty;
	}
	return a.likey > b.likey;
}

void assignSeat(int currStudent) {
	seats.clear();
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			// 누군가 앉아있는 자리라면 고려하지 않는다.
			if(Class[i][j] > 0)
				continue;
			Seat s;
			s.y = i;
			s.x = j;
			// 비어있는 자리에 대해서 인접한 칸 검사
			for(int k = 0; k < 4; ++k) {
				int ny = s.y + dy[k];
				int nx = s.x + dx[k];
				// 교실을 벗어나지 않는 좌표에서
				if(ny >= 1 && nx >= 1 && ny <= N && nx <= N) {
					// 인접한 자리가 비어있다면
					if(Class[ny][nx] == 0) 
						s.empty++;
					// 누군가 앉아있는 자리라면, 선호하는 친구가 앉았는지 검사
					else {
						for(int l = 0; l < 4; ++l) 
							if(favoriteStudents[currStudent][l] == Class[ny][nx]) {
								s.likey++;
								break;
							}
					}
				}
			}
			seats.push_back(s);
		}
	}
	sort(seats.begin(), seats.end(), cmp);
	Class[seats.front().y][seats.front().x] = currStudent;
}

int getAnswer() {
	int ret = 0;
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			int cnt = 0;
			for(int k = 0; k < 4; ++k) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if(ny >= 1 && nx >= 1 && ny <= N && nx <= N) {
					for(int l = 0; l < 4; ++l) {
						if(favoriteStudents[Class[i][j]][l] == Class[ny][nx]) {
							cnt++;
							break;
						}
					}
				}
			}
			switch(cnt) {
				case 1:
					ret += 1;
					break;
				case 2:
					ret += 10;
					break;
				case 3:
					ret += 100;
					break;
				case 4:
					ret += 1000;
					break;
			}
		}
	}
	return ret;
}

void solution() {
	for(int i = 0; i < numOfStudents; ++i) {
		int currStudent;
		cin >> currStudent;
		for(int j = 0; j < 4; ++j)
			cin >> favoriteStudents[currStudent][j];
		assignSeat(currStudent);
	}
	cout << getAnswer() << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
