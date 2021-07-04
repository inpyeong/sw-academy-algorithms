#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 51, MAX_M = 13, INF = 987654321;

int N, M, Answer = INF;
int Board[MAX_N][MAX_N];
vector<pair<int, int> > Houses;
vector<pair<int, int> > Chickens;
bool Check[MAX_M];


void input() {
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == 1) 
        Houses.push_back(make_pair(i, j));
      else if(Board[i][j] == 2)
        Chickens.push_back(make_pair(i, j));
    }
}

void calcCityChickenDist() {
  int sumOfHouseChickenDist = 0;
  for(int i = 0; i < Houses.size(); ++i) {
    int houseChickenDist = INF;
    for(int j = 0; j < Chickens.size(); ++j)
      if(Check[j]) {
        houseChickenDist = min(houseChickenDist, abs(Houses[i].first - Chickens[j].first) 
            + abs(Houses[i].second - Chickens[j].second));
      }
    sumOfHouseChickenDist += houseChickenDist;
  }
  Answer = min(Answer, sumOfHouseChickenDist);
}

void dfs(int idx, int cnt) {
  if(cnt == M) {
    calcCityChickenDist();
    return;
  }
  for(int i = idx; i < Chickens.size(); ++i) {
    if(!Check[i]) {
      Check[i] = true;
      dfs(i, cnt+1);
      Check[i] = false;
    }
  }
}

void solution() {
  dfs(0, 0);
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
