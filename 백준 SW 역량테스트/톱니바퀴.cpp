#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int mxK = 100;

int K, Answer;
vector<int> Wheel[5];
pair<int, int> Cmd[mxK];
int DirState[5];

void input() {
  for(int i = 1; i <= 4; ++i) {
    string s;
    cin >> s;
    for(char c : s) Wheel[i].push_back(c-'0');
  }
  cin >> K;
  for(int i = 0; i < K; ++i) 
    cin >> Cmd[i].first >> Cmd[i].second;
}

void printWheels() {
  cout << "=========" << endl;
  for(int i = 1; i <= 4; ++i) {
    for(int j = 0; j < 8; ++j)
      cout << Wheel[i][j] << " ";
    cout << endl;
  }
}

void rotateWheel(int idx) {
  int d = DirState[idx];
  int tmp;
  if(d == 1) {
    tmp = Wheel[idx].back();
    Wheel[idx].pop_back();
    Wheel[idx].insert(Wheel[idx].begin(), tmp);
  }
  else if(d == -1) {
    tmp = Wheel[idx].front();
    Wheel[idx].erase(Wheel[idx].begin());
    Wheel[idx].push_back(tmp);
  }
}

void solution() {
  for(int i = 0; i < K; ++i) {
    int posl = Cmd[i].first - 1;
    int posr = Cmd[i].first + 1;
    memset(DirState, 0, sizeof(DirState));
    DirState[Cmd[i].first] = Cmd[i].second;

    while(posl >= 1) {
      if(Wheel[posl][2] != Wheel[posl+1][6]) {
        DirState[posl] = -DirState[posl+1];
        posl--;
      }
      else break;
    }

    while(posr <= 4) {
      if(Wheel[posr-1][2] != Wheel[posr][6]) {
        DirState[posr] = -DirState[posr-1];
        posr++;
      }
      else break;
    }

    for(int j = 1; j <= 4; ++j) 
      rotateWheel(j);
  }
  // printWheels();

  if(Wheel[1][0]) Answer += 1;
  if(Wheel[2][0]) Answer += 2;
  if(Wheel[3][0]) Answer += 4;
  if(Wheel[4][0]) Answer += 8;
}

void solve() {
  input();
  solution();
  cout << Answer << endl;
}

int main() {
  solve();
  return 0;
}
