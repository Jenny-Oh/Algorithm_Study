#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int N, mem;
int sMap[20][20];
int totalS=0;
int ppl[20];
int minDiff = INT_MAX;
int startTeam[10];
int linkTeam[10];


void chooseTeam(int idx, int cnt){
    if (cnt == mem){
        int start =0, link = 0;
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