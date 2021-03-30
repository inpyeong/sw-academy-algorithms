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

using namespace std;

const int BOTTOM = 6;

struct Dice {
    int y, x;
    vector<int> sides = vector<int>(7, 0);
};

int dy[] = { 0, 0,  0, -1, 1 };
int dx[] = { 0, 1, -1,  0, 0 };

int opposite[7] = { 0, 6, 5, 4, 3, 2, 1 };

void rollTheDice(Dice& dice, int cmd) {
    int s1, s2, s3, s4, s5, s6;
    s1 = dice.sides[1], s2 = dice.sides[2], s3 = dice.sides[3];
    s4 = dice.sides[4], s5 = dice.sides[5], s6 = dice.sides[6];
    switch(cmd) {
        case 1:
            dice.sides[1] = s4;
            dice.sides[4] = s6;
            dice.sides[6] = s3;
            dice.sides[3] = s1;
            break;
        case 2:
            dice.sides[4] = s1;
            dice.sides[6] = s4;
            dice.sides[3] = s6;
            dice.sides[1] = s3;
            break;
        case 3:
            dice.sides[1] = s5;
            dice.sides[2] = s1;
            dice.sides[6] = s2;
            dice.sides[5] = s6;
            break;
        case 4:
            dice.sides[5] = s1;
            dice.sides[1] = s2;
            dice.sides[2] = s6;
            dice.sides[6] = s5;
            break;
    }
}

vector<int> solve(int n, int m, vector<vector<int> > board, int sy, int sx, vector<int> cmd) {
    vector<int> answer;
    Dice dice;
    dice.y = sy;
    dice.x = sx;
    for(int i = 0; i < cmd.size(); ++i) {
        int dny = dice.y + dy[cmd[i]];
        int dnx = dice.x + dx[cmd[i]];
        if(dny < 0 || dny >= n || dnx < 0 || dnx >= m) continue;
        dice.y = dny;
        dice.x = dnx;
        rollTheDice(dice, cmd[i]);
        if(board[dice.y][dice.x] == 0) {
            board[dice.y][dice.x] = dice.sides[BOTTOM];
        }
        else {
            dice.sides[BOTTOM] = board[dice.y][dice.x];
            board[dice.y][dice.x] = 0;
        }
        answer.push_back(dice.sides[opposite[BOTTOM]]);
    }
    return answer;
}

int main(int argc, char** argv)
{
    // freopen("input.txt", "r", stdin);
    int n, m, sy, sx, k;
    cin >> n >> m >> sy >> sx >> k;
    vector<vector<int> > board(n, vector<int>(m));
    vector<int> cmd(k);
    for(int i = 0; i < n; ++i) 
        for(int j = 0; j < m; ++j) 
            cin >> board[i][j];
    for(int i = 0; i < k; ++i)
        cin >> cmd[i];
    vector<int> answer = solve(n, m, board, sy, sx, cmd);
    for(int i = 0; i < answer.size(); ++i)
        cout << answer[i] << endl;
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}