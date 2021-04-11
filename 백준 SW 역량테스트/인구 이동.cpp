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
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

const int MAX_N = 50;

int n, l, r, countryIdx;
int countries[MAX_N][MAX_N];
int discovered[MAX_N][MAX_N];
vector<pair<int, int> > unions[MAX_N * MAX_N];
bool canMove;

int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1 };

void input() {
    cin >> n >> l >> r;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> countries[i][j];
}

void bfs(int srcY, int srcX) {
    queue<pair<int, int> > q;
    q.push(make_pair(srcY, srcX));
    discovered[srcY][srcX] = countryIdx;
    unions[countryIdx].push_back(make_pair(srcY, srcX));
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny < 0 || ny >= n || nx < 0 || nx >= n)
                continue;
            if(discovered[ny][nx] != -1)
                continue;
            int diff = abs(countries[y][x] - countries[ny][nx]);
            if(diff >= l && diff <= r) {
                unions[countryIdx].push_back(make_pair(ny, nx));
                discovered[ny][nx] = countryIdx;
                q.push(make_pair(ny, nx));
            }
        } 
    }
    if(unions[countryIdx].size() > 1)
        canMove = true;
}

void openBorder() {
    countryIdx = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(discovered[i][j] != -1)
                continue;
            bfs(i, j);
            countryIdx++;
        }
    }
}

void move() {
    for(int i = 0; i < countryIdx; ++i) {
        int sum = 0;
        for(int j = 0; j < unions[i].size(); ++j)
            sum += countries[unions[i][j].first][unions[i][j].second];
        int newPopulation = sum / unions[i].size();
        for(int j = 0; j < unions[i].size(); ++j)
            countries[unions[i][j].first][unions[i][j].second] = newPopulation;
    }
}

void init() {
    memset(discovered, -1, sizeof(discovered));
    for(int i = 0; i < 2500; ++i) 
        unions[i].clear();
}

void solution() {
    int answer = 0;
    while(true) {
        init();
        openBorder();
        if(canMove) {
            move();
            canMove = false;
            answer++;
        }
        else break;
    }
    cout << answer << endl;
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