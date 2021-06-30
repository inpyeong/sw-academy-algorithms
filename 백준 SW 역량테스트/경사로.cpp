#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 100;

int N, L, Answer;
int Board[MAX][MAX];
int _Board[MAX][MAX];

void input() {
  cin >> N >> L;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) {
      cin >> Board[i][j];
      _Board[j][i] = Board[i][j];
    }
}

bool isInTheBoard(int y, int x) {
  return (y >= 0 && x >= 0 && y < N && x < N);
}

bool canMakeRoad(int board[][MAX], int y, int x) {
  int std = board[y][x+1];
  for(int i = x+1; i < x+1+L; ++i) {
    if(!isInTheBoard(y, i)) return false;
    if(board[y][i] != std) return false;
  }
  return true;
}

int makeRoad(int board[][MAX]) {
  int ret = 0;
  for(int i = 0; i < N; ++i) {
    bool ok = true;
    int lowerBlockCnt = 1;
    for(int j = 0; j < N-1 && ok; ++j) {
      if(board[i][j] == board[i][j+1]) lowerBlockCnt++;
      else if(board[i][j] == board[i][j+1]+1) {
        if(canMakeRoad(board, i, j)) {
          j = j + L - 1;
          lowerBlockCnt = 0;
        }
        else ok = false;
      }
      else if(board[i][j]+1 == board[i][j+1]) {
        if(lowerBlockCnt >= L) lowerBlockCnt = 1;
        else ok = false;
      }
      else if(abs(board[i][j] - board[i][j+1]) > 1) 
        ok = false;
    }
    if(ok) ret++;
  }
  return ret;
}

void solution() {
  Answer += (makeRoad(Board) + makeRoad(_Board));
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
