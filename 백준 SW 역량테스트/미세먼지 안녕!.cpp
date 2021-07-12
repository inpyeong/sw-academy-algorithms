#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 50, D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int R, C, T;
int Board[MAX][MAX];
int _Board[MAX][MAX];
pair<int, int> Cleaner[2];

void input() {
  cin >> R >> C >> T;
  int idx = 0;
  for(int i = 0; i < R; ++i)
    for(int j = 0; j < C; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == -1) {
        Cleaner[idx].first = i;
        Cleaner[idx++].second = j;
      }
    }
}

void printBoard() {
  cout << "=============" << endl;
  for(int i = 0; i < R; ++i) {
    for(int j = 0; j < C; ++j)
      cout << Board[i][j] << " ";
    cout << endl;
  }
}

void spreadDust() {
  memset(_Board, 0, sizeof(_Board));
  for(int i = 0; i < R; ++i)
    for(int j = 0; j < C; ++j) {
      if(Board[i][j] == -1 || Board[i][j] == 0) continue;

      int tmp = Board[i][j] / 5, cnt = 0;
      for(int k = 0; k < 4; ++k) {
        int ny = i + D[k][0];
        int nx = j + D[k][1];
        if(ny >= 0 && nx >= 0 && ny < R && nx < C) {
          if(Board[ny][nx] == -1) continue;
          _Board[ny][nx] += tmp;
          cnt++;
        }
      }
      Board[i][j] -= tmp * cnt;
    }

  for(int i = 0; i < R; ++i)
    for(int j = 0; j < C; ++j) 
      Board[i][j] += _Board[i][j];
}

void Upper() {
  int y = Cleaner[0].first-2;
  int x = Cleaner[0].second;

  while(y >= 0) {
    Board[y+1][x] = Board[y][x];
    y--;
  }
  y++;

  x++;
  while(x < C) {
    Board[y][x-1] = Board[y][x];
    x++;
  }
  x--;

  y++;
  while(y <= Cleaner[0].first) {
    Board[y-1][x] = Board[y][x];
    y++;
  }
  y--;

  x--;
  while(x >= 1) {
    Board[y][x+1] = Board[y][x];
    x--;
  }

  Board[y][Cleaner[0].second+1] = 0;
}

void Lower() {
  int y = Cleaner[1].first+2;
  int x = Cleaner[1].second;

  while(y < R) {
    Board[y-1][x] = Board[y][x];
    y++;
  }
  y--;

  x++;
  while(x < C) {
    Board[y][x-1] = Board[y][x];
    x++;
  }
  x--;

  y--;
  while(y >= Cleaner[1].first) {
    Board[y+1][x] = Board[y][x];
    y--;
  }
  y++;

  x--;
  while(x >= 1) {
    Board[y][x+1] = Board[y][x];
    x--;
  }

  Board[y][Cleaner[1].second+1] = 0;
}

void solution() {
  while(T--) {
    spreadDust();
    Upper();
    Lower();
  }
  // printBoard();
  int answer = 0;
  for(int i = 0; i < R; ++i)
    for(int j = 0; j < C; ++j) {
      if(Board[i][j] == -1) continue;
      answer += Board[i][j];
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
