#include<iostream>
#include<vector>
// 예약어 INT_MAX 를 사용할 수 있는 라이브러리 
#include<limits.h> 
using namespace std;


/* 
    백준 삼성기출 - 스타트와 링크
    시간 초과로 굉장히 애먹었는데 팀 나눌때 탐색 인덱스를 줄일 수 있는지 고민해보기 
    메모리 2024kb
    시간 132ms
    코드길이 1145b
*/
int N, mem; // N : 총 멤버수, mem = N/2 팀당 멤버수 
int sMap[20][20]; // 역량 맵
int totalS=0; // 사용 안함 
int ppl[20]; // 어느 팀인지 0, 1
int minDiff = INT_MAX; // 최소 차이
int startTeam[10]; // 사용 안함 
int linkTeam[10];  // 사용 안함


void chooseTeam(int idx, int cnt){
    if (cnt == mem){
        int start =0, link = 0; // 각 팀의 역량치 저장
        for (int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(ppl[i] == 1 && ppl[j] == 1) 
                    start += (sMap[i][j]);
                if( ppl[i] == 0 && ppl[j] == 0)
                    link += (sMap[i][j]);

            }

        }
        int diff = abs(start-link);
        if (minDiff > diff)
            minDiff = diff;
            
        return;
    }
    // 팀 나누기 : 한 배열에서 0이면 스타트팀, 1이면 링크팀 이렇게 나눴다
    // *** 주의 *** 탐색 시작 인덱스를 idx 부터 안하고 0부터 했더니 시간 초과 에러가 났었다 
    for (int i=idx; i<N; i++){
        if(ppl[i] == 0){
            ppl[i] = 1;
            chooseTeam(i,cnt+1);
            ppl[i] = 0;
        }
    }
    return;
}

int main (){
    freopen("input.txt", "r",stdin);
    cin >> N;
    mem = N/2;
    for(int i=0; i<N; i++){
        ppl[i] = 0;
        for (int j=0; j<N; j++){
           
            cin >> sMap[i][j];
           // totalS += S;
        }
    }
    chooseTeam(0,0);
    cout << minDiff;
    return 0;
}
