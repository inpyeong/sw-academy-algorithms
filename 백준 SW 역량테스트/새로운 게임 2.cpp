#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 12, MAX_K = 10;

struct CHESS {
  int y, x;
  int d;
};

int N, K, Answer;
int Board[MAX_N][MAX_N];
vector<int> BoardState[MAX_N][MAX_N];
CHESS Chess[MAX_K];

int D[5][2] = {{0,0},{0,1},{0,-1},{-1,0},{1,0}};

void input() {
  cin >> N >> K;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      cin >> Board[i][j];
  for(int i = 0; i < K; ++i) {
    cin >> Chess[i].y >> Chess[i].x >> Chess[i].d;
    Chess[i].y--;
    Chess[i].x--;
    BoardState[Chess[i].y][Chess[i].x].push_back(i);
  }
}

bool checkBoardState() {
  for(int i = 0; i < K; ++i) {
    int y = Chess[i].y;
    int x = Chess[i].x;
    if(BoardState[y][x].size() >= 4) return true;
  }
  return false;
}

int findPos(int y, int x, int idx) {
  for(int i = 0; i < BoardState[y][x].size(); ++i)
    if(BoardState[y][x][i] == idx) return i;
}

int findDeleteNum(int y, int x, int chessNum) {
  int cnt = 0;
  for(int i = BoardState[y][x].size()-1; i >= 0; --i) {
    if(BoardState[y][x][i] == chessNum) break;
    cnt++;
  }
  return cnt+1;
}

int getOppositeDir(int num) {
  int d = Chess[num].d;
  if(d == 1) return 2;
  else if(d == 2) return 1;
  else if(d == 3) return 4;
  else if(d == 4) return 3;
}

void moveChess(int y, int x, int ny, int nx, int chessNum, int pos, int bs) {
  if(bs == 0) {
    for(int i = pos; i < BoardState[y][x].size(); ++i) {
      BoardState[ny][nx].push_back(BoardState[y][x][i]);
      int idx = BoardState[y][x][i];
      Chess[idx].y = ny;
      Chess[idx].x = nx;
    }
    int deleteNum = findDeleteNum(y, x, chessNum);
    for(int i = 0; i < deleteNum; ++i) BoardState[y][x].pop_back();
  }
  else if(bs == 1) {
    for(int i = BoardState[y][x].size()-1; i >= pos; --i) {
      BoardState[ny][nx].push_back(BoardState[y][x][i]);
      int idx = BoardState[y][x][i];
      Chess[idx].y = ny;
      Chess[idx].x = nx;
    }
    int deleteNum = findDeleteNum(y, x, chessNum);
    for(int i = 0; i < deleteNum; ++i) BoardState[y][x].pop_back();
  }
  else if(bs == 2) {
    int nd = getOppositeDir(chessNum);
    Chess[chessNum].d = nd;
    int nny = y + D[nd][0];
    int nnx = x + D[nd][1];

    if(nny >= 0 && nnx >= 0 && nny < N && nnx < N) 
      if(Board[nny][nnx] != 2) moveChess(y, x, nny, nnx, chessNum, pos, Board[nny][nnx]);
  }
}

void solution() {
  bool flag = false;
  int time = 0;
  while(true) {
    if(time > 1000) break;
    for(int i = 0; i < K; ++i) {
      int y = Chess[i].y;
      int x = Chess[i].x;
      int d = Chess[i].d;

      int ny = y + D[d][0];
      int nx = x + D[d][1];

      int pos = findPos(y, x, i);
      if(ny >= 0 && nx >= 0 && ny < N && nx < N) 
        moveChess(y, x, ny, nx, i, pos, Board[ny][nx]);
      else 
        moveChess(y, x, ny, nx, i, pos, 2);

      if(checkBoardState()) {
        flag = true;
        break;
      }
    }
    if(flag) break;
    time++;
  }
  if(flag) cout << time + 1 << endl;
  else cout << -1 << endl;
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
