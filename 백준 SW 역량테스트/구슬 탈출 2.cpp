#include <iostream>
#include <queue>

using namespace std;

const int MAX = 10;

struct Ball {
  int y, x;
}Red, Blue;

int N, M;
char Board[MAX][MAX];
queue<pair<pair<int, int>, pair<int, int> > > Q;
bool discovered[MAX][MAX][MAX][MAX];

int D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void input() {
  cin >> N >> M;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j) {
      cin >> Board[i][j];
      if(Board[i][j] == 'R') {
        Red.y = i;
        Red.x = j;
      }
      if(Board[i][j] == 'B') {
        Blue.y = i;
        Blue.x = j;
      }
    }
}

int solution() {
  int ret = 0;
  Q.push(make_pair(make_pair(Red.y, Red.x), make_pair(Blue.y, Blue.x)));
  discovered[Red.y][Red.x][Blue.y][Blue.x] = true;
  while(!Q.empty()) {
    int qSz = Q.size();
    while(qSz--) {
      int redY = Q.front().first.first, redX = Q.front().first.second;
      int blueY = Q.front().second.first, blueX = Q.front().second.second;
      Q.pop();

      if(Board[redY][redX] == 'O') return ret;

      for(int i = 0; i < 4; ++i) {
        int nRedY = redY, nRedX = redX;
        int nBlueY = blueY, nBlueX = blueX;;

        int redMoveCnt = 0,  blueMoveCnt = 0;
        while(Board[nRedY+D[i][0]][nRedX+D[i][1]] != '#' && Board[nRedY][nRedX] != 'O') {
          nRedY += D[i][0];
          nRedX += D[i][1];
          redMoveCnt++;
        }
        while(Board[nBlueY+D[i][0]][nBlueX+D[i][1]] != '#' && Board[nBlueY][nBlueX] != 'O') {
          nBlueY += D[i][0];
          nBlueX += D[i][1];
          blueMoveCnt++;
        }
        
        if(nRedY == nBlueY && nRedX == nBlueX) {
          if(Board[nBlueY][nBlueX] == 'O') continue;
          if(redMoveCnt > blueMoveCnt) {
            nRedY -= D[i][0];
            nRedX -= D[i][1];
          }
          else {
            nBlueY -= D[i][0];
            nBlueX -= D[i][1];
          }
        }

        if(discovered[nRedY][nRedX][nBlueY][nBlueX]) continue;
        Q.push(make_pair(make_pair(nRedY, nRedX), make_pair(nBlueY, nBlueX)));
        discovered[nRedY][nRedX][nBlueY][nBlueX] = true;
      }
    }
    ret++;
    if(ret > 10) return -1;
  }
  return -1;
}

void solve() {
  input();
  cout << solution() << endl;
}

int main() {
  solve();
  return 0;
}
