#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int MAX_N = 20;

struct Group {
    vector<pair<int, int> > normalBlocks;
    vector<pair<int, int> > rainbowBlocks;
};

int N, M, answer;
int Board[MAX_N][MAX_N];
vector<Group> groups;

queue<pair<int, int> > q;
bool discovered[MAX_N][MAX_N];
bool discoveredCopy[MAX_N][MAX_N];

int D[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
vector<vector<int> > v;

void input() {
    cin >> N >> M;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            cin >> Board[i][j];
}

bool cmp(pair<int, int>& a, pair<int, int>& b) {
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

void bfs(int srcY, int srcX, int color) {
    Group g;
    while(!q.empty()) q.pop();
    q.push(make_pair(srcY, srcX));
    discovered[srcY][srcX] = true;

    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if(Board[y][x] > 0) g.normalBlocks.push_back(make_pair(y, x));
        else g.rainbowBlocks.push_back(make_pair(y, x));
        for(int i = 0; i < 4; ++i) {
            int ny = y + D[i][0];
            int nx = x + D[i][1];
            if(ny >= 0 && nx >= 0 && ny < N && nx < N) {
                if(!discovered[ny][nx] && (Board[ny][nx] == color || Board[ny][nx] == 0)) {
                    discovered[ny][nx] = true;
                    q.push(make_pair(ny, nx));
                }
            }
        }
    }

    if(g.normalBlocks.size() + g.rainbowBlocks.size() < 2) return;

    sort(g.normalBlocks.begin(), g.normalBlocks.end(), cmp);
    groups.push_back(g);

    // rollback rainbow blocks' info in discovered
    for(int i = 0; i < g.rainbowBlocks.size(); ++i) {
      int y = g.rainbowBlocks[i].first;
      int x = g.rainbowBlocks[i].second;
      discovered[y][x] = false;
    }
}

bool cmp2(Group& a, Group& b) {
    if(a.normalBlocks.size() + a.rainbowBlocks.size() == b.normalBlocks.size() + b.rainbowBlocks.size()) {
        if(a.rainbowBlocks.size() == b.rainbowBlocks.size()) {
            if(a.normalBlocks.front().first == b.normalBlocks.front().first)
                return a.normalBlocks.front().second > b.normalBlocks.front().second;
            return a.normalBlocks.front().first > b.normalBlocks.front().first;
        }
        return a.rainbowBlocks.size() > b.rainbowBlocks.size();
    }
    return a.normalBlocks.size() + a.rainbowBlocks.size() > b.normalBlocks.size() + b.rainbowBlocks.size();
}

void getGroups() {
    memset(discovered, false, sizeof(discovered));
    groups.clear();
    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j) 
            if(Board[i][j] > 0 && !discovered[i][j]) bfs(i, j, Board[i][j]);
    sort(groups.begin(), groups.end(), cmp2);
}

void removeGroups() {
    for(int i = 0; i < groups.front().normalBlocks.size(); ++i) {
        int y = groups.front().normalBlocks[i].first;
        int x = groups.front().normalBlocks[i].second;
        Board[y][x] = -2;
    }
    for(int i = 0; i < groups.front().rainbowBlocks.size(); ++i) {
        int y = groups.front().rainbowBlocks[i].first;
        int x = groups.front().rainbowBlocks[i].second;
        Board[y][x] = -2;
    }
    int add = (groups.front().normalBlocks.size() + groups.front().rainbowBlocks.size()) * (groups.front().normalBlocks.size() + groups.front().rainbowBlocks.size());
    answer += add;
}

void applyGravity() {
    for(int i = 0; i < N; ++i) 
        for(int j = N-2; j >= 0; --j) {
            if(Board[j][i] == -2 || Board[j][i] == -1) continue;
            int under = j;
            while(true) {
                under++;
                if(under == N) break;
                if(Board[under][i] != -2) break;
            }
            under--;
            if(under == j) continue;
            Board[under][i] = Board[j][i];
            Board[j][i] = -2;
        }
}

void turnAntiClockwise() {
    v = vector<vector<int> >(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j) 
            v[i][j] = Board[j][N-i-1];
    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j) 
            Board[i][j] = v[i][j];
}

void solution() {
    while(true) {
        getGroups();
        if(groups.size() == 0) break;
        removeGroups();
        applyGravity();
        turnAntiClockwise();
        applyGravity();
    }
    cout << answer << endl;
}

void solve() {
    input();
    solution();
}

int main() {
    solve();
    return 0;
}
