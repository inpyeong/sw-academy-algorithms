#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 20, INF = 987654321;

int N, Answer = INF;
int Board[MAX][MAX];
int Label[MAX][MAX];
pair<int, int> Pos[4];

void input() {
  cin >> N;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      cin >> Board[i][j];
}

void printLabel() {
  cout << "=============" << endl;
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j)
      cout << Label[i][j] << " ";
    cout << endl;
  }
}

bool check(int y, int x, int d1, int d2) {
  if(y + d1 >= N || x - d1 < 0) return false;
  if(y + d2 >= N || x + d2 >= N) return false;
  if(y + d1 + d2 >= N || x - d1 +d2 < 0 || x - d1 + d2 >= N) return false;
  return true;
}

void calc() {
  int sum[6] = {0,};
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      sum[Label[i][j]] += Board[i][j];
  sort(sum, sum+6);
  Answer = min(Answer, sum[5]-sum[1]);
}

void labeling() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      Label[i][j] = 5;
  int sub = 0, plus = 0;
  for(int i = 0; i < Pos[1].first; ++i) {
    if(i >= Pos[0].first) sub++;
    for(int j = 0; j <= Pos[0].second-sub; ++j)
      Label[i][j] = 1;
  }
  for(int i = 0; i <= Pos[2].first; ++i) {
    if(i > Pos[0].first) plus++;
    for(int j = Pos[0].second+1+plus; j < N; ++j)
      Label[i][j] = 2;
  }
  sub = 0, plus = 0;
  for(int i = N-1; i >= Pos[1].first; --i) {
    if(i < Pos[3].first) sub++;
    for(int j = 0; j < Pos[3].second-sub; ++j)
      Label[i][j] = 3;
  }
  for(int i = N-1; i > Pos[2].first; --i) {
    if(i <= Pos[3].first) plus++;
    for(int j = Pos[3].second+plus; j < N; ++j)
      Label[i][j] = 4;
  }
  calc();
}

void solution() {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      for(int d1 = 1; d1 <= j; ++d1)
        for(int d2 = 1; d2 < N-j; ++d2) 
          if(check(i, j, d1, d2)) {
            Pos[0].first = i, Pos[0].second = j;
            Pos[1].first = i + d1, Pos[1].second = j - d1;
            Pos[2].first = i + d2, Pos[2].second = j + d2;
            Pos[3].first = i + d1 + d2, Pos[3].second = j - d1 + d2;
            labeling();
          }
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
