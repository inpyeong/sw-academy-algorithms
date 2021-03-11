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
#include <cstring>

using namespace std;

const int MAX = 350, SIZE = 150;

struct Cell {
    // 좌표
    int y, x;
    // 비활성, 활성: true
    // 죽음: false
    bool state;
    // 태어난 시간
    int birthT;
    // 활성화되는 시간
    int activeT;
    // 죽는 시간
    int dieT;
    // 생명력
    int X;
};

int answer;
int n, m, k;
int grid[MAX][MAX];
vector<Cell> v;
int dy[] = { -1, 1,  0, 0 };
int dx[] = {  0, 0, -1, 1 };

bool cmp(Cell a, Cell b) {
    return a.X > b.X;
}

void initialize() {
    memset(grid, 0, sizeof(grid));
    v.clear();
    answer = 0;
}

void input() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            if(a == 0) continue;
            grid[i+SIZE][j+SIZE] = a;

            Cell tmp;
            tmp.y = i + SIZE;
            tmp.x = j + SIZE;
            tmp.X = a;
            tmp.state = true;
            tmp.birthT = 0;
            tmp.activeT = tmp.birthT + tmp.X;
            tmp.dieT = tmp.activeT + tmp.X;
            v.push_back(tmp);
        }
}

void doDie(int time) {
    for(int i = 0; i < v.size(); ++i)
        if(v[i].dieT == time)
            v[i].state = false;
}

void doActive(int time) {
    vector<Cell> tmp;
    for(int i = 0; i < v.size(); ++i) {
        if(v[i].state == false) continue;
        if(v[i].activeT == time) {
            int y = v[i].y;
            int x = v[i].x;
            int X = v[i].X;
            for(int j = 0; j < 4; ++j) {
                int ny = y + dy[j];
                int nx = x + dx[j];
                if(grid[ny][nx] != 0) continue;
                Cell c;
                c.y = ny;
                c.x = nx;
                c.X = X;
                c.state = true;
                c.birthT = time + 1;
                c.activeT = c.birthT + c.X;
                c.dieT = c.activeT + c.X;

                tmp.push_back(c);
            }
        }
    }
    if(tmp.size() == 0) return;
    sort(tmp.begin(), tmp.end(), cmp);
    for(int i = 0; i < tmp.size(); ++i) {
        int y = tmp[i].y;
        int x = tmp[i].x;
        if(grid[y][x] != 0) continue;
        grid[y][x] = tmp[i].X;
        v.push_back(tmp[i]);
    }
}

void solution() {
    int time = 0;
    while(true) {
        if(time == k) break;
        doDie(time);
        doActive(time);
        time++;
    }
    int deadCells = 0;
    for(int i = 0; i < v.size(); ++i) {
        if(v[i].state == false) deadCells++;
        if(v[i].dieT == time) deadCells++;
        if(v[i].birthT == time + 1) deadCells++;
    }
    answer = v.size() - deadCells;
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
        solve(test_case);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}