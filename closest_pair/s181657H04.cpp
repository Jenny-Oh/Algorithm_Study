#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 



double dist_sq(double x1, double y1, double x2, double y2) {
	
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void mergeSort(double* X ,unsigned* Xid, unsigned *TMP , unsigned start, unsigned end) {
	unsigned i,j,k,mid;
	if (start < end) { // 왼쪽 인덱스 < 오른쪽 인덱스 일때
		mid = (start + end) / 2; // 중간 지점
		
		mergeSort(X, Xid, TMP, start, mid); // 왼쪽 리스트 conquer
		mergeSort(X, Xid, TMP, mid + 1, end); // 오른쪽 리스트 conquer

		// 인덱스 값 초기화
		i = k = start, j = mid + 1; 
		//printf("\nmid = %u end = %u", mid, end);
		// 인덱스 배열에 저장
		while (i <= mid && j <= end) {
			if (X[Xid[i]] < X[Xid[j]]) {
				TMP[k++] = Xid[i++]; 
			}
			else {
				TMP[k++] = Xid[j++];
			}
		}
		unsigned l; 
		//printf("\ni %u , j : %u\n", i,j);
		// 남은 리스트 인덱스 배열에 저장
		if (i > mid) { // 뒷부분 리스트가 남음
			for (l = j; l <= end; l++) {
				TMP[k++] = Xid[l];
				
			}
		}
		else {
			for (l = i; l <= mid; l++) {
				//tmp = Xid[l];
				TMP[k++] = Xid[l];
				
			}
		}

		for (i = start; i <= end; i++)
			Xid[i] = TMP[i];

	}
}

void selectionSort(double*Y, unsigned* Yid, unsigned start, unsigned end) {
	unsigned i, j;
	unsigned cur_min , tmp;

	for (i = start; i <= end; i++) {
		cur_min = i;
		for (j = i + 1; j <= end; j++) {
			if (Y[Yid[cur_min]] > Y[Yid[j]]) // cur_min보다 작은 값 찾음
				cur_min = j;
		}
		// 현재 값을 구한 cur_min 값으로 대체한다
		if (i != cur_min) { // 같다면 굳이 바꿀필요가 없다
			tmp = Yid[i];
			Yid[i] = Yid[cur_min];
			Yid[cur_min] = tmp;
		}
	}
}

void   sortXid(double* X, unsigned* Xid, unsigned* TMP, unsigned N) {
	// input  : X[]   (x position array of N points)
	//          Xid[] (index array of X (initially [0,1,...,N-1])
	//          TMP[] (temporary array of size N. may or may not be used)
	//          N   number of points to sort
	// output : Xid[] (sorted indices by x position in X[])

	// MERGE SORT 사용
	unsigned start, end;
	start = 0; end = (N-1);
	
	

	mergeSort(X, Xid,TMP, start, end);
	

}
double closestPairDC(
	unsigned L, unsigned R,	  // current leftmost and rightmost indices
	unsigned* pt1, unsigned* pt2, // closest pair points indices
	double* X, double* Y,         // (x,y) positions array(input)
	unsigned* Xid,  // point index array(sorted by x coordinates)
	unsigned* Yid,  // point index array(gradually sorted by y coordinates)
	unsigned* TMP,  // temporal index array
	unsigned THR	// threshold value
) {
	unsigned i, j, k, M;
	unsigned ptl1, ptr1;
	unsigned ptl2, ptr2;
	double dist_min, dist, d_L, d_R, d_LR ;

	// 대상 점의 개수가 THR 이하인 경우
	if (R - L + 1 <= THR) {
		
		// Xid[L:R]을 Yid[L:R]로 복사
		for (i = L; i <= R; i++)
			Yid[i] = Xid[i];
		// Yid[L:R] 를 y값에 의해 오름차순으로 정렬 => Selection Sort (O(n^2))
		selectionSort(Y, Yid, L, R);

		/* *************** dist 초기화 부분에서 제대로 초기화 되지 않아 에러가 났었다 ************ */
		// dist 초기화 : min 값을 초기화 하기 위해 큰 값으로 초기화  
		dist_min = dist_sq(X[Yid[0]], Y[Yid[0]], X[Yid[1]], Y[Yid[1]]); 
		//printf("dist min ================== %lf\n", dist_min);
		//printf("#1 : Bruteforce");
		// Brute Force 
		for (i = L; i <= R - 1; i++) {
			for (j = i + 1; j <= R; j++) {
				if ((Y[Yid[j]] - Y[Yid[i]])>= dist_min) break;

				dist = dist_sq(X[Yid[i]], Y[Yid[i]], X[Yid[j]], Y[Yid[j]]);
				if (dist < dist_min) {
					*pt1 = Yid[i]; 
					*pt2 = Yid[j];
					dist_min = dist;
				}
			}
		}
	}
	else { // 대상 점의 개수가 THR보다 큰 경우
		
		M = (L + R) / 2;
		d_L = closestPairDC(L, M, &ptl1, &ptl2, X,Y,Xid, Yid, TMP , THR);
		d_R = closestPairDC(M+1, R, &ptr1, &ptr2, X, Y, Xid, Yid, TMP, THR);

		// merge => mergeSort 내용과 유사
		// Yid[L:M]와 Yid[M+1,R]
		// 인덱스 값 초기화
		i = k = L, j = M + 1;
		//printf("\nmid = %u end = %u", mid, end);
		// merge(Y, Yid, TMP, L, M, M + 1, R);	
		// void merge(double *Y, unsigned *Yid, unsigned *TMP, unsigned a1, unsigned b1, unsigned a2, unsigned b2) 
		// 인덱스 배열에 저장
		while (i <= M && j <= R) {
			if (Y[Yid[i]] < Y[Yid[j]]) {
				TMP[k++] = Yid[i++];
			}
			else {
				TMP[k++] = Yid[j++];
			}
		}
		unsigned l;
		//printf("\ni %u , j : %u\n", i,j);
		// 남은 리스트 인덱스 배열에 저장
		if (i > M) { // 뒷부분 리스트가 남음
			for (l = j; l <= R; l++) {
				TMP[k++] = Yid[l];

			}
		}
		else {
			for (l = i; l <= M; l++) {
				//tmp = Xid[l];
				TMP[k++] = Yid[l];

			}
		}

		for (i = L; i <= R; i++)
			Yid[i] = TMP[i];
		
		// dist min 초기화
		if (d_L < d_R) {
			*pt1 = ptl1;
			*pt2 = ptl2;
			d_LR = d_L;
		}
		else {
			*pt1 = ptr1;
			*pt2 = ptr2;
			d_LR = d_R;
		}


		// combine
		double x_mid = (X[Xid[M]] + X[Xid[M + 1]]) * 0.5;
		double target = 0.0;
		dist_min = d_LR;
		k = 0;
		// 중간 영역 점들의 index 복사
		for (i = L; i <= R; i++) {
			target = X[Yid[i]];
			if (target >= x_mid - d_LR && target <= x_mid + d_LR) {
				TMP[k++] = Yid[i];
			}
		}
		//printf("#2 : TMP");
		unsigned tmp1, tmp2;
		double d_tmp = dist_min;
		// d_LR보다 작은 pair 탐색
		for (i = 0; k != 0 && i < k - 1; i++) {
			for (j = i + 1; j < k; j++) {
				// TMP에서 비교해야한다 
				if ((Y[TMP[j]] - Y[TMP[i]]) >= d_tmp) break;

				dist = dist_sq(X[TMP[i]], Y[TMP[i]], X[TMP[j]], Y[TMP[j]]);
				if (dist < dist_min) {
					tmp1 = TMP[i]; 
					tmp2 = TMP[j];
					d_tmp = dist;
				}
			}
		}
		
		if (d_tmp < dist_min) {
			*pt1 = tmp1;
			*pt2 = tmp2;
			dist_min = d_tmp;
		}
		
	}

	return dist_min;

}