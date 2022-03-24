/* 
	DFS + 방문 개수 구하기 
*/

#include<stdio.h>
#include<stdlib.h>

int map[25][25];
int cnt; // 해당 단지내 집의 수 
int N; // 지도 크기
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} }; // 상하좌우 

int compare(const void* a, const void* b) {

	int num1 = *(int*)a;   
	int num2 = *(int*)b;    

	if (num1 < num2)    
		return -1;      

	if (num1 > num2)   
		return 1;       

	return 0;    
}

void findHouse(int x, int y) {
	
	map[x][y] = 0;
	for (int i = 0; i < 4; i++) {
		int next_x = x + dir[i][0];
		int next_y = y + dir[i][1];
		if (next_x < 0 || next_x >= N) continue;
		if (next_y >= 0 && next_y < N) {
			if (map[next_x][next_y]) {
				cnt++;
				
				findHouse(next_x, next_y);
			}
		}
	}


}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	
	char tmp[25];
	for (int i = 0; i < N; i++) {
		scanf("%s", tmp);
		for (int j = 0; j < N; j++) {
			map[i][j] = tmp[j] - '0';
			
		}
	}
	int danji = 0;
	int houses[100] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j]) {
				cnt = 1;
				findHouse(i, j);
				houses[danji++] = cnt;
			}
		}
	}
	
	
	qsort(houses, danji, sizeof(int), compare);
	printf("%d\n", danji);
	for (int i = 0; i < danji; i++)
		printf("%d\n", houses[i]);
}
