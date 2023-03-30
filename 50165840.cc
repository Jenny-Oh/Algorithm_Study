#include<stdio.h>
#include<math.h>

int gears[4][8];
// N극은 0, S극은 1

int calScore(){
    int score = 0;
    for(int i=0; i<4; i++){
        if(gears[i][0]){  // S극일때
            score += pow(2,i);  // 2^i 승 점수 더하기
        }
    }
    return score;
}

void clockGear(int idx, int D){
    if (D == 1){ // clockwise
        int tmp = gears[idx][7];
        for (int i=7; i>0; i--){
            gears[idx][i] = gears[idx][i-1];
        }
        gears[idx][0] = tmp;
    }
    else if(D == -1){ // counterclockwise
        int tmp = gears[idx][0];
        for (int i=0; i<7; i++){
            gears[idx][i] = gears[idx][i+1];
        }
        gears[idx][7] = tmp;
    }
    /*
    for (int i=0; i<8; i++){
        printf("=> %d ", gears[idx][i]);
 
    }
    printf("\n");
    */
}

void moveGear(int N, int D){ 
    int clocks[4] = {0,};
    if(N == 0){ // 0 -> 1 -> 2 -> 3
        clocks[0] = D; // 현 방향 저장
        for (int i=1; i<4; i++){
            // 앞의 2번 & 뒤의 6번 
            if (gears[i-1][2] != gears[i][6]){
                clocks[i] = (-1)*clocks[i-1];
            }
        }
    }    
    else if(N== 3) { // 0 <- 1 <- 2 <- 3
        clocks[3] = D; // 현 방향 저장
        for(int i=2; i>=0; i--){
            if(gears[i+1][6] != gears[i][2])
                clocks[i] = (-1)*clocks[i+1];
        }
    }
    else{ // 1 이나 2 
        clocks[N] = D;
        // left 
        if (gears[N][6] != gears[N-1][2]){ 
            clocks[N-1] = (-1)*clocks[N];
        } 
        // right
        if (gears[N+1][6] != gears[N][2]){ 
            clocks[N+1] = (-1)*clocks[N];
        } 
        if(gears[0][2] != gears[1][6])
            clocks[0] = (-1)*clocks[1];
        if(gears[3][6] != gears[2][2])
            clocks[3] = (-1)*clocks[2];

    }
    for (int i=0; i<4; i++){
        //printf("clocks => %d \n", clocks[i]);
        clockGear(i,clocks[i]);
    }
}

int main() {
    //freopen("input2.txt", "r", stdin);
    for (int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            char c;
            scanf(" %c", &c);
            gears[i][j] = (c-'0');
            //printf("%c , %d // ", c, gears[i][j]);
        }
    }
    
    int T;
    scanf(" %d", &T);
    //printf("\nT = %d\n",T);
    for (int i=0; i<T; i++){
        int N, D;
        scanf("%d %d",&N, &D);
        //printf("N = %d D = %d\n",N,D);
        moveGear(N-1,D); // 톱니 번호 ( 0 ~ 3 )
    }
    printf("%d\n", calScore());
    return 0;
}