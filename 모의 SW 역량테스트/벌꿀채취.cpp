/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 10;

int n, m, c, answer;
int hives[MAX][MAX];
int visited[MAX][MAX];
bool selected[5];
// 0: a, 1: b
int maxValue[2];
vector<int> aHoneys, bHoneys;

void initialize() {
  answer = 0;
  maxValue[0] = maxValue[1] = 0;
  memset(visited, false, sizeof(visited));
  memset(selected, false, sizeof(selected));
  memset(hives, 0, sizeof(hives));
  aHoneys.clear();
  bHoneys.clear();
}

void simpleInitialize() {
  maxValue[0] = maxValue[1] = 0;
  aHoneys.clear();
  bHoneys.clear();
  memset(selected, false, sizeof(selected));
}

void input() {
  cin >> n >> m >> c;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      cin >> hives[i][j];
}

bool canSelect(int y, int x) {
  for(int i = x; i < x+m; ++i)
    if(visited[y][i] != 0 || i >= n)
      return false;
  return true;
}

void collect(int y, int x, int val) {
  for(int i = x; i < x+m; ++i)
    visited[y][i] = val;
}

int getTotalHoneys(const vector<int>& honeys) {
  int ret = 0;
  for(int i = 0; i < honeys.size(); ++i)
    ret += honeys[i];
  return ret;
}

int getProfit(const vector<int>& honeys) {
  int ret = 0;
  for(int i = 0; i < honeys.size(); ++i)
    ret += (honeys[i] * honeys[i]);
  return ret;
}

void dfs(const vector<int> honeys, int val, int idx, int total, int profit) {
  if(total > c) return;
  if(maxValue[val] < profit)
    maxValue[val] = profit;
  for(int i = idx; i < m; ++i) {
    if(selected[i]) continue;
    selected[i] = true;
    dfs(honeys, val, i, total + honeys[i], profit + (honeys[i] * honeys[i]));
    selected[i] = false;
  }
}

void actualSelect(int y, int x, int val) {
  if(val == 2) {
    simpleInitialize();
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j) {
        if(visited[i][j] == 1) aHoneys.push_back(hives[i][j]);
        else if(visited[i][j] == 2) bHoneys.push_back(hives[i][j]);
      }
    // A가 모은 벌꿀의 양이 c 이하라면
    if(getTotalHoneys(aHoneys) <= c)
      maxValue[0] = max(maxValue[0], getProfit(aHoneys));
    // 조합을 통해 가장 큰 profit을 얻는다.
    else dfs(aHoneys, 0, 0, 0, 0);
    // B도 A와 똑같이 진행
    if(getTotalHoneys(bHoneys) <= c)
      maxValue[1] = max(maxValue[1], getProfit(bHoneys));
    else dfs(bHoneys, 1, 0, 0, 0);
    // 답 갱신
    answer = max(answer, maxValue[0] + maxValue[1]);
    return;
  }

  for(int i = y; i < n; ++i)
    for(int j = 0; j < n; ++j) {
      if(canSelect(i, j)) {
        collect(i, j, 2);
        actualSelect(i, j, 2);
        collect(i, j, 0);
      }
    }
}

void solve(int tc) {
  initialize();
  input();

  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j) {
      if(canSelect(i, j)) {
        collect(i, j, 1);
        actualSelect(i, j, 1);
        collect(i, j, 0);
      }
    }

  cout << "#" << tc << " " << answer << endl;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
    solve(test_case);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
