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
#include <algorithm>

using namespace std;

const int MAX = 100;

struct Community {
  int y, x;
  int sz;
  int dir;
  Community(int _y, int _x, int _sz, int _dir): y(_y), x(_x), sz(_sz), dir(_dir) {};
};

int answer;
// N: 셀의 개수, M: 격리 시간, K: 미생물 군집의 개수
int N, M, K;
// 상: 1, 하: 2, 좌: 3, 우: 4
int dy[] = { 0, -1, 1,  0, 0 };
int dx[] = { 0,  0, 0, -1, 1 };
vector<int> board[MAX][MAX];
vector<Community> communities;

void initialize() {
  answer = 0;
  communities.clear();
  for(int i = 0; i < MAX; ++i)
    for(int j = 0; j < MAX; ++j)
      board[i][j].clear();
}

void input() {
  cin >> N >> M >> K;
  for(int i = 0; i < K; ++i) {
    int y, x, sz, dir;
    cin >> y >> x >> sz >> dir;
    Community community = Community(y, x, sz, dir);
    communities.push_back(community);
    board[y][x].push_back(i);
  }
}

void moveCommunities() {
  for(int i = 0; i < communities.size(); ++i) {
    if(communities[i].sz == 0) continue;
    board[communities[i].y][communities[i].x].clear();
  }
  for(int i = 0; i < communities.size(); ++i) {
    if(communities[i].sz == 0) continue;
    communities[i].y += dy[communities[i].dir];
    communities[i].x += dx[communities[i].dir];
    board[communities[i].y][communities[i].x].push_back(i);
  }
}

int changeDir(int dir) {
  int ret;
  if(dir == 1) ret = 2;
  else if(dir == 2) ret = 1;
  else if(dir == 3) ret = 4;
  else if(dir == 4) ret = 3;
  return ret;
}

void killAndMergeCommunities() {
  for(int i = 0; i < communities.size(); ++i) {
    if(communities[i].sz == 0) continue;
    int y = communities[i].y;
    int x = communities[i].x;
    int dir = communities[i].dir;
    if(y == 0 || y == N-1 || x == 0 || x == N-1) {
      communities[i].sz /= 2;
      communities[i].dir = changeDir(dir);
    }
  }
  for(int i = 0; i < communities.size(); ++i) {
    if(communities[i].sz == 0) continue;
    int y = communities[i].y;
    int x = communities[i].x;
    if(board[y][x].size() > 1) {
      int sum = 0;
      int bigSz = 0;
      int idx = 0;
      int dir = 0;
      for(int j = 0; j < board[y][x].size(); ++j) {
        sum += communities[board[y][x][j]].sz;
        if(communities[board[y][x][j]].sz > bigSz) {
          bigSz = communities[board[y][x][j]].sz;
          idx = board[y][x][j];
          dir = communities[board[y][x][j]].dir;
        }
        communities[board[y][x][j]].sz = 0;
      }
      communities[idx].sz = sum;
      communities[idx].dir = dir;
      board[y][x].clear();
      board[y][x].push_back(idx);
    }
  }
}

int calculate() {
  int ret = 0;
  for(int i = 0; i < communities.size(); ++i)
    ret += communities[i].sz;
  return ret;
}

void solution() {
  for(int i = 0; i < M; ++i) {
    moveCommunities();
    killAndMergeCommunities();
  }
  answer = calculate();
}

void solve(int tc) {
  initialize();
  input();
  solution();
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
