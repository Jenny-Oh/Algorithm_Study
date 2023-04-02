#include<iostream>
#include<limits.h>
using namespace std;

int N, L;
int map[100][100]; 
int result;
bool ladder[100];



/* 
    백준 삼성 기출 - 경사로

        하드코딩으로 풂. 시뮬레이션.
    
    메모리 2060kb
    시간 0ms
    코드길이 4296b


*/
int main (){

    freopen("input.txt", "r", stdin);
    cin >> N >> L;

    for(int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> map[i][j];
        }
        
    }
    result = 2*N; // 전체 가능한 길 개수 
    int pre, cur, cnt=0;
    int target, k;
    // 행 
    for(int i=0; i<N; i++){
        pre = map[i][0];
        for(int j=0; j<N; j++)
            ladder[j] = false;
        for(int j=1; j<N; j++){
            cur = map[i][j];
            cnt = 0;
            if (pre + 1 == cur){
                // 앞에 놓기
                target = pre; // 기준값 
                k = j-1; // 이전 인덱스
                if(ladder[k] == true){ result--; break;}
                ladder[k] = true;
                cnt = 1;
                
                //ladder[k] = true;
                while( --k>=0 && cnt < L){
                    if(map[i][k] == target && ladder[k] == false){
                         cnt++;
                         ladder[k] = true;
                    }
                    else break;
                }
                if (cnt != L){
                    result--;
                    break;
                }
                //cout << cnt << " => ";
                
            }
            if(cur + 1 == pre){
                // 지금부터 놓기
                target = cur;
                k = j; // 현 인덱스 
                if(ladder[k] == true){ result--; break;}
                ladder[k] = true;
                cnt = 1;
                //ladder[k] = true;
                cnt = 1;
                while (++k < N && cnt < L){
                    if(map[i][k] == target && ladder[k] == false){
                        cnt++;
                        ladder[k] = true;
                    }
                    else break;
                }
                if (cnt != L){
                    result--;
                    break;
                }

            }
            if (abs(pre-cur) > 1 ){ // 1이상 차이나서 불가능 길
                result--;
                break;
            }
            pre = cur;
            
        }
        //cout << "r = " << result << "\n";
    }
    //cout << result << "\n";
    // 열 
    for (int j=0; j<N; j++){
        pre = map[0][j];
        for (int i=0; i<N; i++){
            ladder[i] = false;
        }
        for(int i=1; i<N; i++){
            cur = map[i][j];
            cnt = 0;
            if (pre + 1 == cur){
                // 앞에 놓기
                target = pre; // 기준값 
                k = i-1; // 이전 인덱스
               
                if(ladder[k] == true){ result--; break;}
                ladder[k] = true;
                cnt = 1;
                
                //cout << "k = " << k << "\n";
                while( --k>=0 && cnt < L){
                    if(map[k][j] == target && ladder[k] == false){
                         cnt++;
                         ladder[k] = true;
                    }
                    else break;
                }
                if (cnt != L){
                    result--;
                    break;
                }

                
            }
            if(cur + 1 == pre){
                // 지금부터 놓기
                target = cur;
                k = i; // 현 인덱스 
                if(ladder[k] == true){ result--; break;}
                ladder[k] = true;
                cnt = 1;
                //cout << "k = " << k; 
                while (++k < N && cnt < L ){
                    if(map[k][j] == target && ladder[k] == false){
                        cnt++;
                        ladder[k] = true;
                    }
                    else break;
                }
                //cout << "cnt = " << cnt << " => "; 
                if (cnt != L){
                    result--;
                    break;
                }

            }
            if (abs(pre-cur) > 1 ){ // 1이상 차이나서 불가능 길
                result--;
                break;
            }
            pre = cur;
        }
        //cout << "r = " << result << "\n";
    }

    cout << result << "\n";
    return 0;
}