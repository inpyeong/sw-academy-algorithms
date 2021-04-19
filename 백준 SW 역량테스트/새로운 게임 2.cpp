#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 12, MAX_K = 10;

struct Pawn {
    int y, x;
    int d;
};

int n, k;
int m[MAX_N][MAX_N];
vector<int> ms[MAX_N][MAX_N];
Pawn pawn[MAX_K];

int dy[] = {0,0,0,-1,1};
int dx[] = {0,1,-1,0,0};

void input() {
    cin >> n >> k;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> m[i][j];
    for(int i = 0; i < k; ++i) {
        int y, x, d;
        cin >> y >> x >> d;
        y--, x--;
        pawn[i] = { y, x, d };
        ms[y][x].push_back(i);
    }
}

int findPos(int y, int x, int idx) {
    for(int i = 0; i < ms[y][x].size(); ++i)
        if(ms[y][x][i] == idx)
            return i;
}

int getDelNum(int y, int x, int pawnNum) {
    int ret = 0;
    for(int i = ms[y][x].size()-1; i >= 0; --i) {
        if(ms[y][x][i] == pawnNum) break;
        ret++;
    }
    return ret+1;
}

int getReverseDir(int idx) {
    int d = pawn[idx].d;
    if(d == 1) return 2;
    else if(d == 2) return 1;
    else if(d == 3) return 4;
    else if(d == 4) return 3;
}

void movePawn(int y, int x, int ny, int nx, int pawnNum, int pos, int state) {
    if(state == 0) {
        for(int i = pos; i < ms[y][x].size(); ++i) {
            ms[ny][nx].push_back(ms[y][x][i]);
            int idx = ms[y][x][i];
            pawn[idx].y = ny;
            pawn[idx].x = nx;
        }
        int delNum = getDelNum(y, x, pawnNum);
        for(int i = 0; i < delNum; ++i)
            ms[y][x].pop_back();
    }
    else if(state == 1) {
        for(int i = ms[y][x].size()-1; i >= pos; --i) {
            ms[ny][nx].push_back(ms[y][x][i]);
            int idx = ms[y][x][i];
            pawn[idx].y = ny;
            pawn[idx].x = nx;
        }
        int delNum = getDelNum(y, x, pawnNum);
        for(int i = 0; i < delNum; ++i)
            ms[y][x].pop_back();
    }
    else if(state == 2) {
        int nd = getReverseDir(pawnNum);
        pawn[pawnNum].d = nd;
        int nny = y + dy[nd];
        int nnx = x + dx[nd];
        if(nny >= 0 && nny < n && nnx >= 0 && nnx < n)
            if(m[nny][nnx] != 2) movePawn(y, x, nny, nnx, pawnNum, pos, m[nny][nnx]);
    }
}

bool isOver() {
    for(int i = 0; i < k; ++i) {
        int y = pawn[i].y;
        int x = pawn[i].x;
        if(ms[y][x].size() >= 4)
            return true;
    }
    return false;
}

void solution() {
    bool check = false;
    int turn = 0;
    while(true) {
        if(turn > 1000) break;
        for(int i = 0; i < k; ++i) {
            int d = pawn[i].d;
            int y = pawn[i].y, x = pawn[i].x;
            int ny = y + dy[d], nx = x + dx[d];
            int pos = findPos(y, x, i);
            if(ny >= 0 && ny < n && nx >= 0 && nx < n)
                movePawn(y, x, ny, nx, i, pos, m[ny][nx]);
            else
                movePawn(y, x, ny, nx, i, pos, 2);
            if(isOver()) {
                check = true;
                break;
            }
        }
        if(check) 
            break;
        turn++;
    }
    if(check)
        cout << turn + 1 << endl;
    else
        cout << -1 << endl;
}

void solve() {
    input();
    solution();
}

int main() {
    solve();
    return 0;
}