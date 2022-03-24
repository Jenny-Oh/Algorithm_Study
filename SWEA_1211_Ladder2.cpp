#include<stdio.h>
#include<string.h>

#define MAX 100


int min, start;
int ladder[MAX][MAX];
int visit[MAX][MAX];
int dir[3][2] = {{1,0},{0,-1},{0,1} }; // ���¿� 
int cur; // ��� Ƚ��
int flag; //  ������ ��������

void DFS(int row, int col) {
	//printf("row = %d col = %d \n", row, col);
	visit[row][col] = 1;
	if (row == (MAX - 1)) { 
		flag = 1; //  ������ ����
		return;
	}
	else {
		
		// �¿� �켱 Ž��
		int next_x, next_y;
		for (int i = 2; i >= 0; i--) {
			next_x = row + dir[i][0];
			next_y = col + dir[i][1];
			if (next_x < 0 || next_x >= MAX) continue;
			if (next_y >= 0 && next_y < MAX) {
				if (!visit[next_x][next_y] && ladder[next_x][next_y]){
					break;
				}
			}
		}
		cur++; // ��� Ƚ�� 
		DFS(next_x, next_y);
	}

}


int main() {
	freopen("input.txt", "r", stdin);
	
	for (int t = 1; t <= 10; t++) {
		int test;
		char tmp[201];
		char c;
		scanf("%d ", &test);

		//printf("test %d\n",test);
		
		// �̷�ä���
		char buf;
		
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				scanf("%d", &test);
				ladder[i][j] = test;
			}
		}
			
		
		min = MAX*MAX; // �ּڰ� �ʱ�ȭ
		for (int j = 0; j < MAX; j++) {
			
			if (ladder[0][j]) {
				// visit �迭 �ʱ�ȭ
				for (int i = 0; i < MAX; i++)
					for (int j = 0; j < MAX; j++)
						visit[i][j] = 0;
				cur = 0; flag = 0; // �ʱ�ȭ
				DFS(0, j);
				
				//printf("flag = %d cur = %d min = %d \n", flag, cur, min);
				if (flag && cur < min) {
					min = cur;
					start = j;
				}
			}
		}
		printf("#%d %d\n", t, start);
	}
	

}