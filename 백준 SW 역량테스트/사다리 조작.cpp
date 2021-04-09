#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int n, m, h, answer;
bool visited[11][30];

void input() {
    answer = INF;
    cin >> n >> m >> h;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        visited[b][a] = true;
    }
}

bool ladderGame() {
    for(int i = 1; i <= n; ++i) {
        int currNum = i;
        for(int j = 1; j <= h; ++j) {
            if(visited[currNum][j]) currNum = currNum+1;
            else if(visited[currNum-1][j]) currNum = currNum-1;
        }
        if(currNum != i) return false;
    }
    return true;
}

void selectLadder(int idx, int cnt) {
    if(cnt >= 4) return;
    if(ladderGame()) {
        answer = min(answer, cnt);
        return;
    }
    for(int i = idx; i <= h; ++i) {
        for(int j = 1; j < n; ++j) {
            if(visited[j][i]) continue;
            if(visited[j-1][i]) continue;
            if(visited[j+1][i]) continue;
            visited[j][i] = true;
            selectLadder(i, cnt+1);
            visited[j][i] = false;
        }
    }
}

void solution() {
    selectLadder(1, 0);
    if(answer == INF) cout << -1 << endl;
    else cout << answer << endl;
}

void solve() {
    input();
    solution();
}

int main(int argc, char** argv) {
  solve();
	return 0;
}
