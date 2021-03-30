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

using namespace std;

const int MAX_N = 100;

int n, k, l;
int board[MAX_N][MAX_N];
vector<pair<int, char> > cmd;

int dy[] = { 0,  0, 1, -1 };
int dx[] = { 1, -1, 0,  0 };

void input() {
    cin >> n >> k;
    for(int i = 0; i < k; ++i) {
        int y, x;
        cin >> y >> x;
        board[y-1][x-1] = 1;
    }
    cin >> l;
    for(int i = 0; i < l; ++i) {
        int x;
        char c;
        cin >> x >> c;
        cmd.push_back(make_pair(x, c));
    }
}

int turn(int d, char c) {
    int ret;
    if(c == 'L') {
        if(d == 0) ret = 3;
        else if(d == 1) ret = 2;
        else if(d == 2) ret = 0;
        else if(d == 3) ret = 1;
    }
    else if(c == 'D') {
        if(d == 0) ret = 2;
        else if(d == 1) ret = 3;
        else if(d == 2) ret = 1;
        else if(d == 3) ret = 0;
    }
    return ret;
}

void solution() {
    deque<pair<int, int> > snake;
    int y = 0, x = 0, d = 0;
    int time = 0, idx = 0;
    snake.push_back(make_pair(y, x));
    board[y][x] = 2;
    while(true) {
        time++;
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny < 0 || ny >= n || nx < 0 || nx >= n || board[ny][nx] == 2)
            break;
        else if(board[ny][nx] == 0) {
            board[ny][nx] = 2;
            board[snake.back().first][snake.back().second] = 0;
            snake.pop_back();
            snake.push_front(make_pair(ny, nx));
        } else if(board[ny][nx] == 1) {
            board[ny][nx] = 2;
            snake.push_front(make_pair(ny, nx));
        }
        if(idx < cmd.size() && time == cmd[idx].first) 
            d = turn(d, cmd[idx++].second);
        y = ny;
        x = nx;
    }
    cout << time << endl;
}

void solve() {
    input();
    solution();
}

int main(int argc, char** argv)
{
    solve();
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}