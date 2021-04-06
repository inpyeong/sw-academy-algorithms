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

using namespace std;

const int MAX = 50;

struct Robot {
    int y, x;
    int d;
    int cleaning;
} robot;

int n, m, answer;
int r, c, d;
int board[MAX][MAX];
bool check[MAX][MAX];

int dy[] = { -1, 0, 1,  0 };
int dx[] = {  0, 1, 0, -1 };

void input() {
    cin >> n >> m;
    cin >> r >> c >> d;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) 
            cin >> board[i][j];
    robot.y = r;
    robot.x = c;
    robot.d = d;
    robot.cleaning = 0;
}

int turnLeft(int d) {
    if(d == 0) return 3;
    else if(d == 1) return 0;
    else if(d == 2) return 1;
    else if(d == 3) return 2;
}

int getBackDirection(int d) {
    if(d == 0) return 2;
    else if(d == 1) return 3;
    else if(d == 2) return 0;
    else if(d == 3) return 1;
}

void solution() {
    while(true) {
        int y = robot.y;
        int x = robot.x;
        int d = robot.d;
        int cleaning = robot.cleaning;
        // 현 위치 청소
        if(check[y][x] == false) {
            check[y][x] = true;
            robot.cleaning++;
        }
        // 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행
        bool canClean = false;
        int nd = d;
        for(int i = 0; i < 4; ++i) {
            nd = turnLeft(nd);
            int ny = y + dy[nd];
            int nx = x + dx[nd];
            // 아직 청소하지 않은 공간이 존재한다면
            if(board[ny][nx] == 0 && check[ny][nx] == false) {
                // 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행
                robot.y = ny;
                robot.x = nx;
                robot.d = nd;
                canClean = true;
                break;
            }
        }
        // 청소하지 못했다면
        if(!canClean) {
            int back = getBackDirection(robot.d);
            int ny = y + dy[back];
            int nx = x + dx[back];
            // 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우
            if(board[ny][nx] == 1) break;
            else {
                robot.y = ny;
                robot.x = nx;
            }
            
        }
    }
}

void solve() {
    input();
    solution();
    cout << robot.cleaning << "\n";
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
	//freopen("input.txt", "r", stdin);
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