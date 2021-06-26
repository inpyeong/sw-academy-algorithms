#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 20;

int N, Answer;
int Board[MAX][MAX];
int _Board[MAX][MAX];
int Dirs[5];

void input() {
  cin >> N;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      cin >> Board[i][j];
}

void copyBoard() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      _Board[i][j] = Board[i][j];
}

void UP() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      if(_Board[j][i]) {
        int pos = j - 1;
        while(pos >= 0) {
          if(_Board[pos][i] == 0) {
            _Board[pos][i] = _Board[pos+1][i];
            _Board[pos+1][i] = 0;
            pos--;
          }
          else break;
        }
      }
  for(int i = 0; i < N; ++i)
    for(int j = 1; j < N; ++j) 
      if(_Board[j-1][i] && _Board[j-1][i] == _Board[j][i]) {
        _Board[j-1][i] *= 2;
        _Board[j][i] = 0;
      }
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      if(_Board[j][i]) {
        int pos = j - 1;
        while(pos >= 0) {
          if(_Board[pos][i] == 0) {
            _Board[pos][i] = _Board[pos+1][i];
            _Board[pos+1][i] = 0;
            pos--;
          }
          else break;
        }
      }
}

void DOWN() {
  for(int i = 0; i < N; ++i)
    for(int j = N-1; j >= 0; --j) 
      if(_Board[j][i]) {
        int pos = j + 1;
        while(pos < N) {
          if(_Board[pos][i] == 0) {
            _Board[pos][i] = _Board[pos-1][i];
            _Board[pos-1][i] = 0;
            pos++;
          }
          else break;
        }
      }
  for(int i = 0; i < N; ++i)
    for(int j = N-2; j >= 0; --j) 
      if(_Board[j+1][i] && _Board[j+1][i] == _Board[j][i]) {
        _Board[j+1][i] *= 2;
        _Board[j][i] = 0;
      }
  for(int i = 0; i < N; ++i)
    for(int j = N-1; j >= 0; --j) 
      if(_Board[j][i]) {
        int pos = j + 1;
        while(pos < N) {
          if(_Board[pos][i] == 0) {
            _Board[pos][i] = _Board[pos-1][i];
            _Board[pos-1][i] = 0;
            pos++;
          }
          else break;
        }
      }
}

void LEFT() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      if(_Board[i][j]) {
        int pos = j - 1;
        while(pos >= 0) {
          if(_Board[i][pos] == 0) {
            _Board[i][pos] = _Board[i][pos+1];
            _Board[i][pos+1] = 0;
            pos--;
          }
          else break;
        }
      }
  for(int i = 0; i < N; ++i)
    for(int j = 1; j < N; ++j) 
      if(_Board[i][j-1] && _Board[i][j-1] == _Board[i][j]) {
        _Board[i][j-1] *= 2;
        _Board[i][j] = 0;
      }
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) 
      if(_Board[i][j]) {
        int pos = j - 1;
        while(pos >= 0) {
          if(_Board[i][pos] == 0) {
            _Board[i][pos] = _Board[i][pos+1];
            _Board[i][pos+1] = 0;
            pos--;
          }
          else break;
        }
      }
}

void RIGHT() {
  for(int i = 0; i < N; ++i)
    for(int j = N-1; j >= 0; --j) 
      if(_Board[i][j]) {
        int pos = j + 1;
        while(pos < N) {
          if(_Board[i][pos] == 0) {
            _Board[i][pos] = _Board[i][pos-1];
            _Board[i][pos-1] = 0;
            pos++;
          }
          else break;
        }
      }
  for(int i = 0; i < N; ++i)
    for(int j = N-2; j >= 0; --j) 
      if(_Board[i][j+1] && _Board[i][j+1] == _Board[i][j]) {
        _Board[i][j+1] *= 2;
        _Board[i][j] = 0;
      }
  for(int i = 0; i < N; ++i)
    for(int j = N-1; j >= 0; --j) 
      if(_Board[i][j]) {
        int pos = j + 1;
        while(pos < N) {
          if(_Board[i][pos] == 0) {
            _Board[i][pos] = _Board[i][pos-1];
            _Board[i][pos-1] = 0;
            pos++;
          }
          else break;
        }
      }
}

int getMax() {
  int ret = 0;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      if(ret < _Board[i][j]) ret = _Board[i][j];
  return ret;
}

void play() {
  for(int i = 0; i < 5; ++i) {
    switch(Dirs[i]) {
      case 0:
        UP();
        break;
      case 1:
        DOWN();
        break;
      case 2:
        LEFT();
        break;
      case 3:
        RIGHT();
        break;
    }
  }
  Answer = max(Answer, getMax());
}

void dfs(int cnt) {
  if(cnt == 5) {
    copyBoard();
    play();
    return;
  }
  for(int i = 0; i < 4; ++i) {
    Dirs[cnt] = i;
    dfs(cnt+1);
  }
}

void solution() {
  dfs(0);
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
