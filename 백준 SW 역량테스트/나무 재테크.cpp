#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 11;

int n, m, k;
int land[MAX][MAX];
int A[MAX][MAX];
vector<int> trees[MAX][MAX];

int dx[] = { -1, -1, 0, 1, 1,  1,  0, -1 };
int dy[] = {  0,  1, 1, 1, 0, -1, -1, -1 };

void input() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            cin >> A[i][j];
            land[i][j] = 5;
        }
    for(int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        trees[x][y].push_back(z);
    }
}

void springAndSummer() {
    // 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
    // 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
    // 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(trees[i][j].size() == 0) continue;
            vector<int> v;
            int nutri = 0;
            sort(trees[i][j].begin(), trees[i][j].end());
            for(int k = 0; k < trees[i][j].size(); ++k) {
                int age = trees[i][j][k];
                if(land[i][j] >= age) {
                    land[i][j] -= age;
                    v.push_back(age + 1);
                }
                else nutri += (age / 2);
            }
            trees[i][j].clear();
            for(int k = 0; k < v.size(); ++k)
                trees[i][j].push_back(v[k]);
            land[i][j] += nutri;
        }
    }
}

void fall() {
    // 가을에는 나무가 번식한다.
    // 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            if(trees[i][j].size() == 0) continue;
            for(int k = 0; k < trees[i][j].size(); ++k) {
                int age = trees[i][j][k];
                if(age % 5 == 0) {
                    for(int l = 0; l < 8; ++l) {
                        int nx = i + dx[l];
                        int ny = j + dy[l];
                        if(nx >= 1 && nx <= n && ny >= 1 && ny <= n) 
                            trees[nx][ny].push_back(1);
                    }
                }
            }
        }
}

void winter() {
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) 
            land[i][j] += A[i][j];
}

int getNumOfAliveTrees() {
    int ret = 0;
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) 
            ret += trees[i][j].size();
    return ret;
}

void solution() {
    while(k--) {
        springAndSummer();
        fall();
        winter();
    }
    int answer = getNumOfAliveTrees();
    cout << answer << endl;
}

void solve() {
    input();
    solution();
}

int main(int argc, char** argv) {
    solve();
	return 0;
}