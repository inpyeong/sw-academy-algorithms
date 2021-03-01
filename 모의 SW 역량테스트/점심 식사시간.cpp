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
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct Stair {
  int y, x;
  int len;
  // 현재 이용자 수
  int num;
  Stair(int _y, int _x, int _len, int _num): y(_y), x(_x), len(_len), num(_num) {};
};

struct Person {
  int y, x;
  // 계단까지 가는데 걸리는 시간
  int moveTime;
  // 계단을 이용하기 시작하는 시간
  int startT;
  // 계단 이용을 끝내는 시간
  int endT;
  bool fin;
  Person(int _y, int _x, int _moveTime, int _startT, int _enT, int _fin): y(_y), x(_x), moveTime(_moveTime), startT(_startT), endT(_enT), fin(_fin) {};
};

const int mxN = 10, INF = 987654321;

int n, pNum, answer;
vector<vector<int> > room(mxN, vector<int>(mxN));
// 사람마다 고른 계단의 번호(0, 1)
vector<int> Select(mxN);
vector<Stair> stairs;
vector<Person> people;
// 2개의 계단에서 대기열 역할을 해주는 Queue
queue<int> waiting[2];

void init() {
  for(int i = 0; i < pNum; ++i) {
    people[i].moveTime = people[i].startT = people[i].endT = -1;
    people[i].fin = false;
  }
  for(int i = 0; i < 2; ++i) {
    while(!waiting[i].empty()) waiting[i].pop();
    stairs[i].num = 0;
  }
}

int getDist(int p, int s) {
  int dx = abs(people[p].x - stairs[s].x);
  int dy = abs(people[p].y - stairs[s].y);
  return (dx + dy) + 1;
}

void completeMoving(int t) {
  for(int i = 0; i < pNum; ++i)
    if(people[i].endT == t) {
      people[i].fin = true;
      stairs[Select[i]].num--;
    }
}

bool check() {
  for(int i = 0; i < pNum; ++i)
    if(people[i].fin == false)
      return false;
  return true;
}

// 계단에 도착하면 일단 대기열에 넣는다.
void goToStairs(int t) {
  for(int i = 0; i < pNum; ++i)
    if(people[i].moveTime == t)
      waiting[Select[i]].push(i);
}

void simulate() {
  init();
  for(int i = 0; i < pNum; ++i) 
    people[i].moveTime = getDist(i, Select[i]);
  int time = 0;
  while(true) {
    completeMoving(time);
    if(check()) break;
    goToStairs(time);
    for(int i = 0; i < 2; ++i) {
      int stairNum = stairs[i].num;
      int waitingSz = waiting[i].size();
      // 계단에 내려갈 수 있다면
      if(stairNum < 3 && waitingSz > 0) {
        while(!waiting[i].empty()) {
          // 3명이 계단을 내려가고 있으면 중지
          if(stairs[i].num == 3) break;
          people[waiting[i].front()].startT = time;
          people[waiting[i].front()].endT = (time + stairs[i].len);
          stairs[i].num++;
          waiting[i].pop();
        }
      }
    }
    time++;
  }
  answer = min(answer, time);
}

void dfs(int p) {
  if(p == pNum) {
    simulate();
    return;
  }
  for(int s = 0; s < 2; ++s) {
    Select[p] = s;
    dfs(p+1);
  }
}

void solve(int tc) {
  cin >> n;
  pNum = 0;
  people.clear();
  stairs.clear();
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j) {
      cin >> room[i][j];
      if(room[i][j] == 1) {
        pNum++;
        people.push_back(Person(i, j, -1, -1, -1, false));
      }
      else if(room[i][j] >= 2) 
        stairs.push_back(Stair(i, j, room[i][j], 0));
    }

  answer = INF;
  dfs(0);
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
