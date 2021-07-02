#include <iostream>
#include <vector>

using namespace std;

const int MAX = 101;

int N, Answer;
int Board[MAX][MAX];
int X, Y, Dir, Gen;
vector<int> DirInfo;

int D[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};

void input() {
  cin >> N;
}

void drawDragonCurve() {
  int sz = DirInfo.size();
  for(int i = sz-1; i >= 0; --i) {
    int nd = (DirInfo[i] + 1) % 4;
    Y += D[nd][0];
    X += D[nd][1];
    Board[Y][X] = 1;
    DirInfo.push_back(nd);
  }
}

void countSquare() {
  for(int i = 0; i < MAX; ++i) 
    for(int j = 0; j < MAX; ++j) 
      if(Board[i][j] && Board[i][j+1] && Board[i+1][j] && Board[i+1][j+1])
        Answer++;
}

void solution() {
  for(int i = 0; i < N; ++i) {
    cin >> X >> Y >> Dir >> Gen;
    DirInfo.clear();
    Board[Y][X] = 1;
    Y += D[Dir][0];
    X += D[Dir][1];
    Board[Y][X] = 1;
    DirInfo.push_back(Dir);
    for(int j = 1; j <= Gen; ++j)
      drawDragonCurve();
  }
  countSquare();
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
