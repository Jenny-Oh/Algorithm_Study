// 위상정렬 사용
// 1. 진입 차수가 0인 정점들을 큐에 넣는다
// 2. 인접 정점들과의 연결을 끊고 진입 차수를 1씩 줄인다
// 3. 큐가 빌때까지 1,2를 반복한다


#include<stdio.h>

int level[1002][2]; //[0] : 진입차수 [1]: 진출차수
int link[1002][1002];


int main() {
	freopen("input.txt", "r", stdin);
	


	for (int t = 1; t <= 10; t++) {
		int N, edge;
		scanf("%d %d", &N, &edge);
		//printf("%d %d\n", N, edge);
		
	
		
		for (int i = 1; i <= N; i++) {
			//printf("%d\n", i);
			level[i][0] = 0; 
			level[i][1] = 0;
			for (int j = 1; j <= N; j++) {
				link[i][j] = 0;
			}
		}

		
		for (int e = 1; e <= edge; e++) {
			int V, E;
			scanf("%d %d", &V, &E);
			//printf(" %d => %d\n", V, E);
			link[V][E] = 1; // 링크 채우기 V->E
			level[E][0]++; //진입
			level[V][1]++; // 진출
		} 

		

		int queue[1000];
		int front = -1, rear = -1;
		int flag = 0;
		
		// Step 1 
		for (int i = 1; i <= N; i++) {
			if (level[i][0] == 0) { // 진입 차수 0 
				queue[++rear] = i;
				level[i][0] = -1; // 진입차수 -1로 바꾸기
			}
		}

		printf("#%d ", t);
		while (front < rear){
			// Step 2 
			int v = queue[++front];
			//printf("output => %d ", v);
			printf("%d ", v);
			for (int j = 1; j <= N; j++) {
				if (link[v][j] == 1) {
					link[v][j] = 1;
					level[j][0]--;
				}
			}
			// Step 1
			for (int i = 1; i <= N; i++) {
				if (level[i][0] == 0) {
					queue[++rear] = i;
					//printf("Insert => %d \n", i);
					level[i][0] = -1;
				}
			}

		}

		printf("\n");
	}// 10번 테스트 케이스 끝

	return 0;
}
