#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;


int map[102][102];
int route[102][102];
int N;
int dir[4][2] = {  {1, 0}, {0, 1} ,{0, -1}, {-1,0}}; // ÇÏ¿ìÁÂ»ó


queue<pair<int, int>> q;

int BFS() {
	q.push({ 1,1 });
	route[1][1] = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		//int r = route[x][y];
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];

			if (nx < 0 || ny< 0 || nx > N || ny > N)
				continue;
			
			if(route[nx][ny] > route[x][y] + map[nx][ny]){
				//visit[nx][ny] = 1;
				route[nx][ny] = route[x][y] + map[nx][ny];
				q.push({ nx, ny });
			}
				
			
		}

	}
	return route[N][N];
}


int main() {

	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);


	for (int t = 1; t <= T; t++) {
		char tmp[101];
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%s", tmp);
			for (int j = 1; j <= N; j++) {
				map[i][j] = tmp[j - 1] - '0';
				route[i][j] = 1000000;
				//printf("%d",map[i][j]);
				//visit[i][j] = 0;
			}
			//printf("\n");
		}

		int ans = BFS();
		printf("#%d %d\n", t, ans);
	}
	return 0;
}