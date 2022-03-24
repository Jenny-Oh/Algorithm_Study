#include<stdio.h>

#define MAX 100

int maze[100][100];
int dest_x, dest_y;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} }; // 상하좌우 
int ans;

void DFS(int x, int y) {
	//printf(" x = %d y = %d \n",x,y);
	maze[x][y] = 1;
	if (x == dest_x && y == dest_y) {
		ans = 1;
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			int next_x = x + dir[i][0];
			int next_y = y + dir[i][1];
			
			if (next_x < 0 || next_x >= MAX)
				continue;
			if (next_y >= 0 && next_y < MAX) {
				//printf("next is %d %d \n", next_x, next_y);
				
				if (maze[next_x][next_y]!=1)
					DFS(next_x, next_y);
				
			}
		}
		//return;
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	int T = 10;
	

	while(T-->=1) {
		int test;
		scanf("%d ", &test);
		int start_x, start_y;
		//printf("test = %d \n", test);
		char s[101];
		// 미로 값 채우기
		for (int i = 0; i < MAX; i++) {
			scanf("%s", s);
			for (int j = 0; j < MAX; j++) {
				int tmp = s[j]-'0';
				//printf("%d", tmp);
				if (tmp > 1) {
					if (tmp == 2) {
						start_x = i; 
						start_y = j;
					}
					else {
						dest_x = i; 
						dest_y = j;
					}
					
				}
				maze[i][j] = tmp;
				
			}
			//printf("\n");
		}
		
		ans = 0; // 정답 초기화
		DFS(start_x, start_y);
		
		printf("#%d %d\n", test, ans);
	}
}