#include<iostream>
#include<queue>
#include<vector>
using namespace std;
/*
    백준 삼성 기출 - 아기상어

    bfs 

    ** 상어 사이즈보다 작은 물고기라도 갈 수 없는 위치에 있는 것들 처리가 까다로웠음
    메모리 2028kb
    시간 4ms

*/
#define NMAX 20
int N;
int map[NMAX][NMAX]; // 원래 지도 
int time=0; // 전체 걸린 시간
int sharkX, sharkY, sharkSize =2;
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int visit[NMAX][NMAX] = {-1,}; // bfs 물고기 방문 여부
int distFish[NMAX][NMAX]; // 물고기 최소 거리 
queue<pair<int,int>> eatfish;
vector<pair<int,int>> smallfish;


int minDist(){
    // 상어와 물고기 사이의 최소 거리 구하기
    // 상어 위치 넣기 
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            visit[i][j] = -1;
            distFish[i][j] = -1;
        }
    }
    eatfish.push({sharkX,sharkY});
    visit[sharkX][sharkY] = 1;
    distFish[sharkX][sharkY] = 0;
    
    

    while(!eatfish.empty()){
        int l = eatfish.front().first;
        int r = eatfish.front().second;
        int t = distFish[l][r];
        eatfish.pop();
        for (int i=0; i<4; i++){
            int nx = l + dir[i][0];
            int ny = r + dir[i][1];

            if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if(map[nx][ny] > sharkSize) continue;
            
            else if(visit[nx][ny] < 0){
                eatfish.push({nx,ny});
                visit[nx][ny] = 1;
                distFish[nx][ny] = t+1;
            } 

        }

    }

    return 0;
}

void solution(){
    /* 먹을 수 있는 물고기 찾기 */
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j] < 1) continue;
            if(sharkSize > map[i][j]){
                smallfish.push_back({i,j});
                map[i][j] = 0; //  중복 선택 방지 
            }
        }
    }
    int eatenNum = 0;
    while(smallfish.size()>0){
        // 현 위치에서 가장 가까운 물고기 찾기
        //cout << "inital => " << sharkX << " , " << sharkY <<  "\n";
        minDist(); // bfs로 상어 위치로부터 모든 물고기 거리 계산 
        
        int dist = NMAX*NMAX;
        int target = 0;
        int flag = 1;
        // 후보 물고기 중 가장 가까운 물고기 찾기 
        for(int i=0; i<smallfish.size(); i++){
            
            int tmp = distFish[smallfish[i].first][smallfish[i].second];
            //cout << tmp << "\n";           
            if(tmp < 0) { // dist == -1 (도달할 수 없는 물고기의 위치 )
                flag = 0;
                continue;
            }
            
            if (dist > tmp){
                target = i;
                dist = tmp;
            }
            else if( dist == tmp){
                if(smallfish[i].first < smallfish[target].first){
                    target = i;
                }
                else if (smallfish[i].first == smallfish[target].first){
                    if(smallfish[i].second < smallfish[target].second){
                        target = i;
                    }
                }
            }
            flag = 1;
        }
        sharkX = smallfish[target].first; 
        sharkY = smallfish[target].second;
        // ** 더 이상 먹을 수 있는 물고기가 없음 **
        if(distFish[sharkX][sharkY] < 0) {
            return;
        }
       // cout << " dist  =  " << dist << "\n";
        /* 물고기 위치로 이동 */
        time += dist;
        eatenNum += 1;
        
        
        
        //cout << sharkX << " , " << sharkY << "=> " << map[sharkX][sharkY] << "\n";
        map[sharkX][sharkY] = 0;
       
        smallfish.erase(smallfish.begin() + target);

        
        /* 상어 크기 재정비 */
        if(eatenNum >= sharkSize){
            eatenNum -= sharkSize;
            sharkSize++;
            //cout << "size = " << sharkSize << "\n";
            
            /* 먹을 수 있는 물고기 찾기 */
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    if(map[i][j] < 1) continue;
                    if(sharkSize > map[i][j]){
                        smallfish.push_back({i,j});
                        map[i][j] = 0; //  중복 선택 방지 
                    }
                }
            }
        }

       
        //cout << "=====================\n";

    }

}




int main() {
    freopen("input.txt", "r", stdin);
    cin >> N;
    
    for(int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            int m;
            cin >> m;
            map[i][j] = m;
            if(m == 9){
                sharkX=i; sharkY=j;
                map[i][j] = 0;
            }
            
        }
    }

    
    solution();
    cout << time;
}
