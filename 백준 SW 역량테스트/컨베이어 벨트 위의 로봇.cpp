#include <iostream>
#include <queue>

using namespace std;

const int MAX = 220;

int N, K, Start, End, cnt, answer;
int belt[MAX];
bool visit[MAX];
queue<int> robot;

void input() {
	cin >> N >> K;
	for(int i = 1; i <= 2 * N; ++i)
		cin >> belt[i];
}

void moveBelt() {
	Start--;
	End--;
	if(Start < 1)
		Start = 2 * N;
	if(End < 1)
		End = 2 * N;
}

void moveRobot() {
	int size = robot.size();
	for(int i = 0; i < size; ++i) {
		int cur = robot.front();
		visit[cur] = false;
		robot.pop();

		if(cur == End)
			continue;

		int next = cur + 1;
		if(next > 2 * N)
			next = 1;
		if(belt[next] >= 1 && visit[next] == false) {
			belt[next]--;
			if(belt[next] == 0)
				cnt++;
			if(next == End)
				continue;
			visit[next] = true;
			robot.push(next);
		}
		else {
			visit[cur] = true;
			robot.push(cur);
		}
	}
}

void makeRobot() {
	if(visit[Start] == false && belt[Start] >= 1) {
		visit[Start] = true;
		belt[Start]--;
		robot.push(Start);
		if(belt[Start] == 0)
			cnt++;
	}
}

void solution() {
	Start = 1;
	End = N;
	while(cnt < K) {
		answer++;
		moveBelt();
		moveRobot();
		makeRobot();
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
