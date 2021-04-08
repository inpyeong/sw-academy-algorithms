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
#include <string>

using namespace std;

const int MAX_K = 100;

int k;
int chain[4][8];
pair<int, int> cmd[MAX_K];
int rotateInfo[4];

void initializeRotateInfo() {
    for(int i = 0; i < 4; ++i) 
        rotateInfo[i] = 0;
}

void input() {
    for(int i = 0; i < 4; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < 8; ++j) {
            chain[i][j] = str[j] - '0';
        }
    }
    cin >> k;
    for(int i = 0; i < k; ++i) {
        int f, s; 
        cin >> f >> s;
        cmd[i].first = f - 1;
        cmd[i].second = s;
    }
}

void rotateChain(int pos, int dir) {
    // 시계 방향 회전
    if(dir == 1) {
        int end = chain[pos][7];
        for(int i = 7; i >= 1; --i) 
            chain[pos][i] = chain[pos][i-1];
        chain[pos][0] = end;
    }
    // 반시계 방향 회전
    else if(dir == -1) {
        int begin = chain[pos][0];
        for(int i = 0; i <= 6; ++i)
            chain[pos][i] = chain[pos][i+1];
        chain[pos][7] = begin;
    }
}

void printAllChain() {
    cout << "=========" << endl;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 8; ++j)
            cout << chain[i][j] << " ";
        cout << endl;
    }
    cout << "=========" << endl;
}

int calcScore() {
    int ret = 0;
    if(chain[0][0] == 1) ret += 1;
    if(chain[1][0] == 1) ret += 2;
    if(chain[2][0] == 1) ret += 4;
    if(chain[3][0] == 1) ret += 8;
    return ret;
}

void solution() {
    for(int i = 0; i < k; ++i) {
        initializeRotateInfo();
        int pos = cmd[i].first;
        int dir = cmd[i].second;

        rotateInfo[pos] = dir;
        int posl = pos - 1, posr = pos + 1;
        while(posl >= 0 && rotateInfo[posl+1] != 0) {
            // 서로 맞닿은 톱니의 극이 다르다면 반시계 방향으로 회전
            if(chain[posl][2] != chain[posl+1][6]) 
                rotateInfo[posl] = -rotateInfo[posl+1];                
            posl--;
        }
        while(posr <= 3 && rotateInfo[posr-1] != 0) {
            // 서로 맞닿은 톱니의 극이 다르다면 반시계 방향으로 회전
            if(chain[posr-1][2] != chain[posr][6]) 
                rotateInfo[posr] = -rotateInfo[posr-1];                
            posr++;
        }
        for(int i = 0; i < 4; ++i)
            rotateChain(i, rotateInfo[i]);
    }
    // printAllChain();
    cout << calcScore() << endl;
}

void solve() {
    input();
    solution();
}

int main(int argc, char** argv)
{
	// int test_case;
	// int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	// freopen("input.txt", "r", stdin);
	// cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	// for(test_case = 1; test_case <= T; ++test_case)
	// {

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////

        solve();

	// }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}