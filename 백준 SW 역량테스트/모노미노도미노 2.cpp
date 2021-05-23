#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 10000;

struct Info {
    int type;
    int y, x;
};

int N, score;
Info Infos[MAX_N];
int Green[6][4];
int Blue[4][6];
bool fullLines[6];

void input() {
    cin >> N;
    for(int i = 0; i < N; ++i) {
        int t, y, x;
        cin >> t >> y >> x;
        Infos[i] = {t, y, x};
    }
}

void printBoard() {
    cout << "----------------------" << endl;
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 4; ++j) 
            cout << Green[i][j] << " ";
        cout << endl;
    }
    cout << "======================" << endl;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 6; ++j) 
            cout << Blue[i][j] << " ";
        cout << endl;
    }
    cout << "----------------------" << endl;
}

void checkFullLines() {
    // Green
    memset(fullLines, false, sizeof(fullLines));
    for(int i = 2; i < 6; ++i) {
        int j;
        for(j = 0; j < 4; ++j) 
            if(!Green[i][j]) break;
        if(j == 4) {
            fullLines[i] = true;
            score++;
        }
    }
    vector<vector<int> > greenCopy(6, vector<int>(4, 0));
    int greenRow = 5;
    for(int i = 5; i >= 0; --i) {
        if(!fullLines[i]) {
            for(int j = 0; j < 4; ++j) 
                greenCopy[greenRow][j] = Green[i][j];
            greenRow--;
        }
    }
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 4; ++j)
            Green[i][j] = greenCopy[i][j];
    // Blue
    memset(fullLines, false, sizeof(fullLines));
    for(int i = 2; i < 6; ++i) {
        int j;
        for(j = 0; j < 4; ++j) 
            if(!Blue[j][i]) break;
        if(j == 4) {
            fullLines[i] = true;
            score++;
        }
    }
    vector<vector<int> > blueCopy(4, vector<int>(6, 0));
    int blueCol = 5;
    for(int i = 5; i >= 0; --i) {
        if(!fullLines[i]) {
            for(int j = 0; j < 4; ++j) 
                blueCopy[j][blueCol] = Blue[j][i];
            blueCol--;
        }
    }
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 6; ++j)
            Blue[i][j] = blueCopy[i][j];
}

void checkSpecialLines() {
    // Green
    int cntG = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 4; ++j)
            if(Green[i][j]) {
                cntG++;
                break;
            }
    vector<vector<int> > greenCopy(6, vector<int>(4, 0));
    for(int i = 5; i >= 0; --i) 
        for(int j = 0; j < 4; ++j) {
            if((i-cntG) < 0) continue;
            greenCopy[i][j] = Green[i-cntG][j];
        }
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 4; ++j)
            Green[i][j] = greenCopy[i][j];
    // Blue
    int cntB = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 4; ++j)
            if(Blue[j][i]) {
                cntB++;
                break;
            }
    vector<vector<int> > blueCopy(4, vector<int>(6, 0));
    for(int i = 5; i >= 0; --i) 
        for(int j = 0; j < 4; ++j) {
            if((i-cntB) < 0) continue;
            blueCopy[j][i] = Blue[j][i-cntB];
        }
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 6; ++j)
            Blue[i][j] = blueCopy[i][j];
}

void moveBlocks(Info info) {
    int t = info.type, y = info.y, x = info.x;
    int posG = 5, posB = 5;
    if(t == 1) {
        // Green
        for(int i = 2; i < 6; ++i) 
            if(Green[i][x]) {
                posG = i-1;
                break;
            }
        Green[posG][x] = 1;
        // Blue
        for(int i = 2; i < 6; ++i) 
            if(Blue[y][i]) {
                posB = i-1;
                break;
            }
        Blue[y][posB] = 1;
        checkFullLines();
        checkSpecialLines();
    }
    else if(t == 2) {
        // Green
        for(int i = 2; i < 6; ++i) 
            if(Green[i][x] || Green[i][x+1]) {
                posG = i-1;
                break;
            }
        Green[posG][x] = 1;
        Green[posG][x+1] = 1;
        // Blue
        for(int i = 2; i < 6; ++i) 
            if(Blue[y][i]) {
                posB = i-1;
                break;
            }
        Blue[y][posB] = 1;
        Blue[y][posB-1] = 1;
        checkFullLines();
        checkSpecialLines();
    }
    else if(t == 3) {
        // Green
        for(int i = 2; i < 6; ++i)
            if(Green[i][x]) {
                posG = i-1;
                break;
            }
        Green[posG][x] = 1;
        Green[posG-1][x] = 1;
        // Blue
        for(int i = 2; i < 6; ++i) 
            if(Blue[y][i] || Blue[y+1][i]) {
                posB = i-1;
                break;
            }
        Blue[y][posB] = 1;
        Blue[y+1][posB] = 1;
        checkFullLines();
        checkSpecialLines();
    }
}

int getTotalBlocks() {
    int ret = 0;
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 4; ++j)
            if(Green[i][j]) ret++;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 6; ++j)
            if(Blue[i][j]) ret++;
    return ret;
}

void solution() {
    for(int i = 0; i < N; ++i) 
        moveBlocks(Infos[i]);
    // printBoard();
    cout << score << endl;
    cout << getTotalBlocks() << endl;
}

void solve() {
    input();
    solution();
}

int main() {
    solve();
    return 0;
}