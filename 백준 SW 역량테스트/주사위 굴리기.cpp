#include <iostream>
#include <vector>

using namespace std;

const int MAX_NM = 20, MAX_K = 1000;;

struct Dice {
  int y, x;
  int area[7];
}dice;

int N, M, K;
int Board[MAX_NM][MAX_NM];
int Cmd[MAX_K];
vector<int> Answer;

int D[5][2] = {{0,0},{0,1},{0,-1},{-1,0},{1,0}};

void input() {
  cin >> N >> M >> dice.y >> dice.x >> K;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j)
      cin >> Board[i][j];
  for(int i = 0; i < K; ++i)
    cin >> Cmd[i];
}

void East() {
  int tmp = dice.area[3];
  dice.area[3] = dice.area[6];
  dice.area[6] = dice.area[4];
  dice.area[4] = dice.area[1];
  dice.area[1] = tmp;
}

void West() {
  int tmp = dice.area[4];
  dice.area[4] = dice.area[6];
  dice.area[6] = dice.area[3];
  dice.area[3] = dice.area[1];
  dice.area[1] = tmp;
}

void North() {
  int tmp = dice.area[2];
  dice.area[2] = dice.area[6];
  dice.area[6] = dice.area[5];
  dice.area[5] = dice.area[1];
  dice.area[1] = tmp;
}

void South() {
  int tmp = dice.area[5];
  dice.area[5] = dice.area[6];
  dice.area[6] = dice.area[2];
  dice.area[2] = dice.area[1];
  dice.area[1] = tmp;
}

void moveDice(int ny, int nx, int d) {
  dice.y = ny, dice.x = nx;
  switch(d) {
    case 1:
      East();
      break;
    case 2:
      West();
      break;
    case 3:
      North();
      break;
    case 4:
      South();
      break;
  }
}

void solution() {
  for(int i = 0; i < K; ++i) {
    int ny = dice.y + D[Cmd[i]][0];
    int nx = dice.x + D[Cmd[i]][1];
    if(ny >= 0 && nx >= 0 && ny < N && nx < M) {
      moveDice(ny, nx, Cmd[i]);
      if(Board[dice.y][dice.x]) {
        dice.area[1] = Board[dice.y][dice.x];
        Board[dice.y][dice.x] = 0;
      }
      else 
        Board[dice.y][dice.x] = dice.area[1];
      Answer.push_back(dice.area[6]);
    }
  }
}

void solve() {
  input();
  solution();
  for(int ans : Answer)
    cout << ans << endl;
}

int main() {
  solve();
  return 0;
}
