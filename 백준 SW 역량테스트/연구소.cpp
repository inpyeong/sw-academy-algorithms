#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 8;

int N, M, Answer;
int Board[MAX][MAX];
int _Board[MAX][MAX];
bool check[MAX*MAX];
vector<pair<int, int> > Virus;

bool Discovered[MAX][MAX];
queue<pair<int, int> > Q;

int D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void input() {
  cin >> N >> M;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == 2) 
        Virus.push_back(make_pair(i, j));
    }
}

void print_Board() {
  cout << "=======" << endl;
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < M; ++j)
      cout << _Board[i][j] << " ";
    cout << endl;
  }
}

void copyBoard() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j)
      _Board[i][j] = Board[i][j];
}

int getNumOfZero() {
  copyBoard();
  for(int i = 0; i < N*M; ++i) 
    if(check[i]) {
      if(_Board[i/M][i%M]) return -1;
      else _Board[i/M][i%M] = 1;
    } 
  memset(Discovered, false, sizeof(Discovered));
  while(!Q.empty()) Q.pop();
  for(int i = 0; i < Virus.size(); ++i) {
    int srcY = Virus[i].first, srcX = Virus[i].second;
    Discovered[srcY][srcX] = true;
    Q.push(make_pair(srcY, srcX));
    while(!Q.empty()) {
      int y = Q.front().first;
      int x = Q.front().second;
      Q.pop();
      _Board[y][x] = 2;
      for(int j = 0; j < 4; ++j) {
        int ny = y + D[j][0];
        int nx = x + D[j][1];
        if(ny >= 0 && nx >= 0 && ny < N && nx < M) {
          if(!Discovered[ny][nx] && !_Board[ny][nx]) {
            Discovered[ny][nx] = true;
            Q.push(make_pair(ny, nx));
          }
        }
      }
    }
  }
  int ret = 0;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j)
      if(!_Board[i][j]) ret++;
  return ret;
}

void dfs(int cnt, int idx) {
  if(cnt == 3) {
    int candi = getNumOfZero();
    Answer = max(Answer, candi);
    return;
  }
  for(int i = idx; i < N*M; ++i) {
    if(!check[i]) {
      check[i] = true;
      dfs(cnt+1, i);
      check[i] = false;
    }
  }
}

void solution() {
  dfs(0, 0);
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
