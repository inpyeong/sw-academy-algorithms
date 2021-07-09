#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 20, D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

struct Shark {
  int y, x;
  int size;
  int eatCnt;
  int time;
}Shark;

struct Fish {
  int y, x;
  int dist;
};

int N;
int Board[MAX][MAX];
queue<pair<pair<int, int>, int> > Q;
bool Discovered[MAX][MAX];
vector<Fish> Fishes;

void input() {
  cin >> N;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == 9) {
        Shark.y = i;
        Shark.x = j;
        Shark.size = 2;
        Shark.eatCnt = 0;
        Shark.time = 0;
      }
    }
}

void init() {
  Fishes.clear();
  while(!Q.empty()) Q.pop();
  memset(Discovered, false, sizeof(Discovered));
}

void bfs() {
  Q.push(make_pair(make_pair(Shark.y, Shark.x), 0));
  Discovered[Shark.y][Shark.x] = true;
  while(!Q.empty()) {
    int y = Q.front().first.first;
    int x = Q.front().first.second;
    int dist = Q.front().second;
    Q.pop();
    for(int i = 0; i < 4; ++i) {
      int ny = y + D[i][0];
      int nx = x + D[i][1];
      if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
      if(Discovered[ny][nx]) continue;
      if(Board[ny][nx] == 0 || Board[ny][nx] == Shark.size) {
        Discovered[ny][nx] = true;
        Q.push(make_pair(make_pair(ny, nx), dist+1));
      } 
      else if(Board[ny][nx] < Shark.size) {
        Fish f;
        f.y = ny;
        f.x = nx;
        f.dist = dist+1;
        Fishes.push_back(f);
        Discovered[ny][nx] = true;
        Q.push(make_pair(make_pair(ny, nx), dist+1));
      }
    }
  }
}

void eatFish() {
  int y = Fishes.front().y;
  int x = Fishes.front().x;
  int dist = Fishes.front().dist;

  Board[y][x] = 9;
  Board[Shark.y][Shark.x] = 0;

  Shark.y = y;
  Shark.x = x;
  Shark.eatCnt++;
  Shark.time += dist;
  if(Shark.eatCnt == Shark.size) {
    Shark.size++;
    Shark.eatCnt = 0;
  }
}

bool cmp(Fish& a, Fish& b) {
  if(a.dist == b.dist) {
    if(a.y == b.y)
      return a.x < b.x;
    return a.y < b.y;
  }
  return a.dist < b.dist;
}

void solution() {
  while(true) {
    init();
    bfs();
    if(Fishes.size() == 0) {
      cout << Shark.time << endl;
      break;
    }
    else if(Fishes.size() == 1) eatFish();
    else if(Fishes.size() >= 2) {
      sort(Fishes.begin(), Fishes.end(), cmp);
      eatFish();
    }
  }
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
