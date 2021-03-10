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
#include <cmath>
#include <algorithm>

using namespace std;

const int mxM = 100, mxA = 8;

struct BC {
    // 번호
    int n;
    // 위치(Location)
    int x, y;
    // 충전 범위(Coverage)
    int c;
    // 성능(Performance)
    int p;

    BC() {}
    BC(int _n, int _x, int _y, int _c, int _p): n(_n), x(_x), y(_y), c(_c), p(_p) {}
};

struct Person {
    int x, y;
    int sum;

    Person() {}
    Person(int _x, int _y, int _sum): x(_x), y(_y), sum(_sum) {}
};

int answer;
int m, a;

int moving[2][mxM+1];
BC bcs[mxA];
Person people[2];
vector<BC> v0, v1;
int dy[] = { 0, -1, 0, 1,  0 };
int dx[] = { 0,  0, 1, 0, -1 };

void initialize() {
    answer = 0;
    people[0] = Person(0, 0, 0);
    people[1] = Person(9, 9, 0);
    moving[0][0] = 0;
    moving[1][0] = 0;
}

void input() {
    cin >> m >> a;
    for(int i = 0; i < 2; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> moving[i][j];
    for(int i = 0; i < a; ++i) {
        int x, y, c, p;
        cin >> x >> y >> c >> p;
        bcs[i] = BC(i, x-1, y-1, c, p);
    }
}

int getDist(BC bc, Person person) {
    return (abs(bc.x - person.x) + abs(bc.y - person.y));
}

void letsGo(int dir0, int dir1) {
        people[0].x += dx[dir0];
        people[0].y += dy[dir0];
        people[1].x += dx[dir1];
        people[1].y += dy[dir1];
}

bool cmp(BC a, BC b) {
    return a.p > b.p;
}

void solution() {
    for(int i = 0; i <= m; ++i) {
        int dir0 = moving[0][i];
        int dir1 = moving[1][i];

        // 사람 이동
        letsGo(dir0, dir1);
        // 충전받을 수 있는 BC를 구한다.
        vector<BC> v0, v1;
        for(int j = 0; j < a; ++j) {
            if(getDist(bcs[j], people[0]) <= bcs[j].c)
                v0.push_back(bcs[j]);
            if(getDist(bcs[j], people[1]) <= bcs[j].c)
                v1.push_back(bcs[j]);
        }
        // 성능으로 내림차순 정렬
        sort(v0.begin(), v0.end(), cmp);
        sort(v1.begin(), v1.end(), cmp);
        // cout << i << " ";
        // if(v0.size()) cout << "첫 번째 " << v0[0].n << " ";
        // if(v1.size()) cout << "두 번째 " << v1[0].n << endl;
        // 어느 한쪽이라도 BC가 없으면..
        if(v0.size() == 0 && v1.size() == 0) 
            continue;
        else if(v0.size() == 0) {
            people[1].sum += v1[0].p;
            continue;
        }
        else if(v1.size() == 0) {
            people[0].sum += v0[0].p;
            continue;
        }
        // 각자 충전받을 수 있는 BC 중에서 최고의 성능을 가진
        // BC가 다른 경우 그냥 성능을 더해주면 된다.
        if(v0[0].n != v1[0].n) {
            people[0].sum += v0[0].p;
            people[1].sum += v1[0].p;
        }
        // 하지만 최고 성능을 가진 BC가 같다면
        else {
            // 만약 한 개의 BC만 갖고 있는 사람이 있다면
            if(v0.size() == 1 && v1.size() == 1) {
                people[0].sum += v0[0].p / 2;
                people[1].sum += v1[0].p / 2;
            }
            else if(v0.size() == 1) {
                people[0].sum += v0[0].p;
                people[1].sum += v1[1].p;
            }
            else if(v1.size() == 1) {
                people[0].sum += v0[1].p;
                people[1].sum += v1[0].p;
            }
            // 둘 다 여러 개의 BC를 가지고 있다면
            else {
                if(v0[1].p == v1[1].p) {
                    people[0].sum += v0[0].p;
                    people[1].sum += v1[1].p;
                }
                else {
                    if(v0[1].p > v1[1].p) {
                        people[0].sum += v0[1].p;
                        people[1].sum += v1[0].p;
                    }
                    else {
                        people[0].sum += v0[0].p;
                        people[1].sum += v1[1].p;
                    }
                }
            }
        }
    }
}

void solve(int tc) {
    initialize();
    input();
    solution();
    cout << "#" << tc << " " << people[0].sum + people[1].sum << endl;
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