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

using namespace std;

const int MAX = 10, CUSTOM_MAX = 1001;

struct Customer {
  int num;
  int arrT;
  int receptionDesk;
  int repairDesk;
  int startReceptionT, endReceptionT;
  int startRepairT, endRepairT;
  bool fin;
};

struct Reception {
  bool use;
  int t;
};

struct Repair {
  bool use;
  int t;
};

int N, M, K, A, B, answer;
Customer customers[CUSTOM_MAX];
Reception receptionDesks[MAX];
Repair repairDesks[MAX];
queue<int> receptionQ, repairQ;

void initialize() {
  answer = 0;
  while(!receptionQ.empty()) receptionQ.pop();
  while(!repairQ.empty()) repairQ.pop();
}

void input() {
  cin >> N >> M >> K >> A >> B;
  for(int i = 1; i <= N; ++i) {
    int a; cin >> a;
    receptionDesks[i].t = a;
    receptionDesks[i].use = false;
  }
  for(int i = 1; i <= M; ++i) {
    int b; cin >> b;
    repairDesks[i].t = b;
    repairDesks[i].use = false;
  }
  for(int i = 1; i <= K; ++i) {
    int t; cin >> t;
    customers[i].num = i;
    customers[i].arrT = t;
    customers[i].receptionDesk = -1;
    customers[i].repairDesk = -1;
    customers[i].fin = false;
    customers[i].startReceptionT = customers[i].endReceptionT = -1;
    customers[i].startRepairT = customers[i].endRepairT = -1;
  }
}

void makeFinish(int time) {
  for(int i = 1; i <= K; ++i) {
    if(customers[i].endReceptionT == time)
      receptionDesks[customers[i].receptionDesk].use = false;
    if(customers[i].endRepairT == time) {
      repairDesks[customers[i].repairDesk].use = false;
      customers[i].fin = true;
    }
  }
}

bool finishCheck(int time) {
  for(int i = 1; i <= K; ++i)
    if(customers[i].fin == false)
      return false;
  return true;
}

bool receptionCmp(int a, int b) {
  return customers[a].num < customers[b].num;
}

bool repairCmp(int a, int b) {
  return customers[a].receptionDesk < customers[b].receptionDesk;
}

void arrive(int time, string s) {
  vector<int> v;
  if(s == "reception") {
    for(int i = 1; i <= K; ++i)
      if(customers[i].arrT == time)
        v.push_back(i);
    sort(v.begin(), v.end(), receptionCmp);
    for(int i = 0; i < v.size(); ++i)
      receptionQ.push(v[i]);
  }
  else {
    for(int i = 1; i <= K; ++i)
      if(customers[i].startRepairT == time)
        v.push_back(i);
    sort(v.begin(), v.end(), repairCmp);
    for(int i = 0; i < v.size(); ++i)
      repairQ.push(v[i]);
  }
}

int remaining(string s) {
  int ret = 0;
  if(s == "reception") {
    for(int i = 1; i <= N; ++i)
      if(receptionDesks[i].use == false)
        ret++;
  }
  else {
    for(int i = 1; i <= M; ++i)
      if(repairDesks[i].use == false)
        ret++;
  }
  return ret;
}

void service(int time, int idx, string s) {
  if(s == "reception") {
    for(int i = 1; i <= N; ++i)
      if(receptionDesks[i].use == false) {
        receptionDesks[i].use = true;
        customers[idx].receptionDesk = i;
        customers[idx].startReceptionT = time;
        customers[idx].endReceptionT = time + receptionDesks[i].t;
        customers[idx].startRepairT = customers[idx].endReceptionT;
        return;
      }
  }
  else {
    for(int i = 1; i <= M; ++i)
      if(repairDesks[i].use == false) {
        repairDesks[i].use = true;
        customers[idx].repairDesk = i;
        customers[idx].startRepairT = time;
        customers[idx].endRepairT = time + repairDesks[i].t;
        return;
      }
  }
}

void solution() {
  int time = 0;
  while(true) {
    makeFinish(time);
    if(finishCheck(time)) break;

    arrive(time, "reception");
    int remainingReceptions = remaining("reception");
    int receptionQSz = receptionQ.size();
    if(receptionQSz > 0 && remainingReceptions > 0) {
      while(!receptionQ.empty()) {
        if(remainingReceptions == 0) break;
        service(time, receptionQ.front(), "reception");
        receptionQ.pop();
        remainingReceptions--;
      }
    }

    arrive(time, "repair");
    int remainingRepairs = remaining("repair");
    int repairQSz = repairQ.size();
    if(repairQSz > 0 && remainingRepairs > 0) {
      while(!repairQ.empty()) {
        if(remainingRepairs == 0) break;
        service(time, repairQ.front(), "repair");
        repairQ.pop();
        remainingRepairs--;
      }
    }
    time++;
  }

  for(int i = 1; i <= K; ++i)
    if(customers[i].receptionDesk == A && customers[i].repairDesk == B)
      answer += i;
  if(answer == 0) answer = -1;
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
