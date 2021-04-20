#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 51, MAX_M = 51;

int n, m, t;
vector<int> circles[MAX_N];
bool check[MAX_N][MAX_M];
bool wasDelete;

void input() {
	cin >> n >> m >> t;
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j < m; ++j) {
			int num;
			cin >> num;
			circles[i].push_back(num);
		}
}

void rotateCircle(int idx, int d, int k) {
	vector<int> tmp;
	// cw
	if(d == 0) {
		for(int i = m-k; i < m; ++i) 
			tmp.push_back(circles[idx][i]);
		for(int i = 0; i < m-k; ++i)
			tmp.push_back(circles[idx][i]);
		circles[idx] = tmp;
	}
	// ccw
	else if(d == 1) {
		for(int i = k; i < m; ++i) 
			tmp.push_back(circles[idx][i]);
		for(int i = 0; i < k; ++i)
			tmp.push_back(circles[idx][i]);
		circles[idx] = tmp;
	}
}

void printCircles() {
	cout << "===================" << endl;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < m; ++j)
			cout << circles[i][j] << " ";
		cout << endl;
	}
	cout << "===================" << endl;
}

void deleteNum() {
	memset(check, false, sizeof(check));
	wasDelete = false;
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j < m; ++j) {
			bool del = false;
			int here = circles[i][j];
			if(here == 0) continue;
			// up
			int upPos = i+1;	
			if(upPos <= n && here == circles[upPos][j]) {
				check[upPos][j] = true;
				if(!del) 
					del = true;
			}
			// down
			int downPos = i-1;	
			if(downPos > 0 && here == circles[downPos][j]) {
				check[downPos][j] = true;
				if(!del) 
					del = true;
			}
			// left			
			int leftPos;
			if(j == 0) leftPos = m-1;
			else leftPos = j-1;
			if(here == circles[i][leftPos]) {
				check[i][leftPos] = true;
				if(!del) 
					del = true;
			}
			// right
			int rightPos;
			if(j == m-1) rightPos = 0;
			else rightPos = j+1;
			if(here == circles[i][rightPos]) {
				check[i][rightPos] = true;
				if(!del) 
					del = true;
			}
			if(del) 
				check[i][j] = true;
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < m; ++j) 
			if(check[i][j]) {
				circles[i][j] = 0;
				if(!wasDelete)
					wasDelete = true;
			}
}

void calc() {
	int cnt = 0, sum = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < m; ++j)
			if(circles[i][j] > 0) {
				cnt++;
				sum += circles[i][j];
			}
	double avg = (double)(sum) / (double)(cnt);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < m; ++j) {
			if(circles[i][j] == 0)
				continue;
			if((double)(circles[i][j]) > avg)
				circles[i][j]--;
			else if((double)(circles[i][j]) < avg)
				circles[i][j]++;
		}
}

int getSum() {
	int ret = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < m; ++j)
			ret += circles[i][j];
	return ret;
}

void solution() {
	for(int i = 0; i < t; ++i) {
		int x, d, k;
		cin >> x >> d >> k;
		for(int j = 1; j <= n; ++j) 
			if(j % x == 0) 
				rotateCircle(j, d, k);
		deleteNum(); 
		if(!wasDelete)
			calc();
	}
	cout << getSum() << endl;
}

void solve() {
	input();
	solution();
}

int main() {
	solve();
	return 0;
}
