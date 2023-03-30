#include<iostream>
#include<tuple>
#include<queue>

using namespace std;

/* 

  백준 삼성 기출 - 연구소3
  
  
  메모리 2052kb
  시간 16ms
  코드길이 3109b
  
*/


int mat[50][50],mat2[50][50], visit[50][50];
int N, V; // lab size, # of virus 
int dir[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}}; 
int virusTime;
int cannot = 1;
int blank = 0;


vector<pair<int, int>> chosen;
vector<pair<int,int>> virus;
int virusV[10]= {0,};

void bfs(){
    
    
    int v; // last visit depth
    int times;
    int left = blank; // 빈 개수 
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            visit[i][j] = -1; // 미방문 상태로 초기화 
    }
    
    queue<pair<int,int>> q; // 활성된 바이러스 위치를 새로운 큐에 넣는다 bfs용
    for(int i=0; i<10; i++){
        if(virusV[i]){
            //printf("%d ", i);
            int f = virus[i].first;
            int s = virus[i].second;
            q.push({f,s});
            visit[f][s] = 0; // 바이러스 위치 -> 시작시간으로 초기화 
        } 
    }
    //int s = chosen.size();
    //printf("-----------\n");
    while(!q.empty()){ // 활성 바이러스 끝날때까지 
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        int flag = 0;
        for (int i=0; i<4; i++){
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            v = visit[x][y]; // 감염되는데 걸리는 시간 
            if(nx >= N || nx < 0 || ny < 0 || ny >= N) continue;
            if(visit[nx][ny] >= 0 ) continue;
            if(!(mat[nx][ny] & 1)){ // mat[nx][ny] == 1일 때 빼고 다 , 즉 벽 빼고 다 
                if(mat[nx][ny] == 0) { // 빈 공간일 경우 
                    left--;
                    //visit[nx][ny] = v+1;
                }
                visit[nx][ny] = v+1; // 도달하는데 경과한 시간 
                q.push({nx,ny});
                times = visit[nx][ny]; // 마지막 인덱스까지 경과한 시간장저장
            }
        }
        if(left == 0) break; // 빈 개수가 없을때 
    }
    /*
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d ", visit[i][j]);
        }
        printf("\n");
    } */
    //printf("left = %d ----------times = %d vT = %d  -------------------\n",left,times,virusTime);
    
    if (left <= 0){
        cannot = 0;
        virusTime = min(times,virusTime); // 그 중 최솟값이 최소 시간 
       // printf("left = %d ----------times = %d vT = %d  -------------------\n",left,times,virusTime);
    }
   
    
    
}


void activateVir(int n, int depth)
{
    // 파라미터 설명
    // n 은 바이러스 현재 인덱스 , depth는 활성된 바이러스 개수 
    if (depth == V){   
        bfs();
        return;
    }
    else{
        // 바이러스 활성화 해야함
        int s = virus.size();
        for(int i=n; i<s; i++){
            if(!virusV[i]){ 
                virusV[i] = 1;
                activateVir(i+1,depth+1);
                virusV[i] = 0;
            }
        }
        
    }
}
int main () {
    //freopen("input2.txt","r",stdin);
    // 0 : 빈칸, 1: 벽, 2: 바이러스
    blank = 0; // 빈칸 세기
    scanf("%d", &N);
    scanf("%d", &V);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            int tmp;
            scanf("%d", &tmp);
            mat[i][j] = tmp;
            if(tmp== 0) blank++; // 빈칸 개수 세기
            if(tmp==2) virus.push_back({i,j}); // 바이러스 배열 
            visit[i][j] = -1;
        }
    }
    if(!blank) { // 처음부터 빈곳이 없다면 
        printf("0\n");
        return 0;
    }
    virusTime = N*N; // 최댓값 초기화
    
    activateVir(0,0);
    
    // 퍼뜨릴수 
    if(cannot) virusTime = -1;
    printf("%d\n",virusTime);
    return 0;
}
