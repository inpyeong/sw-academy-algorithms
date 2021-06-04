#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 6, MAX_Q = 1000;

int N, Q, BoardSz;
vector<vector<int> > Board;
int L[MAX_Q];
vector<vector<int> > tmp;
vector<pair<int, int> > tmp2;
bool discovered[1 << MAX_N][1 << MAX_N];

vector<int> answer(2, 0);

int D[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};

void printBoard() {
    cout << "======" << endl;
    for(int i = 0; i < BoardSz; ++i) {
        for(int j = 0; j < BoardSz; ++j)
            cout << Board[i][j] << " ";
        cout << endl;
    }
}

void input() {
    cin >> N >> Q;
    BoardSz = (1 << N);
    Board = vector<vector<int> >(BoardSz, vector<int>(BoardSz, 0));
    for(int i = 0; i < BoardSz; ++i) 
        for(int j = 0; j < BoardSz; ++j) 
            cin >> Board[i][j];
    for(int i = 0; i < Q; ++i)
        cin >> L[i];
}

void turnBoardClockwise(int y, int x, int sz) {
    tmp = vector<vector<int> >(sz, vector<int>(sz, 0));
    for(int i = 0; i < sz; ++i) 
        for(int j = 0; j < sz; ++j) 
            tmp[i][j] = Board[y+sz-j-1][x+i];
    for(int i = y; i < y+sz; ++i)
        for(int j = x; j < x+sz; ++j)
            Board[i][j] = tmp[i-y][j-x];
}

void decreaseIce() {
    tmp2.clear();
    int cnt;
    for(int i = 0; i < BoardSz; ++i) {
        for(int j = 0; j < BoardSz; ++j) {
            cnt = 0;
            for(int k = 0; k < 4; ++k) {
                int ny = i + D[k][0];
                int nx = j + D[k][1];
                if(ny >= 0 && nx >= 0 && ny < BoardSz && nx < BoardSz) 
                    if(Board[ny][nx]) cnt++;
            }
            if(cnt < 3) tmp2.push_back(make_pair(i, j));
        }
    }
    for(int i = 0; i < tmp2.size(); ++i) {
        if(Board[tmp2[i].first][tmp2[i].second] > 0)
            Board[tmp2[i].first][tmp2[i].second]--;
    }
}

void doFireStorm(int newBoardSz) {
    for(int i = 0; i < BoardSz; i += newBoardSz) 
        for(int j = 0; j < BoardSz; j += newBoardSz) {
            turnBoardClockwise(i, j, newBoardSz);
        }
    decreaseIce();
}

int bfs(int srcY, int srcX) {
    int ret = 0;
    queue<pair<int, int> > q;

    q.push(make_pair(srcY, srcX));
    discovered[srcY][srcX] = true;
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        ret++;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int ny = y + D[i][0];
            int nx = x + D[i][1];
            if(ny >= 0 && nx >= 0 && ny < BoardSz && nx < BoardSz) {
                if(!discovered[ny][nx] && Board[ny][nx] > 0) {
                    discovered[ny][nx] = true;
                    q.push(make_pair(ny, nx));
                }
            }
        }
    }
    return ret;
}

void getAnswer() {
    for(int i = 0; i < BoardSz; ++i)
        for(int j = 0; j < BoardSz; ++j) {
            answer[0] += Board[i][j];
            if(Board[i][j] > 0)
                answer[1] = max(answer[1], bfs(i, j));
        }
}

void solution() {
    for(int i = 0; i < Q; ++i) {
        doFireStorm(1 << L[i]);
        // printBoard();
    }
    // printBoard();
    getAnswer();
}

void solve() {
    input();
    solution();
    cout << answer[0] << "\n" << answer[1];
}

int main() {
    solve();
    return 0;
}