#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

int N, M;
int map[50][50];
struct chicken {
    int x, y;
    bool visited;
};


vector<chicken> c;
vector<pair<int,int>> house;
int cNum=0; // 치킨집 개수
int tmpIdx =0;
int minDist = INT_MAX;

// DFS - min Dist
void calDist(){
    int dist = 0;
    int hNum = house.size();
    
    for (int i=0; i<hNum; i++){
        int hminDist = INT_MAX;
        for(int j=0; j<cNum; j++){
            if(c[j].visited){ // 선택된 치킨집 중에서 
                int hDist = abs(house[i].first - c[j].x) + abs(house[i].second - c[j].y);
                if (hDist < hminDist)
                    hminDist = hDist;
            }
        }
        dist += hminDist;
    }   
    if (dist < minDist)
        minDist = dist;
    return;
}

// 최대 M개 치킨집 고르기
void chooseChicken(int m, int cidx){
    if(m == M){
        calDist();
        return;
    }
    for (int i= cidx; i<cNum;i++){
        if(!c[i].visited){
            c[i].visited = true;
            chooseChicken(m+1, i);
            c[i].visited = false;
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