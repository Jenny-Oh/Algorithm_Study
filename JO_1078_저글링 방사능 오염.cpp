#include<stdio.h>

#define MAX 100

int map[MAX][MAX];
int time;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} }; // 상하좌우 
int N, M,cur ;
int flag = 0;





int BFS(int x, int y) {
	int queue_x[MAX * MAX];
	int queue_y[MAX * MAX];
	int q[MAX * MAX];

	
	int front=0, rear = 0;
	q[rear] = 0;
	queue_x[rear] = x;
	queue_y[rear++] = y;
	
	
	//printf("x %d y %d\n", x, y);
	int lev;
	while (front < rear) {
		lev = q[front];
		int cur_x = queue_x[front];
		int cur_y = queue_y[front++];
		
		map[cur_x][cur_y] = 0;
		//printf("x %d y %d\n", cur_x, cur_y);
		flag = 0;
		for (int i = 0; i < 4; i++) {
			int next_x = cur_x + dir[i][0];
			int next_y = cur_y + dir[i][1];
			if (next_x < 0 || next_x >= N) continue;
			if (next_y >= 0 && next_y < M) {
				if (map[next_x][next_y]) {
					flag = 1;
					//printf("next => x %d y %d\n", next_x, next_y);
					q[rear] = lev + 1;
					queue_x[rear] = next_x;
					queue_y[rear++] = next_y;
				}
			}
		}
		
		
		//printf("level %d\n", lev);
	}
	
	return lev;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d %d ", &M, &N);
	char tmp[101];
	for (int i = 0; i < N; i++) {
		scanf("%s", tmp);
		//printf("%s\n", tmp);
		for (int j = 0; j < M; j++)
			map[i][j] = tmp[j] - '0';
	}
	int x, y; // 방사능 노출 위치
	scanf("%d %d", &y, &x);
	time = 3; 
	// 첫번째부터 넣기때문에
	int level = BFS(x-1, y-1);
	
	
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j])
				cnt++;
		}
	}
	printf("%d\n%d\n", level + time ,cnt);
}