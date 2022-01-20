#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 



double dist_sq(double x1, double y1, double x2, double y2) {
	
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void mergeSort(double* X ,unsigned* Xid, unsigned *TMP , unsigned start, unsigned end) {
	unsigned i,j,k,mid;
	if (start < end) { // ���� �ε��� < ������ �ε��� �϶�
		mid = (start + end) / 2; // �߰� ����
		
		mergeSort(X, Xid, TMP, start, mid); // ���� ����Ʈ conquer
		mergeSort(X, Xid, TMP, mid + 1, end); // ������ ����Ʈ conquer

		// �ε��� �� �ʱ�ȭ
		i = k = start, j = mid + 1; 
		//printf("\nmid = %u end = %u", mid, end);
		// �ε��� �迭�� ����
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
		// ���� ����Ʈ �ε��� �迭�� ����
		if (i > mid) { // �޺κ� ����Ʈ�� ����
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
			if (Y[Yid[cur_min]] > Y[Yid[j]]) // cur_min���� ���� �� ã��
				cur_min = j;
		}
		// ���� ���� ���� cur_min ������ ��ü�Ѵ�
		if (i != cur_min) { // ���ٸ� ���� �ٲ��ʿ䰡 ����
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

	// MERGE SORT ���
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

	// ��� ���� ������ THR ������ ���
	if (R - L + 1 <= THR) {
		
		// Xid[L:R]�� Yid[L:R]�� ����
		for (i = L; i <= R; i++)
			Yid[i] = Xid[i];
		// Yid[L:R] �� y���� ���� ������������ ���� => Selection Sort (O(n^2))
		selectionSort(Y, Yid, L, R);

		/* *************** dist �ʱ�ȭ �κп��� ����� �ʱ�ȭ ���� �ʾ� ������ ������ ************ */
		// dist �ʱ�ȭ : min ���� �ʱ�ȭ �ϱ� ���� ū ������ �ʱ�ȭ  
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
	else { // ��� ���� ������ THR���� ū ���
		
		M = (L + R) / 2;
		d_L = closestPairDC(L, M, &ptl1, &ptl2, X,Y,Xid, Yid, TMP , THR);
		d_R = closestPairDC(M+1, R, &ptr1, &ptr2, X, Y, Xid, Yid, TMP, THR);

		// merge => mergeSort ����� ����
		// Yid[L:M]�� Yid[M+1,R]
		// �ε��� �� �ʱ�ȭ
		i = k = L, j = M + 1;
		//printf("\nmid = %u end = %u", mid, end);
		// merge(Y, Yid, TMP, L, M, M + 1, R);	
		// void merge(double *Y, unsigned *Yid, unsigned *TMP, unsigned a1, unsigned b1, unsigned a2, unsigned b2) 
		// �ε��� �迭�� ����
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
		// ���� ����Ʈ �ε��� �迭�� ����
		if (i > M) { // �޺κ� ����Ʈ�� ����
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
		
		// dist min �ʱ�ȭ
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
		// �߰� ���� ������ index ����
		for (i = L; i <= R; i++) {
			target = X[Yid[i]];
			if (target >= x_mid - d_LR && target <= x_mid + d_LR) {
				TMP[k++] = Yid[i];
			}
		}
		//printf("#2 : TMP");
		unsigned tmp1, tmp2;
		double d_tmp = dist_min;
		// d_LR���� ���� pair Ž��
		for (i = 0; k != 0 && i < k - 1; i++) {
			for (j = i + 1; j < k; j++) {
				// TMP���� ���ؾ��Ѵ� 
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