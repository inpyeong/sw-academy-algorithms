#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 101;

int R, C, K;
int A[MAX][MAX];
int ARow, ACol;

void input() {
  cin >> R >> C >> K;
  for(int i = 1; i <= 3; ++i)
    for(int j = 1; j <= 3; ++j)
      cin >> A[i][j];
  ARow = 3, ACol = 3;
}

void printA() {
  cout << "============" << endl;
  for(int i = 1; i <= ARow; ++i) {
    for(int j = 1; j <= ACol; ++j)
      cout << A[i][j] << " ";
    cout << endl;
  }
}

bool cmp(pair<int, int>& a,pair<int, int>& b) {
  if(a.second == b.second)
    return a.first < b.first;
  return a.second < b.second;
}

void ROperation() {
  int nextACol = 0;
  for(int i = 1; i <= ARow; ++i) {
    vector<int> num;
    for(int j = 1; j <= ACol; ++j) {
      num.push_back(A[i][j]);
      A[i][j] = 0;
    }
    sort(num.begin(), num.end());

    vector<pair<int, int> > numWithCnt;
    int cnt = 1;
    for(int j = 0; j < ACol-1; ++j) {
      if(num[j] == num[j+1]) cnt++;
      else {
        numWithCnt.push_back(make_pair(num[j], cnt));
        cnt = 1;
      }
    }
    numWithCnt.push_back(make_pair(num[ACol-1], cnt));

    sort(numWithCnt.begin(), numWithCnt.end(), cmp);
    int idx = 1;
    for(int j = 0; j < numWithCnt.size(); ++j) {
      if(numWithCnt[j].first == 0) continue;
      A[i][idx++] = numWithCnt[j].first;
      if(idx > 100) break;
      A[i][idx++] = numWithCnt[j].second;
      if(idx > 100) break;
    }
    idx--;
    nextACol = max(nextACol, idx);
  }
  ACol = nextACol;
}

void COperation() {
  int nextARow = 0;
  for(int i = 1; i <= ACol; ++i) {
    vector<int> num;
    for(int j = 1; j <= ARow; ++j) {
      num.push_back(A[j][i]);
      A[j][i] = 0;
    }
    sort(num.begin(), num.end());

    vector<pair<int, int> > numWithCnt;
    int cnt = 1;
    for(int j = 0; j < ARow-1; ++j) {
      if(num[j] == num[j+1]) cnt++;
      else {
        numWithCnt.push_back(make_pair(num[j], cnt));
        cnt = 1;
      }
    }
    numWithCnt.push_back(make_pair(num[ARow-1], cnt));

    sort(numWithCnt.begin(), numWithCnt.end(), cmp);
    int idx = 1;
    for(int j = 0; j < numWithCnt.size(); ++j) {
      if(numWithCnt[j].first == 0) continue;
      A[idx++][i] = numWithCnt[j].first;
      if(idx > 100) break;
      A[idx++][i] = numWithCnt[j].second;
      if(idx > 100) break;
    }
    idx--;
    nextARow = max(nextARow, idx);
  }
  ARow = nextARow;
}

void solution() {
  int answer = 0;
  while(true) {
    if(A[R][C] == K) break;

    if(ARow >= ACol) ROperation();
    else COperation();

    answer++;
    if(answer > 100) {
      answer = -1;
      break;
    }
  }
  // printA();
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
