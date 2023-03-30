#include <iostream>
#include <vector>
using namespace std;
int N; // 수의 개수
int rMax = -1000000001;
int rMin = 1000000001;
int numer[11];
int oper[4];

/* 
    백준 삼성 기출 - 연산자 끼워넣기
    
    연산자 순서가 다른 모든 경우의 수를 계산해야했기 때문에 dp로 탐색
    
    
    메모리 2020kb
    시간 0ms
    코드길이 1261b
   
*/

int solution(int result, int idx){
    if (idx == N){
        if(result > rMax){
            rMax = result;
        }
        if (result < rMin){
            rMin = result;
        }
        // 모든 연산자를 다 넣었기에 리턴
        return 0;
    }
    for(int i=0; i<4; i++){
        if(oper[i]>0){
            oper[i]--;
            if(i==0)
                solution(result + numer[idx], idx+1);
            else if(i==1)
                solution(result - numer[idx], idx+1);
            else if(i==2)
                solution(result * numer[idx], idx+1);
            else 
                solution(result / numer[idx], idx+1); 
            // 다시 살려야함
            oper[i]++;
        }
    }
    return 0;
}

int main (){
    freopen("input.txt", "r", stdin);
    cin >> N;
   
    int num;
    for (int i=0; i<N; i++){
        //cout << i;
        cin >> numer[i];
    }
    //cout << numer[0] << "\n"; 
    cin >> oper[0] >> oper[1] >> oper[2] >> oper[3];
    //cout << oper[3] << "\n hello \n"; 
    solution(numer[0],1);
    cout << rMax << "\n" << rMin;
    return 0;
}
