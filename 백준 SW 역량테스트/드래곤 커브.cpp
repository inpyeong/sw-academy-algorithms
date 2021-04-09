#include <iostream>
#include <vector>

using namespace std;

const int MAX = 101;

int n, x, y, d, g;
int board[MAX][MAX];
vector<int> dirInfo;

int dy[] = { 0, -1,  0, 1 };
int dx[] = { 1,  0, -1, 0 };

void input() {
    cin >> n;
}

void makeDragonCurve() {
    int sz = dirInfo.size();
    for(int i = sz-1; i >= 0; --i) {
        int nd = (dirInfo[i] + 1) % 4;
        y = y + dy[nd];
        x = x + dx[nd];
        board[y][x] = 1;
        dirInfo.push_back(nd);
    }
}

void countSquare() {
    int answer = 0;
    for(int i = 0; i < MAX; ++i) 
        for(int j = 0; j < MAX; ++j) 
            if(board[i][j] == 1 && board[i][j+1] == 1 && board[i+1][j] == 1 && board[i+1][j+1] == 1)
                answer++;
    cout << answer << endl;
}

void solution() {
    for(int i = 0; i < n; ++i) {
        cin >> x >> y >> d >> g;
        dirInfo.clear();
        board[y][x] = 1;
        y = y + dy[d]; 
        x = x + dx[d]; 
        board[y][x] = 1;
        dirInfo.push_back(d);
        for(int j = 0; j < g; ++j)
            makeDragonCurve();
    }
    countSquare();
}

void solve() {
    input();
    solution();
}

int main(int argc, char** argv) {
    solve();
	return 0;
}