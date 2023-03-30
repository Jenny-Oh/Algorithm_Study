#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

/* 
    백준 삼성기출 - 치킨 배달
    치킨집과 집을 벡터로 따로 선언하여 관리 -> 탐색 시간 줄이기
    
    최대 M개 고르라고는 했지만 어쨋든 거리의 최소값을 구하는 것이 목적이므로 
    M개 치킨집 모두 고르고 거리를 계산했다
    
    
    
*/
int N, M;
int map[50][50];
struct chicken {
    int x, y;
    bool visited;
};


vector<chicken> c; // 치킨집 벡터
vector<pair<int,int>> house; // 집 벡터 
int cNum=0; // 치킨집 개수
int tmpIdx =0;
int minDist = INT_MAX;

// DFS로 최소거리 구하기 
void calDist(){
    int dist = 0;
    int hNum = house.size();
    
    // 선택된 치킨집들 중 집에서 가장 가까운 거리를 갖는 것으로 채택 
    for (int i=0; i<hNum; i++){
        int hminDist = INT_MAX; 
        for(int j=0; j<cNum; j++){
            if(c[j].visited){ // 선택된 치킨집 중에서 
                int hDist = abs(house[i].first - c[j].x) + abs(house[i].second - c[j].y);
                if (hDist < hminDist)
                    hminDist = hDist; // 집에서 가장 가까운 치킨집 기찾기
            }
        }
        dist += hminDist;
    }   
    if (dist < minDist)
        minDist = dist;
    return;
}

// 최대 M개 치킨집 고르기 -> DP 
void chooseChicken(int m, int cidx){
    if(m == M){
        calDist();
        return;
    }
    for (int i= cidx; i<cNum;i++){
        if(!c[i].visited){
            c[i].visited = true;
            chooseChicken(m+1, i);
            c[i].visited = false; // 방문 초기화함해줘야함
        }
    }
    
    return;
}
int main () {
    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            int tmp;
            cin >> tmp;
            //cout << tmp;
        
            if (tmp == 1) house.push_back({i,j});
            else if (tmp == 2) { 
                c.push_back({i,j,false});
            }
        }
    }
    cNum = c.size();
   // cout << cNum << " " << house.size() <<"\n";
    
    chooseChicken(0,0);
    cout << minDist;
    return 0;
}
