#include <iostream>
#include <vector>
using namespace std;

/* 
    백준 삼성 기출 - 퇴사
    DP로 해결하여 풀었다.
    메모리 : 2020KB
    시간 : 0ms
    코드 길이 : 761B
*/
int N;
int pMax = -1;

struct session {
    int t; // 며칠걸리는지
    int p; // 얼마 받는지
};

vector<session> s;

void solution(int pSum, int day){
    if (day > N){
        //cout << pSum << "\n";
        if(pMax < pSum)
            pMax = pSum;
        return;
    }
    // 오늘 상담 한다
    if (day + s[day].t <= N+1)
        solution(pSum + s[day].p , day + s[day].t);
    // 안한다
    solution(pSum, day+1);
    return;
}

int main () {
    freopen("input.txt", "r", stdin);
    cin >> N;
    //cout << N;
    N-=1;
    //cout << N;
    int t,p;
    for (int i=0; i<=N; i++){
        cin >> t >> p;
        s.push_back({t,p});
    }
    //cout << s[0].t << s[0].p << "\n";
    solution(0,0);
    cout << pMax ;
}
