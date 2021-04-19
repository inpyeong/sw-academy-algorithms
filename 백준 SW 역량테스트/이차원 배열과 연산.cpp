#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1 + 100;

int r, c, k, answer;
int A[MAX][MAX]; 
int numCnt[MAX];

void input() {
	cin >> r >> c >> k;
	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 3; ++j)
			cin >> A[i][j];
}

void find() {
	int time = 0;
	int ar = 3, ac = 3;
	while(true) {
		if(A[r][c] == k) {
			answer = time;
			break;
		}
		if(time > 100) {
			answer = -1;
			break;
		}
		vector<int> sizes;
		// R
		if(ar >= ac) {
			for(int i = 1; i <= ar; ++i) {
				vector<pair<int, int> > v;
				memset(numCnt, 0, sizeof(numCnt));
				for(int j = 1; j <= ac; ++j) 
					numCnt[A[i][j]]++;
				for(int j = 1; j < MAX; ++j) {
					if(numCnt[j] == 0) continue;
					v.push_back(make_pair(numCnt[j], j));
				}
				sort(v.begin(), v.end());
				for(int j = 1; j <= ac; ++j)
					A[i][j] = 0;
				int idx = 1;
				for(int j = 0; j < v.size(); ++j) {
					A[i][idx++] = v[j].second;
					A[i][idx++] = v[j].first;
				}
				idx--;
				sizes.push_back(idx);
			}
			sort(sizes.begin(), sizes.end());
			ac = sizes.back();
		}
		// C
		else {
			for(int i = 1; i <= ac; ++i) {
				vector<pair<int, int> > v;
				memset(numCnt, 0, sizeof(numCnt));
				for(int j = 1; j <= ar; ++j) 
					numCnt[A[j][i]]++;
				for(int j = 1; j < MAX; ++j) {
					if(numCnt[j] == 0) continue;
					v.push_back(make_pair(numCnt[j], j));
				}
				sort(v.begin(), v.end());
				for(int j = 1; j <= ar; ++j)
					A[j][i] = 0;
				int idx = 1;
				for(int j = 0; j < v.size(); ++j) {
					A[idx++][i] = v[j].second;
					A[idx++][i] = v[j].first;
				}
				idx--;
				sizes.push_back(idx);
			}
			sort(sizes.begin(), sizes.end());
			ar = sizes.back();
		}
		time++;
	}
}

void solution() {
	if(A[r][c] == k) {
		answer = 0;
		cout << answer << endl;
		return;
	}
	find();
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
