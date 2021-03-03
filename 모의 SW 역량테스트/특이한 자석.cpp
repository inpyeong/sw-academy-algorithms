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

using namespace std;

int k, answer;
vector<vector<int> > wheels(4, vector<int>(8));
// turns: 자석의 화전 정보
vector<pair<int, int> > turns;
// turnDir: 바퀴를 돌리는 방향을 저장한다.
vector<int> turnDir(4, 0);

void initialize() {
    answer = 0;
    turns.clear();
}

void input() {
    cin >> k;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 8; ++j) {
            int m; cin >> m;
            wheels[i][j] = m;
        }
    for(int i = 0; i < k; ++i) {
        int w, d;
        cin >> w >> d;
        turns.push_back(make_pair(w-1, d));
    }
}

void getTurnInfo(int i) {
    int idx = turns[i].first;
    int dir = turns[i].second;
    turnDir[idx] = dir;

    int left = idx - 1, right = idx + 1;
    while(left >= 0) {
        if(turnDir[left+1] == 0) break;
        if(wheels[left][2] != wheels[left+1][6])
            turnDir[left] = -turnDir[left+1];
        else
            turnDir[left] = 0;
        left--;
    }
    while(right < 4) {
        if(turnDir[right-1] == 0) break;
        if(wheels[right][6] != wheels[right-1][2]) 
            turnDir[right] = -turnDir[right-1];
        else
            turnDir[right] = 0;
        right++;
    }
}

void turnWheels() {
    for(int i = 0; i < 4; ++i) {
        // 시계방향 회전
        if(turnDir[i] == 1) {
            int tmp = wheels[i].back();
            wheels[i].pop_back();
            wheels[i].insert(wheels[i].begin(), tmp);
        }
        // 반시계방향
        else if(turnDir[i] == -1) {
            int tmp = wheels[i].front();
            wheels[i].erase(wheels[i].begin());
            wheels[i].push_back(tmp);
        }
    }
    turnDir = vector<int>(4, 0);
}

void calculate() {
    for(int i = 0; i < 4; ++i) {
        if(wheels[i][0] == 1) {
            switch(i) {
                case 0:
                    answer += 1;
                    break;
                case 1:
                    answer += 2;
                    break;
                case 2:
                    answer += 4;
                    break;
                case 3:
                    answer += 8;
                    break;
            }
        }
    }    
}

void solve(int tc) {
    initialize();
    input();
    for(int i = 0; i < k; ++i) {
        getTurnInfo(i);
        turnWheels();
    }
    calculate();
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