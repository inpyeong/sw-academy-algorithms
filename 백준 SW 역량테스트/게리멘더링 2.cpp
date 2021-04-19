#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 20, INF = 987654321;

struct Coord {
	int y, x;
};

int n, answer = INF;
int m[MAX][MAX];
int label[MAX][MAX];
Coord pos[4];

void input() {
	cin >> n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> m[i][j];
}

bool isOk(int y, int x, int d1, int d2) {
	if(y+d1 >= n || x-d1 < 0) 
		return false;
	if(y+d2 >= n || x+d2 >= n)
		return false;
	if(y+d1+d2 >= n || x-d1+d2 < 0 || x-d1+d2 >= n)
		return false;
	return true;
}

void printLabel() {
	cout << "===========" << endl;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			cout << label[i][j] << " ";
		cout << endl;
	}
	cout << "===========" << endl;
}

void calc() {
	int sum[6] = {0,};
	for(int i = 0; i < n; ++i) 
		for(int j = 0; j < n; ++j) 
			sum[label[i][j]] += m[i][j];
	sort(sum, sum+6);
	int diff = sum[5] - sum[1];
	answer = min(answer, diff);
}

void labeling() {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			label[i][j] = 5;
	int sub = 0, plus = 0;
	// 1
	for(int i = 0; i < pos[1].y; ++i) {
		if(i >= pos[0].y)
			sub++;
		for(int j = 0; j <= pos[0].x-sub; ++j)
			label[i][j] = 1;
	}
	// 2
	for(int i = 0; i <= pos[2].y; ++i) {
		if(i > pos[0].y) plus++;
		for(int j = pos[0].x+1+plus; j < n; ++j)
			label[i][j] = 2;
	}
	// 3
	sub = 0;
	for(int i = n-1; i >= pos[1].y; --i) {
		if(i < pos[3].y)
			sub++;
		for(int j = 0; j < pos[3].x-sub; ++j)
			label[i][j] = 3;
	}
	// 4
	plus = 0;
	for(int i = n-1; i > pos[2].y; --i) {
		if(i <= pos[3].y) plus++;
		for(int j = pos[3].x+plus; j < n; ++j)
			label[i][j] = 4;
	}
	// printLabel();
	calc();
}

void solution() {
	for(int i = 0; i < n; ++i) 
		for(int j = 0; j < n; ++j) 
			for(int d1 = 1; d1 <= j; ++d1) 
				for(int d2 = 1; d2 < n - j; ++d2) 
					if(isOk(i, j, d1, d2)) {
						pos[0].y = i, pos[0].x = j;
						pos[1].y = i+d1, pos[1].x = j-d1;
						pos[2].y = i+d2, pos[2].x = j+d2;
						pos[3].y = i+d1+d2, pos[3].x = j-d1+d2;
						labeling();
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
