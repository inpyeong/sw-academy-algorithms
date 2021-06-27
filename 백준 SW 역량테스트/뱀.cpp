#include <iostream>
#include <deque>

using namespace std;

const int MAX_N = 101, MAX_L = 100;

int N, K, L, Answer;
// 0: empty, 1: apple, 2: Snake
int Board[MAX_N][MAX_N];
pair<int, char> Moving[MAX_L];
deque<pair<int, int> > DQ;
int Dir = 3;

int D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void input() {
  cin >> N >> K;
  for(int i = 0; i < K; ++i) {
    int y, x;
    cin >> y >> x;
    Board[y][x] = 1;
  }
  cin >> L;
  for(int i = 0; i < L; ++i) 
    cin >> Moving[i].first >> Moving[i].second;
}

bool moveHead() {
  int ny = DQ.front().first + D[Dir][0];
  int nx = DQ.front().second + D[Dir][1];

  if(ny >= 1 && nx >= 1 && ny <= N && nx <= N) {
    if(Board[ny][nx] == 2) return true;
    DQ.push_front(make_pair(ny, nx));
    if(Board[ny][nx] == 0) {
      Board[DQ.back().first][DQ.back().second] = 0;
      DQ.pop_back();
    }
    Board[ny][nx] = 2;
    return false;
  }
  else return true;
}

void changeDirection(char c) {
  if(c == 'L') {
    if(Dir == 0) Dir = 2;
    else if(Dir == 1) Dir = 3;
    else if(Dir == 2) Dir = 1;
    else if(Dir == 3) Dir = 0;
  }
  else if(c == 'D') {
    if(Dir == 0) Dir = 3;
    else if(Dir == 1) Dir = 2;
    else if(Dir == 2) Dir = 0;
    else if(Dir == 3) Dir = 1;
  }
}

void solution() {
  DQ.push_front(make_pair(1, 1));
  Board[1][1] = 2;
  int t = 0, idx = 0;
  while(true) {
    bool fin = moveHead();
    if(fin) break;
    t++;
    if(Moving[idx].first == t) 
      changeDirection(Moving[idx++].second);
  }
  cout << ++t << endl;
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
