#include<iostream>

using namespace std;

const int MAX = 1000000;
int n, b, c;
int a[MAX];

void input() {
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> b >> c;
}

void solution() {
    long long answer = 0;
    for(int i = 0; i < n; ++i) {
        answer++;
        a[i] -= b;
        if(a[i] > 0) {
            answer += (a[i] / c);
            answer += (a[i] % c) ? 1 : 0;
        }
    }
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