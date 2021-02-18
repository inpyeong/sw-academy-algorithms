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

int n, m, r, c, l;
int dy[] = { 1, 0, -1,  0 };
int dx[] = { 0, 1,  0, -1 };

void solve(int tc) {
  cin >> n >> m >> r >> c >> l;
  vector<vector<int> > tunnel(n, vector<int>(m));
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j)
      cin >> tunnel[i][j];
  
  int answer = 0;
  vector<vector<int> > discovered(n, vector<int>(m, 0));
  queue<pair<int, int> > q;

  discovered[r][c] = 1;
  q.push(make_pair(r, c));
  while(!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int type = tunnel[y][x];
    q.pop();
    switch(type) {
      case 1:
        for(int i = 0; i < 4; ++i) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 0 && (ntype == 3 || ntype == 5 || ntype == 6))
            continue;
          if(i == 1 && (ntype == 2 || ntype == 4 || ntype == 5))
            continue;
          if(i == 2 && (ntype == 3 || ntype == 4 || ntype == 7))
            continue;
          if(i == 3 && (ntype == 2 || ntype == 6 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 2:
        for(int i = 0; i < 4; i+=2) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 0 && (ntype == 3 || ntype == 5 || ntype == 6))
            continue;
          if(i == 2 && (ntype == 3 || ntype == 4 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 3:
        for(int i = 1; i < 4; i+=2) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 1 && (ntype == 2 || ntype == 4 || ntype == 5))
            continue;
          if(i == 3 && (ntype == 2 || ntype == 6 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 4:
        for(int i = 1; i < 3; ++i) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 1 && (ntype == 2 || ntype == 4 || ntype == 5))
            continue;
          if(i == 2 && (ntype == 3 || ntype == 4 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 5:
        for(int i = 0; i < 2; ++i) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 0 && (ntype == 3 || ntype == 5 || ntype == 6))
            continue;
          if(i == 1 && (ntype == 2 || ntype == 4 || ntype == 5))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 6:
        for(int i = 0; i < 4; i+=3) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 0 && (ntype == 3 || ntype == 5 || ntype == 6))
            continue;
          if(i == 3 && (ntype == 2 || ntype == 6 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
      case 7:
        for(int i = 2; i < 4; i++) {
          int ny = y + dy[i];
          int nx = x + dx[i];
          if(ny < 0 || ny >= n || nx < 0 || nx >= m || discovered[ny][nx])
            continue;
          int ntype = tunnel[ny][nx];
          if(ntype == 0) continue;
          if(i == 2 && (ntype == 3 || ntype == 4 || ntype == 7))
            continue;
          if(i == 3 && (ntype == 2 || ntype == 6 || ntype == 7))
            continue;
          discovered[ny][nx] = discovered[y][x] + 1;
          q.push(make_pair(ny, nx));
        }
        break;
    }
  }
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j) {
      if(discovered[i][j] > 0 && discovered[i][j] <= l) 
        answer++;
    }
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
