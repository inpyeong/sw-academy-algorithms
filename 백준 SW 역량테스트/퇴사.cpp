#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 16;

int N, Answer;
int T[MAX], P[MAX];
bool check[MAX];

void input() {
  cin >> N;
  for(int i = 1; i <= N; ++i) 
    cin >> T[i] >> P[i];
}

void calcMoney() {
  int day = 0, candiMoney = 0;
  for(int i = 1; i <= N; ++i) {
    if(check[i]) {
      if(day <= i) {
        day = i + T[i];
        candiMoney += P[i];
        if(day > N+1) return;
      }
      else if(day > i) return;
    }
  }
  Answer = max(Answer, candiMoney);
}

void dfs(int total, int cnt, int idx) {
  if(cnt == total) {
    calcMoney();
    return;
  }
  for(int i = idx; i <= N; ++i) {
    if(!check[i]) {
      check[i] = true;
      dfs(total, cnt+1, i);
      check[i] = false;
    }
  }
}

void solution() {
  for(int i = 1; i <= N; ++i)
    dfs(i, 0, 1);
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
