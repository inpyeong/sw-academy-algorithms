#include <iostream> 
#include <vector>

using namespace std;

struct Cube {
  char U[9], D[9], F[9], B[9], L[9], R[9];
}Cube;

int N, M;
char Side, Dir;
vector<char> Answer;

void init() {
  for(int i = 0; i < 9; ++i) {
    Cube.U[i] = 'w';
    Cube.D[i] = 'y';
    Cube.F[i] = 'r';
    Cube.B[i] = 'o';
    Cube.L[i] = 'g';
    Cube.R[i] = 'b';
  }
}

void input() {
  cin >> N;
}

void rotateCube() {
  char tmp, tmp2, tmp3;
  char tmp4[9];
  if(Side == 'U') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.U[i];

      Cube.U[0] = tmp4[2];
      Cube.U[1] = tmp4[5];
      Cube.U[2] = tmp4[8];
      Cube.U[3] = tmp4[1];
      Cube.U[4] = tmp4[4];
      Cube.U[5] = tmp4[7];
      Cube.U[6] = tmp4[0];
      Cube.U[7] = tmp4[3];
      Cube.U[8] = tmp4[6];

      tmp = Cube.F[0];
      tmp2 = Cube.F[1];
      tmp3 = Cube.F[2];

      Cube.F[0] = Cube.L[0];
      Cube.F[1] = Cube.L[1];
      Cube.F[2] = Cube.L[2];

      Cube.L[0] = Cube.B[0];
      Cube.L[1] = Cube.B[1];
      Cube.L[2] = Cube.B[2];

      Cube.B[0] = Cube.R[0];
      Cube.B[1] = Cube.R[1];
      Cube.B[2] = Cube.R[2];

      Cube.R[0] = tmp;
      Cube.R[1] = tmp2;
      Cube.R[2] = tmp3;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.U[i];

      Cube.U[0] = tmp4[6];
      Cube.U[1] = tmp4[3];
      Cube.U[2] = tmp4[0];
      Cube.U[3] = tmp4[7];
      Cube.U[4] = tmp4[4];
      Cube.U[5] = tmp4[1];
      Cube.U[6] = tmp4[8];
      Cube.U[7] = tmp4[5];
      Cube.U[8] = tmp4[2];

      tmp = Cube.F[0];
      tmp2 = Cube.F[1];
      tmp3 = Cube.F[2];

      Cube.F[0] = Cube.R[0];
      Cube.F[1] = Cube.R[1];
      Cube.F[2] = Cube.R[2];

      Cube.R[0] = Cube.B[0];
      Cube.R[1] = Cube.B[1];
      Cube.R[2] = Cube.B[2];

      Cube.B[0] = Cube.L[0];
      Cube.B[1] = Cube.L[1];
      Cube.B[2] = Cube.L[2];

      Cube.L[0] = tmp;
      Cube.L[1] = tmp2;
      Cube.L[2] = tmp3;
    }
  }
  else if(Side == 'D') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.D[i];

      Cube.D[0] = tmp4[2];
      Cube.D[1] = tmp4[5];
      Cube.D[2] = tmp4[8];
      Cube.D[3] = tmp4[1];
      Cube.D[4] = tmp4[4];
      Cube.D[5] = tmp4[7];
      Cube.D[6] = tmp4[0];
      Cube.D[7] = tmp4[3];
      Cube.D[8] = tmp4[6];

      tmp = Cube.F[6];
      tmp2 = Cube.F[7];
      tmp3 = Cube.F[8];

      Cube.F[6] = Cube.R[6];
      Cube.F[7] = Cube.R[7];
      Cube.F[8] = Cube.R[8];

      Cube.R[6] = Cube.B[6];
      Cube.R[7] = Cube.B[7];
      Cube.R[8] = Cube.B[8];

      Cube.B[6] = Cube.L[6];
      Cube.B[7] = Cube.L[7];
      Cube.B[8] = Cube.L[8];

      Cube.L[6] = tmp;
      Cube.L[7] = tmp2;
      Cube.L[8] = tmp3;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.D[i];

      Cube.D[0] = tmp4[6];
      Cube.D[1] = tmp4[3];
      Cube.D[2] = tmp4[0];
      Cube.D[3] = tmp4[7];
      Cube.D[4] = tmp4[4];
      Cube.D[5] = tmp4[1];
      Cube.D[6] = tmp4[8];
      Cube.D[7] = tmp4[5];
      Cube.D[8] = tmp4[2];

      tmp = Cube.F[6];
      tmp2 = Cube.F[7];
      tmp3 = Cube.F[8];

      Cube.F[6] = Cube.L[6];
      Cube.F[7] = Cube.L[7];
      Cube.F[8] = Cube.L[8];

      Cube.L[6] = Cube.B[6];
      Cube.L[7] = Cube.B[7];
      Cube.L[8] = Cube.B[8];

      Cube.B[6] = Cube.R[6];
      Cube.B[7] = Cube.R[7];
      Cube.B[8] = Cube.R[8];

      Cube.R[6] = tmp;
      Cube.R[7] = tmp2;
      Cube.R[8] = tmp3;
    }
  }
  else if(Side == 'F') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.F[i];

      Cube.F[0] = tmp4[2];
      Cube.F[1] = tmp4[5];
      Cube.F[2] = tmp4[8];
      Cube.F[3] = tmp4[1];
      Cube.F[4] = tmp4[4];
      Cube.F[5] = tmp4[7];
      Cube.F[6] = tmp4[0];
      Cube.F[7] = tmp4[3];
      Cube.F[8] = tmp4[6];

      tmp = Cube.U[6];
      tmp2 = Cube.U[7];
      tmp3 = Cube.U[8];

      Cube.U[6] = Cube.R[0];
      Cube.U[7] = Cube.R[3];
      Cube.U[8] = Cube.R[6];

      Cube.R[0] = Cube.D[2];
      Cube.R[3] = Cube.D[1];
      Cube.R[6] = Cube.D[0];

      Cube.D[0] = Cube.L[2];
      Cube.D[1] = Cube.L[5];
      Cube.D[2] = Cube.L[8];

      Cube.L[2] = tmp3;
      Cube.L[5] = tmp2;
      Cube.L[8] = tmp;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.F[i];

      Cube.F[0] = tmp4[6];
      Cube.F[1] = tmp4[3];
      Cube.F[2] = tmp4[0];
      Cube.F[3] = tmp4[7];
      Cube.F[4] = tmp4[4];
      Cube.F[5] = tmp4[1];
      Cube.F[6] = tmp4[8];
      Cube.F[7] = tmp4[5];
      Cube.F[8] = tmp4[2];

      tmp = Cube.U[6];
      tmp2 = Cube.U[7];
      tmp3 = Cube.U[8];

      Cube.U[6] = Cube.L[8];
      Cube.U[7] = Cube.L[5];
      Cube.U[8] = Cube.L[2];

      Cube.L[2] = Cube.D[0];
      Cube.L[5] = Cube.D[1];
      Cube.L[8] = Cube.D[2];

      Cube.D[0] = Cube.R[6];
      Cube.D[1] = Cube.R[3];
      Cube.D[2] = Cube.R[0];

      Cube.R[0] = tmp;
      Cube.R[3] = tmp2;
      Cube.R[6] = tmp3;
    }
  }
  else if(Side == 'B') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.B[i];

      Cube.B[0] = tmp4[2];
      Cube.B[1] = tmp4[5];
      Cube.B[2] = tmp4[8];
      Cube.B[3] = tmp4[1];
      Cube.B[4] = tmp4[4];
      Cube.B[5] = tmp4[7];
      Cube.B[6] = tmp4[0];
      Cube.B[7] = tmp4[3];
      Cube.B[8] = tmp4[6];

      tmp = Cube.U[2];
      tmp2 = Cube.U[1];
      tmp3 = Cube.U[0];

      Cube.U[2] = Cube.L[0];
      Cube.U[1] = Cube.L[3];
      Cube.U[0] = Cube.L[6];

      Cube.L[0] = Cube.D[6];
      Cube.L[3] = Cube.D[7];
      Cube.L[6] = Cube.D[8];

      Cube.D[6] = Cube.R[8];
      Cube.D[7] = Cube.R[5];
      Cube.D[8] = Cube.R[2];

      Cube.R[8] = tmp;
      Cube.R[5] = tmp2;
      Cube.R[2] = tmp3;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.B[i];

      Cube.B[0] = tmp4[6];
      Cube.B[1] = tmp4[3];
      Cube.B[2] = tmp4[0];
      Cube.B[3] = tmp4[7];
      Cube.B[4] = tmp4[4];
      Cube.B[5] = tmp4[1];
      Cube.B[6] = tmp4[8];
      Cube.B[7] = tmp4[5];
      Cube.B[8] = tmp4[2];

      tmp = Cube.U[2];
      tmp2 = Cube.U[1];
      tmp3 = Cube.U[0];

      Cube.U[2] = Cube.R[8];
      Cube.U[1] = Cube.R[5];
      Cube.U[0] = Cube.R[2];

      Cube.R[2] = Cube.D[8];
      Cube.R[5] = Cube.D[7];
      Cube.R[8] = Cube.D[6];

      Cube.D[8] = Cube.L[6];
      Cube.D[7] = Cube.L[3];
      Cube.D[6] = Cube.L[0];

      Cube.L[0] = tmp;
      Cube.L[3] = tmp2;
      Cube.L[6] = tmp3;
    }
  }
  else if(Side == 'L') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.L[i];

      Cube.L[0] = tmp4[2];
      Cube.L[1] = tmp4[5];
      Cube.L[2] = tmp4[8];
      Cube.L[3] = tmp4[1];
      Cube.L[4] = tmp4[4];
      Cube.L[5] = tmp4[7];
      Cube.L[6] = tmp4[0];
      Cube.L[7] = tmp4[3];
      Cube.L[8] = tmp4[6];

      tmp = Cube.U[0];
      tmp2 = Cube.U[3];
      tmp3 = Cube.U[6];

      Cube.U[0] = Cube.F[0];
      Cube.U[3] = Cube.F[3];
      Cube.U[6] = Cube.F[6];

      Cube.F[0] = Cube.D[0];
      Cube.F[3] = Cube.D[3];
      Cube.F[6] = Cube.D[6];

      Cube.D[0] = Cube.B[8];
      Cube.D[3] = Cube.B[5];
      Cube.D[6] = Cube.B[2];

      Cube.B[8] = tmp;
      Cube.B[5] = tmp2;
      Cube.B[2] = tmp3;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.L[i];

      Cube.L[0] = tmp4[6];
      Cube.L[1] = tmp4[3];
      Cube.L[2] = tmp4[0];
      Cube.L[3] = tmp4[7];
      Cube.L[4] = tmp4[4];
      Cube.L[5] = tmp4[1];
      Cube.L[6] = tmp4[8];
      Cube.L[7] = tmp4[5];
      Cube.L[8] = tmp4[2];

      tmp = Cube.U[0];
      tmp2 = Cube.U[3];
      tmp3 = Cube.U[6];

      Cube.U[0] = Cube.B[8];
      Cube.U[3] = Cube.B[5];
      Cube.U[6] = Cube.B[2];

      Cube.B[8] = Cube.D[0];
      Cube.B[5] = Cube.D[3];
      Cube.B[2] = Cube.D[6];

      Cube.D[0] = Cube.F[0];
      Cube.D[3] = Cube.F[3];
      Cube.D[6] = Cube.F[6];

      Cube.F[0] = tmp;
      Cube.F[3] = tmp2;
      Cube.F[6] = tmp3;
    }
  }
  else if(Side == 'R') {
    if(Dir == '-') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.R[i];

      Cube.R[0] = tmp4[2];
      Cube.R[1] = tmp4[5];
      Cube.R[2] = tmp4[8];
      Cube.R[3] = tmp4[1];
      Cube.R[4] = tmp4[4];
      Cube.R[5] = tmp4[7];
      Cube.R[6] = tmp4[0];
      Cube.R[7] = tmp4[3];
      Cube.R[8] = tmp4[6];

      tmp = Cube.U[8];
      tmp2 = Cube.U[5];
      tmp3 = Cube.U[2];

      Cube.U[8] = Cube.B[0];
      Cube.U[5] = Cube.B[3];
      Cube.U[2] = Cube.B[6];

      Cube.B[0] = Cube.D[8];
      Cube.B[3] = Cube.D[5];
      Cube.B[6] = Cube.D[2];

      Cube.D[8] = Cube.F[8];
      Cube.D[5] = Cube.F[5];
      Cube.D[2] = Cube.F[2];

      Cube.F[8] = tmp;
      Cube.F[5] = tmp2;
      Cube.F[2] = tmp3;
    }
    else if(Dir == '+') {
      for(int i = 0; i < 9; ++i)
        tmp4[i] = Cube.R[i];

      Cube.R[0] = tmp4[6];
      Cube.R[1] = tmp4[3];
      Cube.R[2] = tmp4[0];
      Cube.R[3] = tmp4[7];
      Cube.R[4] = tmp4[4];
      Cube.R[5] = tmp4[1];
      Cube.R[6] = tmp4[8];
      Cube.R[7] = tmp4[5];
      Cube.R[8] = tmp4[2];

      tmp = Cube.U[8];
      tmp2 = Cube.U[5];
      tmp3 = Cube.U[2];

      Cube.U[8] = Cube.F[8];
      Cube.U[5] = Cube.F[5];
      Cube.U[2] = Cube.F[2];

      Cube.F[8] = Cube.D[8];
      Cube.F[5] = Cube.D[5];
      Cube.F[2] = Cube.D[2];

      Cube.D[2] = Cube.B[6];
      Cube.D[5] = Cube.B[3];
      Cube.D[8] = Cube.B[0];

      Cube.B[0] = tmp;
      Cube.B[3] = tmp2;
      Cube.B[6] = tmp3;
    }
  }
}

void printU() {
  for(int i = 0; i < Answer.size(); ++i) {
    cout << Answer[i];
    if(i % 3 == 2) cout << endl;
  }
}

void solution() {
  for(int i = 0; i < N; ++i) {
    init();
    cin >> M;
    for(int j = 0; j < M; ++j) {
      cin >> Side >> Dir;
      rotateCube();
    }
    for(int j = 0; j < 9; ++j)
      Answer.push_back(Cube.U[j]);
  }
  printU();
}

void solve() {
  input();
  solution();
}

int main() {
  solve();
  return 0;
}
