#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX = 21, INF = 987654321;

int N, Diff = INF;
int S[MAX][MAX];
bool Check[MAX];

void input() {
  cin >> N;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      cin >> S[i][j];
}

int getStats(string team) {
  int ret = 0;
  if(team == "start") {
    for(int i = 1; i <= N; ++i) {
      if(!Check[i]) continue;
      for(int j = 1; j <= N; ++j) {
        if(!Check[j]) continue;
        if(j == i) continue;
        ret += S[i][j];
      }
    }
  }
  else if(team == "link") {
    for(int i = 1; i <= N; ++i) {
      if(Check[i]) continue;
      for(int j = 1; j <= N; ++j) {
        if(Check[j]) continue;
        if(j == i) continue;
        ret += S[i][j];
      }
    }
  }
  return ret;
}

void dfs(int idx, int cnt) {
  if(cnt == N/2) {
    int start = getStats("start");
    int link = getStats("link");
    Diff = min(abs(start - link), Diff);
    return;
  }
  for(int i = idx; i <= N; ++i) {
    if(!Check[i]) {
      Check[i] = true;
      dfs(i+1, cnt+1);
      Check[i] = false;
    }
  }
}

void solution() {
  dfs(1, 0);
  cout << Diff << endl;
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
