#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int way = 4;

int N, K;

int dy[] = { 1, 0, -1,  0 };
int dx[] = { 0, 1,  0, -1 };
int answer;

void dfs(vector<vector<int> >& ground, vector<vector<bool> >& visited, int y, int x, int dist, bool cut) {
  visited[y][x] = true;
  answer = max(answer, dist);
  for(int i = 0; i < way; ++i) {
    int ny = y + dy[i];
    int nx = x + dx[i];
    if(ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx]) {
      if(ground[ny][nx] < ground[y][x])
        dfs(ground, visited, ny, nx, dist+1, cut);
      else {
        if(!cut) {
          ground[ny][nx] -= K;
          if(ground[ny][nx] < ground[y][x])
            dfs(ground, visited, ny, nx, dist+1, !cut);
          ground[ny][nx] += K; 
        }
      }
    }
  } 
  visited[y][x] = false;
}

void solve(int tc) {
  answer = 0;
  cin >> N >> K;
  vector<vector<int> > ground(N, vector<int>(N));
  vector<vector<bool> > visited(N, vector<bool>(N, false));
  int maxHeight = 0;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) {
      cin >> ground[i][j];
      maxHeight = max(maxHeight, ground[i][j]);
    }
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j) {
      if(ground[i][j] == maxHeight) {
        dfs(ground, visited, i, j, 1, false);
      }
    }
  cout << "#" << tc << " " << answer << "\n";
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);
	int test_case;
	int T;
	cin >> T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
    solve(test_case);
	}
	return 0;}
