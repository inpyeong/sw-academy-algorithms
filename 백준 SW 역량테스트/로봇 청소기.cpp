#include <iostream>

using namespace std;

const int MAX = 50;

struct Robot {
  int y, x;
  int d;
}Robot;

int N, M, Answer;
int Board[MAX][MAX];
bool Cleaned[MAX][MAX];

int D[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

void input() {
  cin >> N >> M;
  cin >> Robot.y >> Robot.x >> Robot.d;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j)
      cin >> Board[i][j];
}

int getLeftDir(int d) {
  int ret;
  switch(d) {
    case 0:
      ret = 3;
      break;
    case 1:
      ret = 0;
      break;
    case 2:
      ret = 1;
      break;
    case 3:
      ret = 2;
      break;
  }
  return ret;
}

int getOppositeDir(int d) {
  int ret;
  switch(d) {
    case 0:
      ret = 2;
      break;
    case 1:
      ret = 3;
      break;
    case 2:
      ret = 0;
      break;
    case 3:
      ret = 1;
      break;
  }
  return ret;
}

void solution() {
  bool check = true;
  while(true) {
    if(check) {
      Cleaned[Robot.y][Robot.x] = true;
      Answer++;
    }

    int i;
    for(i = 0; i < 4; ++i) {
      int nd = getLeftDir(Robot.d);
      int ny = Robot.y + D[nd][0];
      int nx = Robot.x + D[nd][1];
      if(!Board[ny][nx]) {
        if(!Cleaned[ny][nx]) {
          Robot.d = nd;
          Robot.y = ny;
          Robot.x = nx;
          check = true;
          break;
        }
      }
      Robot.d = nd;
    }
    if(i == 4) {
      int nnd = getOppositeDir(Robot.d);
      int ny = Robot.y + D[nnd][0];
      int nx = Robot.x + D[nnd][1];
      if(!Board[ny][nx]) {
        Robot.y = ny;
        Robot.x = nx;
        check = false;
      }
      else return;
    }
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
