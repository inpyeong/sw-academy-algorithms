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

const int mxN = 100;

int n, answer;
int board[mxN][mxN];
vector<pair<int, int> > src;
vector<pair<pair<int, int>, pair<int, int> > > wormHoles(5);
int srcY, srcX;

int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1};

void initialize() {
    answer = 0;
    src.clear();
    for(int i = 0; i < 5; ++i) {
        wormHoles[i].first.first = -1;
        wormHoles[i].first.second = -1;
        wormHoles[i].second.first = -1;
        wormHoles[i].second.second = -1;
    }
}

void input() {
    cin >> n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            cin >> board[i][j];
            // 빈 공간이면
            if(board[i][j] == 0)
                src.push_back(make_pair(i, j));
            // 웜홀이면
            else if(board[i][j] >= 6 && board[i][j] <= 10) {
                int idx = 10 - board[i][j];
                if(wormHoles[idx].first.first == -1) {
                    wormHoles[idx].first.first = i;
                    wormHoles[idx].first.second = j;
                } 
                else {
                    wormHoles[idx].second.first = i;
                    wormHoles[idx].second.second = j;
                }
            }
        }
}

void changeD(int b, int& d) {
    if(b == -1 || b == 5) {
        if(d == 0) d = 1;
        else if(d == 1) d = 0;
        else if(d == 2) d = 3;
        else if(d == 3) d = 2;
    }
    else {
        if(b == 1) {
            if(d == 0) d = 1;
            else if(d == 1) d = 3;
            else if(d == 2) d = 0;
            else if(d == 3) d = 2;
        }
        else if(b == 2) {
            if(d == 0) d = 3;
            else if(d == 1) d = 0;
            else if(d == 2) d = 1;
            else if(d == 3) d = 2;
        }
        else if(b == 3) {
            if(d == 0) d = 2;
            else if(d == 1) d = 0;
            else if(d == 2) d = 3;
            else if(d == 3) d = 1;
        }
        else if(b == 4) {
            if(d == 0) d = 1;
            else if(d == 1) d = 2;
            else if(d == 2) d = 3;
            else if(d == 3) d = 0;
        }
    }
}

void solution() {
    for(int i = 0; i < src.size(); ++i) {
        srcY = src[i].first;
        srcX = src[i].second;
        for(int j = 0; j < 4; ++j) {
            int y = srcY, x = srcX;
            int d = j;
            int ans = 0;
            while(true) {
                int ny = y + dy[d];
                int nx = x + dx[d];

                if(ny >= 0 && ny < n && nx >= 0 && nx < n) {
                    if(board[ny][nx] == -1 || (ny == srcY && nx == srcX)) break;
                    // 웜홀이라면
                    if(board[ny][nx] >= 6 && board[ny][nx] <= 10) {
                        int idx = 10 - board[ny][nx];
                        if(wormHoles[idx].first.first == ny && wormHoles[idx].first.second == nx) {
                            ny = wormHoles[idx].second.first;
                            nx = wormHoles[idx].second.second;
                        }
                        else {
                            ny = wormHoles[idx].first.first;
                            nx = wormHoles[idx].first.second;
                        }
                    }
                    // 블록이라면
                    else if(board[ny][nx] >= 1 && board[ny][nx] <= 5) {
                        ans++;
                        changeD(board[ny][nx], d);
                    }
                }
                // 벽이라면
                else {
                    ans++;
                    changeD(-1, d);
                }
                y = ny;
                x = nx;
            }
            answer = max(answer, ans);
        }
    }
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