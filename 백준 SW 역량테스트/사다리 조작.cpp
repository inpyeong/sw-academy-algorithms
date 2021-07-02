#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 11, MAX_H = 30, INF = 987654321;

int N, M, H, Answer;
bool Visited[MAX_N][MAX_H];

void input() {
  Answer = INF;
  cin >> N >> M >> H;
  for(int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;
    Visited[b][a] = true;
  }
}

bool ladderGame() {
  for(int i = 1; i <= N; ++i) {
    int currNum = i;
    for(int j = 1; j <= H; ++j) {
      if(Visited[currNum][j]) currNum++;
      else if(Visited[currNum-1][j]) currNum--;
    }
    if(currNum != i) return false;
  }
  return true;
}

void selectLadder(int idx, int cnt) {
  if(cnt >= 4) return;
  if(ladderGame()) {
    Answer = min(Answer, cnt);
    return;
  }
  // Horizontal
  for(int i = idx; i <= H; ++i) {
    // Vertical
    for(int j = 1; j < N; ++j) {
      if(Visited[j][i]) continue;
      if(Visited[j-1][i]) continue;
      if(Visited[j+1][i]) continue;

      Visited[j][i] = true;
      selectLadder(i, cnt+1);
      Visited[j][i] = false;
    }
  }
}

void solution() {
  selectLadder(1, 0);
  if(Answer == INF) cout << -1 << endl;
  else cout << Answer << endl;
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
