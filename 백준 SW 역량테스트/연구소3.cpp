#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 987654321;
const int MAX_N = 50, MAX_M = 10, D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int N, M, Answer = INF;
int Board[MAX_N][MAX_N];
vector<pair<int, int> > Virus;
bool Check[MAX_M];

queue<pair<int, int> > Q;
int Dist[MAX_N][MAX_N];

void input() {
  cin >> N >> M;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == 2)
        Virus.push_back(make_pair(i, j));
    }
}

int spreadVirus() {
  int time = 0;
  while(!Q.empty()) Q.pop();
  memset(Dist, -1, sizeof(Dist));
  
  for(int i = 0; i < Virus.size(); ++i)
    if(Check[i]) {
      Q.push(make_pair(Virus[i].first, Virus[i].second));
      Dist[Virus[i].first][Virus[i].second] = 0;
    }

  while(!Q.empty()) {
    int qSz = Q.size();
    while(qSz--) {
      int y = Q.front().first;
      int x = Q.front().second;
      Q.pop();
      if(Board[y][x] == 0)
        time = max(time, Dist[y][x]);

      for(int i = 0; i < 4; ++i) {
        int ny = y + D[i][0];
        int nx = x + D[i][1];
        if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if(Board[ny][nx] == 1) continue;
        if(Dist[ny][nx] != -1) continue;
        Q.push(make_pair(ny, nx));
        Dist[ny][nx] = Dist[y][x] + 1;
      }
    }
  }

  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      if(Board[i][j] == 0 && Dist[i][j] == -1)
        return INF;
  return time;
}

void DFS(int idx, int cnt) {
  if(cnt == M) {
    Answer = min(Answer, spreadVirus());
    return;
  }
  for(int i = idx; i < Virus.size(); ++i) {
    if(Check[i]) continue;
    Check[i] = true;
    DFS(i, cnt+1);
    Check[i] = false;
  }
}

void solution() {
  DFS(0, 0);
  if(Answer == INF)
    cout << -1 << endl;
  else
    cout << Answer << endl;
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
