#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 101, D[5][2] = {{0,0},{-1,0},{1,0},{0,1},{0,-1}};

struct Shark {
  int r, c;
  int s;
  int d;
  int z;

  Shark() {}
  Shark(int _r, int _c, int _s, int _d, int _z): r(_r), c(_c), s(_s), d(_d), z(_z) {}
};

int R, C, M;
vector<Shark> Board[MAX][MAX];

void input() {
  cin >> R >> C >> M;
  int r, c, s, d, z;
  for(int i = 0; i < M; ++i) {
    cin >> r >> c >> s >> d >> z;
    Board[r][c].push_back(Shark(r, c, s, d, z));
  }
}

void printBoard() {
  cout << "========" << endl;
  for(int i = 1; i <= R; ++i) {
    for(int j = 1; j <= C; ++j)
      cout << Board[i][j].size() << " ";
    cout << endl;
  }
}

int getOppositeDir(int d) {
  int ret = -1;
  switch(d) {
    case 1:
      ret = 2;
      break;
    case 2:
      ret = 1;
      break;
    case 3:
      ret = 4;
      break;
    case 4:
      ret = 3;
      break;
  }
  return ret;
}

void moveSharks() {
  vector<Shark> tmp;
  for(int i = 1; i <= R; ++i) {
    for(int j = 1; j <= C; ++j) {
      if(!Board[i][j].size()) continue;
      int nr = Board[i][j].front().r;
      int nc = Board[i][j].front().c;
      int nd = Board[i][j].front().d;
      int mod;
      if(nd == 1 || nd == 2) mod = (R-1) * 2;
      else mod = (C-1) * 2;
      for(int k = 0; k < Board[i][j].front().s%mod; ++k) {
         nr += D[nd][0];
         nc += D[nd][1];
         if(nr < 1 || nc < 1 || nr > R || nc > C) {
          nd = getOppositeDir(nd);
          if(nr < 1) nr = 2;
          else if(nc < 1) nc = 2;
          else if(nr > R) nr = R-1;
          else if(nc > C) nc = C-1;
         }
      }
      tmp.push_back(Shark(nr, nc, Board[i][j].front().s, nd, Board[i][j].front().z));
      Board[i][j].clear();
    }
  }
  for(int i = 0; i < tmp.size(); ++i) 
    Board[tmp[i].r][tmp[i].c].push_back(tmp[i]);
}

bool cmp(Shark& a, Shark& b) {
  return a.z > b.z;
}

void killSharks() {
  Shark tmp;
  for(int i = 1; i <= R; ++i) 
    for(int j = 1; j <= C; ++j) {
      if(Board[i][j].size() >= 2) {
        sort(Board[i][j].begin(), Board[i][j].end(), cmp);
        tmp = Board[i][j].front();
        Board[i][j].clear();
        Board[i][j].push_back(tmp);
      }
    }
}

void solution() {
  int answer = 0;
  for(int i = 1; i <= C; ++i) {
    for(int j = 1; j <= R; ++j) 
      if(Board[j][i].size()) {
        answer += Board[j][i].front().z;
        Board[j][i].clear();
        break;
      }
    moveSharks();
    killSharks();
    // printBoard();
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
