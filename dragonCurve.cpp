#include<iostream>
#include<queue>
using namespace std;
/* 
  백준 삼성 기출 - 드래곤 커브
  
  
  메모리 2060kb
  시간 0ms
  코드 길이 2122b
*/

int map[101][101]= {0,};
int N, M, S = 101;
int dirs[4][2] = {{0,1}, {-1, 0}, {0, -1}, {1,0}}; 

// 정사각형 개수 확인 
int isSquare(int x, int y){
    int cnt = 0;
    if(x+1<S){
        //printf("DD\n");
        if(y+1<S){ 
            if(map[x+1][y+1]) cnt++;
        } 
        if(map[x+1][y]) cnt++;
    }
    if(y+1<S){
        if(map[x][y+1]) cnt++;
    }
    if(cnt == 3) return 1;
    return 0;
}

void dragoncurve(int x, int y, int dir, int gen){
    int *arr = (int*)malloc(sizeof(int));
    arr[0] = dir;
    map[x][y] = 1;
    int size = 1, idx = 1; 
    while(gen-->0){ // 자녀 세대 수
        for(int i = size-1; i>=0; i--){
          // 다음 방향 
            int nx = x + dirs[arr[size-1]][0];
            int ny = y + dirs[arr[size-1]][1];
            //printf("[%d] size = %d (x,y) = (%d,%d) dir = %d (nx,ny) = (%d,%d) \n",i,size,x,y,arr[size-1], nx,ny);
            
            if (nx >= 0 && nx < S && ny >= 0 && ny < S){
                    map[nx][ny] = 1;
            }
            x = nx; y = ny; // new location
            realloc(arr,sizeof(int)*(++size));
            int ndir = arr[i] + 1;
            if(ndir > 3)
                ndir = 0;
            
            arr[idx++] = ndir;
           // printf("arr[%d] = %d => ndir = %d \n", i, arr[i],ndir);
        }
        
    }
    
    int nx = x + dirs[arr[size-1]][0];
    int ny = y + dirs[arr[size-1]][1];
   // printf("(x,y) = (%d,%d) (nx,ny) = (%d,%d) \n",x,y,nx,ny);
    if (nx >= 0 && nx < S && ny >= 0 && ny < S){ // 인덱스 범위 확인 
            map[nx][ny] = 1;
    }

   // printf("=====================\n");
}

int main () {
   // freopen("input.txt","r",stdin);
    int T;
    scanf("%d", &T);
    for(int t=0; t<T;t++){
        int x, y, dir, gen;
        scanf("%d %d %d %d", &y, &x, &dir, &gen);
        dragoncurve(x,y,dir,gen);
    }
    

    int count = 0;
    for(int i=0; i<S; i++){
        for(int j=0; j<S; j++){
            
            if(map[i][j] == 1) {
                //printf("(%d, %d)\n",i,j);
                count += isSquare(i,j);
                
            }
        }
        
    }
    printf("%d\n",count);
    return 0;
}
