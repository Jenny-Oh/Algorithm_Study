#include<iostream>
#include<queue>
using namespace std;
/* 
    연구소
    
    
    메모리 2024 kb
    시간 240 ms
    코드길이 2484b
*/
int N,M;
int matrix[8][8];
int mat2[8][8];
int maxSafety;
int dir[4][2] = {{1,0}, {-1,0}, {0,-1}, {0,1}};
queue<pair<int,int>> q;

void bfs(){
    // 큐에 바이러스 넣기 
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(matrix[i][j] == 2){
                q.push({i,j});
            }
        }
    }
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int d=0; d<4; d++){
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];
            if(nx < 0 || ny < 0 || nx >= N || ny >= M ) continue;
            if(mat2[nx][ny] == 1) continue;
            if(mat2[nx][ny] == 0 ){ // nothing
                mat2[nx][ny] = 2;
                q.push({nx,ny});
            }
            
        }
        
    }
    int cnt = 0;
    for (int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            //printf("%d ",mat2[i][j]);
            if(mat2[i][j] == 0)
                cnt++;

        }
        //printf("\n");
    }
    if(cnt > maxSafety) maxSafety = cnt;
    //printf("cnt = %d \n",cnt);
    return;
}

// 벽 2개 더 세우기
void setWalls(int walls){
    //printf("wall = %d \n", walls);
    if(walls == 3){
        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        for(int n=0; n<N; n++){
            for(int m=0; m<M; m++){
                mat2[n][m] = matrix[n][m];
                //printf("%d ", matrix[n][m]);
            }
            //printf("\n");
        }
        //printf("--------------------------\n");
        bfs();
        return;

    }
    else if(walls < 3){ 
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                //printf("%d ",mat2[i][j]);
                if(matrix[i][j] == 0){
                    matrix[i][j] = 1;
                    setWalls(walls+1);
                    matrix[i][j] = 0;
                }
            }
            //printf("\n");
        }
    }

}


int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d %d", &N, &M);
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            scanf("%d", &matrix[i][j]);
            
        }
    }
    maxSafety = 0;
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            if(matrix[i][j]  == 0){ 
            // 벽 하나 세움 -> setWalls로 두개 더 세우기 
                matrix[i][j] = 1;
                setWalls(1);
                matrix[i][j] = 0;
            }
        }
    }
    printf("%d\n",maxSafety);
    return 0;
}
