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

const int MAX_N = 20;
int n, answer;
int board[MAX_N][MAX_N];
int _board[MAX_N][MAX_N];
int dirs[5];

void input() {
    cin >> n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> board[i][j];
}

void copyBoard() {
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            _board[i][j] = board[i][j];
}

void moveUp() {
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) 
            if(_board[j][i] != 0) {
                int k = j - 1;
                while(k >= 0) {
                    if(_board[k][i] == 0) {
                        _board[k][i] = _board[k+1][i];
                        _board[k+1][i] = 0;
                        k--;
                    }
                    else break;
                }
            }
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < n; ++j) {
            int k = j - 1;
            if(_board[k][i] && _board[k][i] == _board[j][i]) {
                _board[k][i] *= 2;
                _board[j][i] = 0;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) 
            if(_board[j][i] != 0) {
                int k = j - 1;
                while(k >= 0) {
                    if(_board[k][i] == 0) {
                        _board[k][i] = _board[k+1][i];
                        _board[k+1][i] = 0;
                        k--;
                    }
                    else break;
                }
            }
}

void moveDown() {
    for(int i = 0; i < n; ++i)
        for(int j = n-1; j >= 0; --j) 
            if(_board[j][i] != 0) {
                int k = j + 1;
                while(k < n) {
                    if(_board[k][i] == 0) {
                        _board[k][i] = _board[k-1][i];
                        _board[k-1][i] = 0;
                        k++;
                    }
                    else break;
                }
            }
    for(int i = 0; i < n; ++i) {
        for(int j = n-2; j >= 0; --j) {
            int k = j + 1;
            if(_board[k][i] && _board[k][i] == _board[j][i]) {
                _board[k][i] *= 2;
                _board[j][i] = 0;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = n-1; j >= 0; --j) 
            if(_board[j][i] != 0) {
                int k = j + 1;
                while(k < n) {
                    if(_board[k][i] == 0) {
                        _board[k][i] = _board[k-1][i];
                        _board[k-1][i] = 0;
                        k++;
                    }
                    else break;
                }
            }
}

void moveLeft() {
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) 
            if(_board[i][j] != 0) {
                int k = j - 1;
                while(k >= 0) {
                    if(_board[i][k] == 0) {
                        _board[i][k] = _board[i][k+1];
                        _board[i][k+1] = 0;
                        k--;
                    }
                    else break;
                }
            }
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < n; ++j) {
            int k = j - 1;
            if(_board[i][k] && _board[i][k] == _board[i][j]) {
                _board[i][k] *= 2;
                _board[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) 
            if(_board[i][j] != 0) {
                int k = j - 1;
                while(k >= 0) {
                    if(_board[i][k] == 0) {
                        _board[i][k] = _board[i][k+1];
                        _board[i][k+1] = 0;
                        k--;
                    }
                    else break;
                }
            }
}

void moveRight() {
    for(int i = 0; i < n; ++i)
        for(int j = n-1; j >= 0; --j) 
            if(_board[i][j] != 0) {
                int k = j + 1;
                while(k < n) {
                    if(_board[i][k] == 0) {
                        _board[i][k] = _board[i][k-1];
                        _board[i][k-1] = 0;
                        k++;
                    }
                    else break;
                }
            }
    for(int i = 0; i < n; ++i) {
        for(int j = n-2; j >= 0; --j) {
            int k = j + 1;
            if(_board[i][k] && _board[i][k] == _board[i][j]) {
                _board[i][k] *= 2;
                _board[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        for(int j = n-1; j >= 0; --j) 
            if(_board[i][j] != 0) {
                int k = j + 1;
                while(k < n) {
                    if(_board[i][k] == 0) {
                        _board[i][k] = _board[i][k-1];
                        _board[i][k-1] = 0;
                        k++;
                    }
                    else break;
                }
            }
}

int getMaxNum() {
    int ret = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) 
            if(_board[i][j] > ret)
                ret = _board[i][j];
    }    
    return ret;
}

void play() {
    for(int i = 0; i < 5; ++i) {
        int d = dirs[i];
        if(d == 0) moveUp();
        else if(d == 1) moveDown();
        else if(d == 2) moveLeft();
        else if(d == 3) moveRight();
    }
    answer = max(answer, getMaxNum());
}

void dfs(int cnt) {
    if(cnt == 5) {
        copyBoard();
        play();
        return;
    }
    for(int i = 0; i < 4; ++i) {
        dirs[cnt] = i;
        dfs(cnt+1);
    }
}

void printBoard() {
    cout << "--------------" << endl;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << _board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------" << endl;
}

void solution() {
    dfs(0);
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