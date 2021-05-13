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

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 1+50, MAX_M = 100;

int n, m, answer;
int A[MAX_N][MAX_N];
bool check[MAX_N][MAX_N];
vector<pair<int, int> > info;
vector<pair<int, int> > clouds;

int dy[] = {0, 0,-1,-1,-1,0,1,1,1};
int dx[] = {0, -1,-1,0,1,1,1,0,-1};
int diagonal[4][2] = {{-1,-1},{-1,1},{1,1},{1,-1}};


void input() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) 
            cin >> A[i][j];
    for(int i = 0; i < m; ++i) {
        int d, s;
        cin >> d >> s;
        info.push_back(make_pair(d, s));
    }
    clouds.push_back(make_pair(n, 1));
    clouds.push_back(make_pair(n, 2));
    clouds.push_back(make_pair(n-1, 1));
    clouds.push_back(make_pair(n-1, 2));
}

void printA() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

void moveClouds(int t) {
    int d = info[t].first, s = info[t].second;
    for(int i = 0; i < clouds.size(); ++i) {
        int y = clouds[i].first;
        int x = clouds[i].second;
        
        s %= n;
        int ny = y;
        int nx = x;
        for(int j = 0; j < s; ++j) {
            ny += dy[d];
            nx += dx[d];

            if(ny == (n+1)) ny -= n;
            if(ny == 0) ny += n;
            if(nx == (n+1)) nx -= n;
            if(nx == 0) nx += n;
        }
        clouds[i].first = ny;
        clouds[i].second = nx;
    }
}

void makeItRain(int t) { 
    memset(check, false, sizeof(check));
    for(int i = 0; i < clouds.size(); ++i) {
        int y = clouds[i].first;
        int x = clouds[i].second;
        check[y][x] = true;
        A[y][x]++;
    }
    for(int i = 0; i < clouds.size(); ++i) {
        int y = clouds[i].first;
        int x = clouds[i].second;
        int cnt = 0;
        for(int j = 0; j < 4; ++j) {
            int ny = y + diagonal[j][0];
            int nx = x + diagonal[j][1];
            if(ny >= 1 && nx >= 1 && ny <= n && nx <= n) {
                if(A[ny][nx] > 0)
                    cnt++;
            }
        }
        A[y][x] += cnt;
    }
    clouds.clear();
}

void makeClouds() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(A[i][j] >= 2 && !check[i][j]) {
                clouds.push_back(make_pair(i, j));
                A[i][j] -= 2;
            }
        }
    }
}

void solution() {
    for(int time = 0; time < m; ++time) {
        moveClouds(time);
        makeItRain(time);
        makeClouds();
        // printA();
    }
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) 
            answer += A[i][j];
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
