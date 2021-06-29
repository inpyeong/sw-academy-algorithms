#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 11, INF = 1e8;

int N, Answer[2];
int A[MAX];
vector<int> Opers;
bool Check[MAX];

void input() {
  cin >> N;
  for(int i = 0; i < N; ++i)
    cin >> A[i];
  for(int i = 0; i < 4; ++i) {
    int n; cin >> n;
    while(n--)
      Opers.push_back(i);
  }
}

int calc(int a, int b, int o) {
  int ret;
  switch(o) {
    case 0:
      ret = a + b;
      break;
    case 1:
      ret = a - b;
      break;
    case 2:
      ret = a * b;
      break;
    case 3:
      if(a < 0) ret = -(-a / b); 
      else ret = a / b;  
      break;
  }
  return ret;
}

void getAnswer(string order) {
  int res = A[0];
  for(int i = 0; i < N-1; ++i) {
    int oper = order[i] - '0';    
    res = calc(res, A[i+1], oper);
  }
  Answer[0] = max(Answer[0], res);
  Answer[1] = min(Answer[1], res);
}

void dfs(int cnt, string tmp) {
  if(cnt == N-1) {
    getAnswer(tmp);
    return;
  }
  for(int i = 0; i < N-1; ++i) {
    if(!Check[i]) {
      Check[i] = true;
      dfs(cnt+1, tmp+string(1, '0'+Opers[i]));
      Check[i] = false;
    }
  }
}

void solution() {
  Answer[0] = -INF;
  Answer[1] = INF;
  dfs(0, "");
}

void solve() {
  input();
  solution();
  cout << Answer[0] << "\n" << Answer[1] << endl;
}

int main() {
  solve();
  return 0;
}
