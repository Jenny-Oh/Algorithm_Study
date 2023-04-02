#include<iostream>
#include<vector>

using namespace std;


/* 
    백준 삼성 기출 - 감시

    BFS ..?를 응용한 풀이 
    
    메모리 2028kb
    시간 44ms
    코드 길이 6417b

*/
int map[8][8], map2[8][8]; // map : 최초 맵, map2 : 가능한 감시영역 표시한 맵 
int result;
vector<pair<int,int>> cctv;
int N, M, Csize;


// 사각지대 세는 함수 
void cntBlank() {
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            //cout << map2[i][j] << " ";
            if(map2[i][j] == 0)
                cnt++;
        }
        //cout << "\n";
    }
    
    // 최솟값 찾기 
    if (result > cnt)
        result = cnt;
    return;
}


// (x,y) 위치 기준으로 상 or 하 or 좌 or 우 한 방향으로만 그림
void drawRoute(int x, int y, int dir){
    // 상하좌우 감시영역 모두 탐색 => map2에 그리기 
    // 0 상 1 우 2 하 3 좌 
    int nx = x;
    int ny = y;
    
    //int delX, delY;
    if (dir == 0){ // 상
        while(--nx>-1){
            if(map2[nx][ny]==6) 
                break;
            if(map2[nx][ny] == 0){
                map2[nx][ny] = 7;
            }
        }
        
    }
    else if (dir == 1){ // 우 
        while(++ny<M){
            if(map2[nx][ny]==6) 
                break;
            if(map2[nx][ny] == 0){
                map2[nx][ny] = 7;
            }
        }
        
    }
    else if (dir == 2){ // 하 
        while(++nx<N){
            if(map2[nx][ny]==6) 
                break;
            if(map2[nx][ny] == 0){
                map2[nx][ny] = 7;
            }
        }
    }
    else{ // 좌 
        while(--ny>-1){
            if(map2[nx][ny]==6) 
                break;
            if(map2[nx][ny] == 0){
                map2[nx][ny] = 7;
            }
        }
    }
    return;
}

void solution(int cnt){
    // cctv cnt개 선택 
    if(cnt > Csize) return;
    if(cnt == Csize ){
        cntBlank();
        return;
    }
    

    int x= cctv[cnt].first;
    int y= cctv[cnt].second;
    // cnt번째 cctv 타입 확인
    int type = map[x][y];

    // 현재까지의 맵 상태 => 지역 변수 map3에 복사해두기 
    int map3[8][8];    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            map3[i][j] = map2[i][j];
        }
    }
    
    if (type == 1){
        // 상 
        drawRoute(x,y,0); 
        solution(cnt+1); // next cctv
        // 초기화가 꼭 필요하다! 한 cctv에 여러 경우의 수가 있는 것이므로 
        // 지역변수로 복사해둔 2차원 배열이므로 따로 함수를 빼서는 X
        // 따로 하면 전역변수로 선언 -> 자꾸 바뀌게 됨.
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 우 
        drawRoute(x,y,1);
        solution(cnt+1);
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 하 
        drawRoute(x,y,2);
        solution(cnt+1);
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 좌 
        drawRoute(x,y,3);
        solution(cnt+1);
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }

    }
    else if (type == 2){
        // 좌우
        drawRoute(x,y,1); // 우 
        drawRoute(x,y,3); // 좌 
        solution(cnt+1);
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }

        // 상하
        drawRoute(x,y,0); // 상
        drawRoute(x,y,2); // 하
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        
    }
    else if(type == 3){
        // 상우
        drawRoute(x,y,0); // 상
        drawRoute(x,y,1); // 우
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 우하
        drawRoute(x,y,1); // 우
        drawRoute(x,y,2); // 하 
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 하좌
        drawRoute(x,y,2);
        drawRoute(x,y,3);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        // 좌상
        drawRoute(x,y,3);
        drawRoute(x,y,0);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }

    }
    else if (type == 4){

        drawRoute(x,y,0);
        drawRoute(x,y,1);
        drawRoute(x,y,2);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }

        drawRoute(x,y,1);
        drawRoute(x,y,2);
        drawRoute(x,y,3);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        drawRoute(x,y,2);
        drawRoute(x,y,3);
        drawRoute(x,y,0);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
        drawRoute(x,y,3);
        drawRoute(x,y,0);
        drawRoute(x,y,1);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
    }
    else if (type == 5){
        // 상하좌우
        drawRoute(x,y,0);
        drawRoute(x,y,1);
        drawRoute(x,y,2);
        drawRoute(x,y,3);
        solution(cnt+1);
        //returnMap();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map2[i][j] = map3[i][j];
            }   
        }
    }

    solution(++cnt);
    
}

int main(){
    freopen("input.txt", "r", stdin);

    cin >> N >> M;
    result = N*M;
    for(int i=0; i< N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
            if(map[i][j] > 0 && map[i][j] < 6) {
                pair<int,int> c = {i,j};
                cctv.push_back(c);
            }
            map2[i][j] = map[i][j];
        }
    }
    Csize = cctv.size();
    // 현재 설치한 cctv 개수를 파라미터로 넘김
    // 처음엔 0 
    solution(0);
   
    cout<< result;
    return 0;
}