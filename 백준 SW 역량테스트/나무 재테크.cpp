#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 11, D[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

int N, M, K;
int Nutrient[MAX][MAX];
int A[MAX][MAX];
vector<int> Trees[MAX][MAX];

void input() {
  cin >> N >> M >> K;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j) {
      cin >> A[i][j];
      Nutrient[i][j] = 5;
    }
  for(int i = 0; i < M; ++i) {
    int y, x, z;
    cin >> y >> x >> z;
    Trees[y][x].push_back(z);
  }
}

void SpringSummer() {
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j) {
      if(!Trees[i][j].size()) continue;
      int nutri = 0;
      vector<int> v;
      sort(Trees[i][j].begin(), Trees[i][j].end());
      for(int k = 0; k < Trees[i][j].size(); ++k) {
        int age = Trees[i][j][k];
        if(Nutrient[i][j] >= age) {
          Nutrient[i][j] -= age;
          v.push_back(age + 1);
        }
        else nutri += (age / 2);
      }
      Trees[i][j].clear();
      for(int k = 0; k < v.size(); ++k)
        Trees[i][j].push_back(v[k]);
      Nutrient[i][j] += nutri;
    }
}

void Fall() {
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j) {
      if(!Trees[i][j].size()) continue;
      for(int k = 0; k < Trees[i][j].size(); ++k) {
        int age = Trees[i][j][k];
        if(age % 5 == 0) {
          for(int l = 0; l < 8; ++l) {
            int ny = i + D[l][0];
            int nx = j + D[l][1];
            if(ny >= 1 && nx >= 1 && ny <= N && nx <= N) 
              Trees[ny][nx].push_back(1);
          }
        }
      }
    }
}

void Winter() {
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      Nutrient[i][j] += A[i][j];
}

void solution() {
  while(K--) {
    SpringSummer();
    Fall();
    Winter();
  }
  int answer = 0;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= N; ++j)
      answer += Trees[i][j].size();
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
