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
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 10, INF = 987654321;

int n, m, answer;
char board[MAX][MAX];
// 0: red
// 1: blue
bool discovered[MAX][MAX][2];
int ry, rx, by, bx;

struct Ball {
    int y, x;
    int moveCnt;
    string color;
    Ball(int _y, int _x, int _moveCnt, string _color): y(_y), x(_x), moveCnt(_moveCnt), color(_color) {};
};

int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1 };
// first: red
// second: blue
typedef pair<Ball, Ball> PairBall;

void initialize() {
    answer = INF;
    memset(discovered, false, sizeof(discovered));
}

void input() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i) 
        for(int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if(board[i][j] == 'R') 
                ry = i, rx = j;
            if(board[i][j] == 'B')
                by = i, bx = j;
        }
}

void solution() {
    queue<PairBall> q;
    q.push(make_pair(Ball(ry, rx, 0, "red"), Ball(by, bx, 0, "blue")));
    discovered[ry][rx][0] = true;
    discovered[by][bx][1] = true;
    while(!q.empty()) {
        PairBall pb = q.front();
        q.pop();
        Ball red = pb.first;
        Ball blue = pb.second;
        // 빨간 공이 구멍 위치에 있으면 게임 성공
        if(board[red.y][red.x] == '0') {
            answer = min(answer, red.moveCnt);
            continue;
        }
        // 파란 공이 구멍에 빠진 경우 게임 실패
        if(board[blue.y][blue.x] == '0')
            continue;
        for(int i = 0; i < 4; ++i) {
            int rny = red.y + dy[i];
            int rnx = red.x + dx[i];
            int bny = blue.y + dy[i];
            int bnx = blue.x + dx[i];
            // 빨간 공, 파란 공의 위치가 보드 밖이라면 고려하지 않는다.
            if(rny < 0 || rny >= n || rnx < 0 || rnx >= m || bny < 0 || bny >= n || bnx < 0 || bnx >= m)
                continue;
            // 빨간 공, 파란 공의 다음 위치가 벽인 경우 고려하지 않는다.
            if(board[rny][rnx] == '#' || board[bny][bnx] == '#')
                continue;
            // 이미 방문했던 좌표라면 고려하지 않는다.
            if(discovered[rny][rnx][0] || discovered[bny][bnx])
                continue;
            q.push(make_pair(Ball(rny, rnx, red.moveCnt+1, "red"), Ball(bny, bny, blue.moveCnt+1, "blue")));
            discovered[rny][rnx][0] = true;
            discovered[bny][bnx][1] = true;
        }
    }
    if(answer > 10) answer = -1;
}

void solve() {
    initialize();
    input();
    solution();
    cout << answer << endl;
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
        solve();

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}