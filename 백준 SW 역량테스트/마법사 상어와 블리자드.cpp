#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 49, MAX_M = 100;

struct Bead {
	int y, x;
	int number;
	Bead(int _y, int _x, int _number) : y(_y), x(_x), number(_number) {}
};

int N, M, answer[4];
int Board[MAX_N][MAX_N];
pair<int, int> DS[MAX_M];
queue<Bead> Q;

int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,-1,1 };

void input() {
	cin >> N >> M;
	for(int i = 0; i < N; ++i) 
		for(int j = 0; j < N; ++j) 
			cin >> Board[i][j];
	for(int i = 0; i < M; ++i)
		cin >> DS[i].first >> DS[i].second;
}

void printQ() {
	cout << "========" << endl;
	while(!Q.empty()) {
		cout << Q.front().y << " " << Q.front().x << endl;
		Q.pop();
	}
}

void printBoard() {
	cout << "========" << endl;
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j)
			cout << Board[i][j] << " ";
		cout << endl;
	}
}

void QClear() {
	while(!Q.empty())
		Q.pop();
}

void destroyBeadsUsingIce(int t) {
	int d = DS[t].first;
	int s = DS[t].second;

	int y = (N / 2), x = (N / 2);
	for(int i = 0; i < s; ++i) {
		y += dy[d];
		x += dx[d];
		Board[y][x] = 0;
	}
}

int getNextDirection(int d) {
	if(d == 3) return 2;
	else if(d == 2) return 4;
	else if(d == 4) return 1;
	else if(d == 1) return 3;
}

// Q에 있는 구슬들을 Board에 넣는 함수
void setBreadsFromQueueToBoard() {
	int d = 1;
	int y = (N / 2), x = (N / 2);
	bool check = false;
	for(int s = 2; s <= N; ++s) {
		if(Q.empty()) 
			break;
		for(int i = 0; i < 2; ++i) {
			d = getNextDirection(d);
			int _s = s;
			while(_s--) {
				if(Q.empty()) 
					break;
				if(_s == (s-1))
					continue;
				y += dy[d];
				x += dx[d];
				Board[y][x] = Q.front().number;
				Q.pop();
			}
			// 맨 윗줄
			if(!check && i == 1 && s == N) {
				i--;
				check = true;
			}
		}
	}
}

// 빈 곳을 채우면서 구슬 재정렬하는 함수
void rearrangeBeads() {
	QClear();
	// 먼저 Q에 구슬을 넣는다.
	int d = 1;
	int y = (N / 2), x = (N / 2);
	bool check = false;
	for(int s = 2; s <= N; ++s) {
		for(int i = 0; i < 2; ++i) {
			d = getNextDirection(d);
			int _s = s;
			while(_s--) {
				if(_s == (s-1))
					continue;
				y += dy[d];
				x += dx[d];
				if(Board[y][x] > 0) {
					Q.push(Bead(y, x, Board[y][x]));
					Board[y][x] = 0;
				}
			}
			// 맨 윗줄
			if(!check && i == 1 && s == N) {
				i--;
				check = true;
			}
		}
	}

	// Q에 있는 구슬들을 Board에 옮긴다.
	setBreadsFromQueueToBoard();
}

void destroyConsecutiveBeads() {
	QClear();
	// 먼저 Q에 구슬을 넣는다.
	vector<Bead> v;
	int d, y, x;
	bool check;
	while(true) {
		d = 1;
		y = (N / 2), x = (N / 2);
		check = false;
		v.clear();
		int priorNumber = -1;
		bool check2 = false;

		for(int s = 2; s <= N; ++s) {
			for(int i = 0; i < 2; ++i) {
				d = getNextDirection(d);
				int _s = s;
				while(_s--) {
					if(_s == (s-1))
						continue;
					y += dy[d];
					x += dx[d];
					if(priorNumber != Board[y][x]) {
						if(v.size() < 4) {
							for(int j = 0; j < v.size(); ++j)
								Q.push(v[j]);
						}
						// 구슬이 폭발하면 기록한다.
						else {
							answer[v.front().number] += v.size();
							check2 = true;
						}
						v.clear();
						priorNumber = Board[y][x];
					}
					v.push_back(Bead(y, x, Board[y][x]));
					Board[y][x] = 0;
				}
				// 맨 윗줄
				if(!check && i == 1 && s == N) {
					i--;
					check = true;
				}
			}
		}

		// Q에 있는 구슬들을 Board에 옮긴다.
		setBreadsFromQueueToBoard();

		// 폭발한 구슬들이 없으면 종료
		if(!check2) break;
	}
}

void transformBeads() {
	QClear();
	int d = 1;
	int y = (N / 2), x = (N / 2);
	bool check = false;
	int priorNumber = Board[y][x-1], cnt = 0;
	for(int s = 2; s <= N; ++s) {
		for(int i = 0; i < 2; ++i) {
			d = getNextDirection(d);
			int _s = s;
			while(_s--) {
				if(_s == (s-1))
					continue;
				y += dy[d];
				x += dx[d];
				if(priorNumber != Board[y][x]) {
					Q.push(Bead(y ,x, cnt));
					Q.push(Bead(y ,x, priorNumber));
					cnt = 1;
					priorNumber = Board[y][x];
				}
				else 
					cnt++;
				Board[y][x] = 0;
			}
			// 맨 윗줄
			if(!check && i == 1 && s == N) {
				i--;
				check = true;
			}
		}
	}
	
	setBreadsFromQueueToBoard();
}

void solution() {
	for(int turn = 0; turn < M; ++turn) {
		destroyBeadsUsingIce(turn);
		rearrangeBeads();
		destroyConsecutiveBeads();
		transformBeads();
		// printBoard();
	}
	cout << answer[1] + answer[2]*2 + answer[3]*3 << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
