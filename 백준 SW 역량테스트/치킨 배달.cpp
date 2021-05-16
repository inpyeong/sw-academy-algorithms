#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_N = 50, MAX_M = 13, INF = 987654321;

int N, M, answer = INF;
int Board[MAX_N][MAX_N];
vector<pair<int, int> > chickens;
vector<pair<int, int> > houses;
bool check[MAX_M];
int numOfChickens;

void input() {
    cin >> N >> M;
    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j) {
            cin >> Board[i][j];
            if(Board[i][j] == 1)
                houses.push_back(make_pair(i, j));
            else if(Board[i][j] == 2) {
                chickens.push_back(make_pair(i, j));
                numOfChickens++;
            }
        }
}

int getChickenDistance() {
    int ret = 0;
    for(int i = 0; i < houses.size(); ++i) {
        int dist = INF;
        for(int j = 0; j < numOfChickens; ++j) 
            if(check[j]) {
                int tmp = abs(chickens[j].first - houses[i].first) 
                        + abs(chickens[j].second - houses[i].second);
                dist = min(dist, tmp);
            }
        ret += dist;
    }
    return ret;
}

void selectChickens(int n, int idx, int cnt) {
    if(n == cnt) {
        answer = min(answer, getChickenDistance());        
        return;
    }
    for(int i = idx; i < numOfChickens; ++i) {
        if(!check[i]) {
            check[i] = true;
            selectChickens(n, i, cnt+1);
            check[i] = false;
        }
    }
}

void solution() {
    for(int i = 1; i <= M; ++i) 
        selectChickens(i, 0, 0);
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


	// }
    solve();
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}