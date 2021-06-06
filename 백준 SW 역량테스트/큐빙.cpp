#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N;
vector<pair<char, char> > V;
vector<char> Cube[7];

void init() {
    V.clear();
    for(int i = 0; i < 7; ++i)
        Cube[i].clear();
}

void input() {
    cin >> N;
    string cmd;
    for(int i = 0; i < N; ++i) {
        cin >> cmd;
        char a = cmd[0], b = cmd[1];
        V.push_back(make_pair(a, b));
    }
    for(int i = 0; i < 9; ++i) {
        // 위
        Cube[1].push_back('w');
        // 아래
        Cube[2].push_back('y');
        // 앞
        Cube[3].push_back('r');
        // 뒤
        Cube[4].push_back('o');
        // 왼
        Cube[5].push_back('g');
        // 오른
        Cube[6].push_back('b');
    }
}

int selectPhase(char where) {
    if(where == 'U') return 1;
    else if(where == 'D') return 2;
    else if(where == 'F') return 3;
    else if(where == 'B') return 4;
    else if(where == 'L') return 5;
    else if(where == 'R') return 6;
}

void reSetting(char where, char dir) {
    int phase = selectPhase(where);
    if(dir == '+') {
        int tmp = Cube[phase].at(0);
        Cube[phase].at(0) = Cube[phase].at(6);
        Cube[phase].at(6) = Cube[phase].at(8);
        Cube[phase].at(8) = Cube[phase].at(2);
        Cube[phase].at(2) = tmp;

        int tmp2 = Cube[phase].at(1);
        Cube[phase].at(1) = Cube[phase].at(3);
        Cube[phase].at(3) = Cube[phase].at(7);
        Cube[phase].at(7) = Cube[phase].at(5);
        Cube[phase].at(5) = tmp2;
    }
    else if(dir == '-') {
        int tmp = Cube[phase].at(0);
        Cube[phase].at(0) = Cube[phase].at(2);
        Cube[phase].at(2) = Cube[phase].at(8);
        Cube[phase].at(8) = Cube[phase].at(6);
        Cube[phase].at(6) = tmp;

        int tmp2 = Cube[phase].at(1);
        Cube[phase].at(1) = Cube[phase].at(5);
        Cube[phase].at(5) = Cube[phase].at(7);
        Cube[phase].at(7) = Cube[phase].at(3);
        Cube[phase].at(3) = tmp2;
    }
}

void rotateCube(char where, char dir) {
    // 1 = 위 | 2 = 아래 | 3 = 앞 | 4 = 뒤 | 5 = 왼 | 6 = 오
    if(where == 'U') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[6].at(0);
            tmp2 = Cube[6].at(1);
            tmp3 = Cube[6].at(2);

            Cube[6].at(0) = Cube[4].at(0);
            Cube[6].at(1) = Cube[4].at(1);
            Cube[6].at(2) = Cube[4].at(2);

            Cube[4].at(0) = Cube[5].at(0);
            Cube[4].at(1) = Cube[5].at(1);
            Cube[4].at(2) = Cube[5].at(2);

            Cube[5].at(0) = Cube[3].at(0);
            Cube[5].at(1) = Cube[3].at(1);
            Cube[5].at(2) = Cube[3].at(2);

            Cube[3].at(0) = tmp;
            Cube[3].at(1) = tmp2;
            Cube[3].at(2) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[6].at(0);
            tmp2 = Cube[6].at(1);
            tmp3 = Cube[6].at(2);

            Cube[6].at(0) = Cube[3].at(0);
            Cube[6].at(1) = Cube[3].at(1);
            Cube[6].at(2) = Cube[3].at(2);

            Cube[3].at(0) = Cube[5].at(0);
            Cube[3].at(1) = Cube[5].at(1);
            Cube[3].at(2) = Cube[5].at(2);

            Cube[5].at(0) = Cube[4].at(0);
            Cube[5].at(1) = Cube[4].at(1);
            Cube[5].at(2) = Cube[4].at(2);

            Cube[4].at(0) = tmp;
            Cube[4].at(1) = tmp2;
            Cube[4].at(2) = tmp3;
        }
    }
    else if(where == 'D') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(6);
            tmp2 = Cube[3].at(7);
            tmp3 = Cube[3].at(8);

            Cube[3].at(6) = Cube[5].at(6);
            Cube[3].at(7) = Cube[5].at(7);
            Cube[3].at(8) = Cube[5].at(8);

            Cube[5].at(6) = Cube[4].at(6);
            Cube[5].at(7) = Cube[4].at(7);
            Cube[5].at(8) = Cube[4].at(8);

            Cube[4].at(6) = Cube[6].at(6);
            Cube[4].at(7) = Cube[6].at(7);
            Cube[4].at(8) = Cube[6].at(8);

            Cube[6].at(6) = tmp;
            Cube[6].at(7) = tmp2;
            Cube[6].at(8) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(6);
            tmp2 = Cube[3].at(7);
            tmp3 = Cube[3].at(8);

            Cube[3].at(6) = Cube[6].at(6);
            Cube[3].at(7) = Cube[6].at(7);
            Cube[3].at(8) = Cube[6].at(8);

            Cube[6].at(6) = Cube[4].at(6);
            Cube[6].at(7) = Cube[4].at(7);
            Cube[6].at(8) = Cube[4].at(8);

            Cube[4].at(6) = Cube[5].at(6);
            Cube[4].at(7) = Cube[5].at(7);
            Cube[4].at(8) = Cube[5].at(8);

            Cube[5].at(6) = tmp;
            Cube[5].at(7) = tmp2;
            Cube[5].at(8) = tmp3;
        }
    }
    else if(where == 'F') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[1].at(6);
            tmp2 = Cube[1].at(7);
            tmp3 = Cube[1].at(8);

            Cube[1].at(6) = Cube[5].at(8);
            Cube[1].at(7) = Cube[5].at(5);
            Cube[1].at(8) = Cube[5].at(2);

            Cube[5].at(8) = Cube[2].at(2);
            Cube[5].at(5) = Cube[2].at(1);
            Cube[5].at(2) = Cube[2].at(0);

            Cube[2].at(2) = Cube[6].at(0);
            Cube[2].at(1) = Cube[6].at(3);
            Cube[2].at(0) = Cube[6].at(6);

            Cube[6].at(0) = tmp;
            Cube[6].at(3) = tmp2;
            Cube[6].at(6) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[1].at(6);
            tmp2 = Cube[1].at(7);
            tmp3 = Cube[1].at(8);

            Cube[1].at(6) = Cube[6].at(0);
            Cube[1].at(7) = Cube[6].at(3);
            Cube[1].at(8) = Cube[6].at(6);

            Cube[6].at(0) = Cube[2].at(2);
            Cube[6].at(3) = Cube[2].at(1);
            Cube[6].at(6) = Cube[2].at(0);

            Cube[2].at(2) = Cube[5].at(8);
            Cube[2].at(1) = Cube[5].at(5);
            Cube[2].at(0) = Cube[5].at(2);

            Cube[5].at(8) = tmp;
            Cube[5].at(5) = tmp2;
            Cube[5].at(2) = tmp3;
        }
    }
    else if(where == 'B') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[1].at(0);
            tmp2 = Cube[1].at(1);
            tmp3 = Cube[1].at(2);

            Cube[1].at(0) = Cube[6].at(2);
            Cube[1].at(1) = Cube[6].at(5);
            Cube[1].at(2) = Cube[6].at(8);

            Cube[6].at(2) = Cube[2].at(8);
            Cube[6].at(5) = Cube[2].at(7);
            Cube[6].at(8) = Cube[2].at(6);

            Cube[2].at(8) = Cube[5].at(6);
            Cube[2].at(7) = Cube[5].at(3);
            Cube[2].at(6) = Cube[5].at(0);

            Cube[5].at(6) = tmp;
            Cube[5].at(3) = tmp2;
            Cube[5].at(0) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[1].at(0);
            tmp2 = Cube[1].at(1);
            tmp3 = Cube[1].at(2);

            Cube[1].at(0) = Cube[5].at(6);
            Cube[1].at(1) = Cube[5].at(3);
            Cube[1].at(2) = Cube[5].at(0);

            Cube[5].at(6) = Cube[2].at(8);
            Cube[5].at(3) = Cube[2].at(7);
            Cube[5].at(0) = Cube[2].at(6);

            Cube[2].at(8) = Cube[6].at(2);
            Cube[2].at(7) = Cube[6].at(5);
            Cube[2].at(6) = Cube[6].at(8);

            Cube[6].at(2) = tmp;
            Cube[6].at(5) = tmp2;
            Cube[6].at(8) = tmp3;
        }
    }
    else if(where == 'L') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(0);
            tmp2 = Cube[3].at(3);
            tmp3 = Cube[3].at(6);

            Cube[3].at(0) = Cube[1].at(0);
            Cube[3].at(3) = Cube[1].at(3);
            Cube[3].at(6) = Cube[1].at(6);

            Cube[1].at(0) = Cube[4].at(8);
            Cube[1].at(3) = Cube[4].at(5);
            Cube[1].at(6) = Cube[4].at(2);

            Cube[4].at(8) = Cube[2].at(0);
            Cube[4].at(5) = Cube[2].at(3);
            Cube[4].at(2) = Cube[2].at(6);

            Cube[2].at(0) = tmp;
            Cube[2].at(3) = tmp2;
            Cube[2].at(6) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(0);
            tmp2 = Cube[3].at(3);
            tmp3 = Cube[3].at(6);

            Cube[3].at(0) = Cube[2].at(0);
            Cube[3].at(3) = Cube[2].at(3);
            Cube[3].at(6) = Cube[2].at(6);

            Cube[2].at(0) = Cube[4].at(8);
            Cube[2].at(3) = Cube[4].at(5);
            Cube[2].at(6) = Cube[4].at(2);

            Cube[4].at(8) = Cube[1].at(0);
            Cube[4].at(5) = Cube[1].at(3);
            Cube[4].at(2) = Cube[1].at(6);

            Cube[1].at(0) = tmp;
            Cube[1].at(3) = tmp2;
            Cube[1].at(6) = tmp3;
        }
    }
    else if(where == 'R') {
        if(dir == '+') {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(2);
            tmp2 = Cube[3].at(5);
            tmp3 = Cube[3].at(8);

            Cube[3].at(2) = Cube[2].at(2);
            Cube[3].at(5) = Cube[2].at(5);
            Cube[3].at(8) = Cube[2].at(8);

            Cube[2].at(2) = Cube[4].at(6);
            Cube[2].at(5) = Cube[4].at(3);
            Cube[2].at(8) = Cube[4].at(0);

            Cube[4].at(6) = Cube[1].at(2);
            Cube[4].at(3) = Cube[1].at(5);
            Cube[4].at(0) = Cube[1].at(8);

            Cube[1].at(2) = tmp;
            Cube[1].at(5) = tmp2;
            Cube[1].at(8) = tmp3;
        }
        else {
            char tmp, tmp2, tmp3;
            tmp = Cube[3].at(2);
            tmp2 = Cube[3].at(5);
            tmp3 = Cube[3].at(8);

            Cube[3].at(2) = Cube[1].at(2);
            Cube[3].at(5) = Cube[1].at(5);
            Cube[3].at(8) = Cube[1].at(8);

            Cube[1].at(2) = Cube[4].at(6);
            Cube[1].at(5) = Cube[4].at(3);
            Cube[1].at(8) = Cube[4].at(0);

            Cube[4].at(6) = Cube[2].at(2);
            Cube[4].at(3) = Cube[2].at(5);
            Cube[4].at(0) = Cube[2].at(8);

            Cube[2].at(2) = tmp;
            Cube[2].at(5) = tmp2;
            Cube[2].at(8) = tmp3;
        }
    }
    reSetting(where, dir);
}

void solution() {
    for(int i = 0; i < V.size(); ++i) {
        char where = V[i].first;
        char dir = V[i].second;
        rotateCube(where, dir);
    }
}

void solve() {
	int tc;
	cin >> tc;
	for(int T = 1; T <= tc; ++T) {
        init();
        input();
        solution();

        int cnt = 1;
        for(int i = 0; i < 9; ++i) {
            cout << Cube[1].at(i);
            if(cnt == 3) {
                cout << endl;
                cnt = 0;
            }
            cnt++;
        }
	}
}

int main() {
    solve();
	return 0;
}