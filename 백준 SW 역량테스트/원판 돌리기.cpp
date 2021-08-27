#include <iostream>

using namespace std;

const int MAX = 51, INF = 987654321;

int N, M, T, Answer;
int Circles[MAX][MAX];
int _Circles[MAX][MAX];
int XDK[MAX][3];
int Tmp[MAX];
bool Deleted;

void input() {
  cin >> N >> M >> T;
  for(int i = 1; i <= N; ++i) 
    for(int j = 1; j <= M; ++j) 
      cin >> Circles[i][j];
  for(int i = 0; i < T; ++i)
    cin >> XDK[i][0] >> XDK[i][1] >> XDK[i][2];
}

void printCircles() {
  cout << "=======" << endl;
  for(int i = 1; i <= N; ++i) {
    cout << i << ": ";
    for(int j = 1; j <= M; ++j)
      cout << Circles[i][j] << " ";
    cout << endl;
  }
  cout << "=======" << endl;
}

void rotateCircle(int d, int k, int idx) {
  for(int i = 1; i <= M; ++i)
    Tmp[i] = Circles[idx][i];
  int cnt = 1;
  // clockwise
  if(d == 0) {
    for(int i = M-k+1; i <= M; ++i)
      Circles[idx][cnt++] = Tmp[i];
    for(int i = 1; i < M-k+1; ++i)
      Circles[idx][cnt++] = Tmp[i];
  }
  // anticlockwise
  else if(d == 1) {
    for(int i = k+1; i <= M; ++i)
      Circles[idx][cnt++] = Tmp[i];
    for(int i = 1; i < k+1; ++i)
      Circles[idx][cnt++] = Tmp[i];
  }
}

void deleteNumber(int a, int b, int c, int d) {
  Deleted = true;
  Circles[a][b] = -INF;
  Circles[c][d] = -INF;
}

void checkCircles() {
  double sum = 0;
  int cnt = 0;
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= M; ++j) {
      _Circles[i][j] = Circles[i][j];
      if(Circles[i][j] != -INF) {
        sum += Circles[i][j];
        cnt++;
      }
    }
  Deleted = false;

  for(int i = 1; i <= N; ++i) {
    for(int j = 1; j <= M; ++j) {
      if(_Circles[i][j] == -INF) continue;
      // vertical
      if(i == 1) {
        if(_Circles[1][j] == _Circles[2][j])
          deleteNumber(1, j, 2, j);
      }
      else if(i == N) {
        if(_Circles[N][j] == _Circles[N-1][j])
          deleteNumber(N, j, N-1, j);
      }
      else {
        if(_Circles[i][j] == _Circles[i-1][j])
          deleteNumber(i, j, i-1, j);
        if(_Circles[i][j] == _Circles[i+1][j])
          deleteNumber(i, j, i+1, j);
      }
      // horizontal
      if(j == 1) {
        if(_Circles[i][1] == _Circles[i][2])
          deleteNumber(i, 1, i, 2);
        if(_Circles[i][1] == _Circles[i][M])
          deleteNumber(i, 1, i, M);
      }
      else if(j == M) {
        if(_Circles[i][M] == _Circles[i][1])
          deleteNumber(i, M, i, 1);
        if(_Circles[i][M] == _Circles[i][M-1])
          deleteNumber(i, M, i, M-1);
      }
      else {
        if(_Circles[i][j] == _Circles[i][j+1])
          deleteNumber(i, j, i, j+1);
        if(_Circles[i][j] == _Circles[i][j-1])
          deleteNumber(i, j, i, j-1);
      }
    }
  }
  if(!Deleted) {
    double avg = sum / (double)cnt;
    for(int i = 1; i <= N; ++i)
      for(int j = 1; j <= M; ++j) {
        if(Circles[i][j] == -INF) continue;
        if(Circles[i][j] > avg)
          Circles[i][j]--;
        else if(Circles[i][j] < avg)
          Circles[i][j]++;
      }
  }
}

void getAnswer() {
  for(int i = 1; i <= N; ++i)
    for(int j = 1; j <= M; ++j) {
      if(Circles[i][j] == -INF) continue;
      Answer += Circles[i][j];
    }
}

void solution() {
  for(int i = 0; i < T; ++i) {
    int x = XDK[i][0];
    int d = XDK[i][1];
    int k = XDK[i][2];

    for(int j = x; j <= N; j += x) 
      rotateCircle(d, k, j);
    // printCircles();

    checkCircles();
  }
  getAnswer();
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
