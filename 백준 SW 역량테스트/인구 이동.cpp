#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX = 50, D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int N, L, R, Idx, Answer;
int Board[MAX][MAX];
queue<pair<int, int> > Q;
int Discovered[MAX][MAX];
vector<pair<int, int> > Unite[MAX*MAX];

void input() {
  cin >> N >> L >> R;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      cin >> Board[i][j];
}

void bfs(int srcY, int srcX, int idx) {
  Q.push(make_pair(srcY, srcX));
  Discovered[srcY][srcX] = idx;
  while(!Q.empty()) {
    int y = Q.front().first;
    int x = Q.front().second;
    Q.pop();
    Unite[idx].push_back(make_pair(y, x));
    for(int i = 0; i < 4; ++i) {
      int ny = y + D[i][0];
      int nx = x + D[i][1];
      if(ny >= 0 && nx >= 0 && ny < N && nx < N)
        if(Discovered[ny][nx] == -1) {
          int diff = abs(Board[y][x] - Board[ny][nx]);
          if(diff >= L && diff <= R) {
            Discovered[ny][nx] = idx;
            Q.push(make_pair(ny, nx));
          }
        }
    }
  }
}

void movePeople() {
  int tmp;
  for(int idx = 0; idx < Idx; ++idx) {
    tmp = 0;
    for(int i = 0; i < Unite[idx].size(); ++i) 
      tmp += Board[Unite[idx][i].first][Unite[idx][i].second];
    tmp /= Unite[idx].size();
    for(int i = 0; i < Unite[idx].size(); ++i) 
      Board[Unite[idx][i].first][Unite[idx][i].second] = tmp;
  }
}

void solution() {
  while(true) {
    memset(Discovered, -1, sizeof(Discovered));
    for(int i = 0; i < Idx; ++i)
      Unite[i].clear();
    Idx = 0;
    for(int i = 0; i < N; ++i) 
      for(int j = 0; j < N; ++j) 
        if(Discovered[i][j] == -1) 
          bfs(i, j, Idx++);
    if(Idx == N*N) break;
    movePeople();
    Answer++;
  }
}

void solve() {
  input();
  solution();
  cout << Answer << endl;
}

int main() {
  solve();
  return 0;
}
