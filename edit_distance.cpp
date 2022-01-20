#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int minimum(int a, int b, int c) { // 3개의 정수 중 최솟값 구하기
	int tmp = a < b ? a : b;
	return tmp < c ? tmp : c;
}



void Edit_Distance(
	// inputs
	char* SS,		// Source string array
	char* TS,		// Edited string array
	int ins_cost, int del_cost, int sub_cost,
	// insertion, deletion, substitution cost
// outputs
int** Table,    // Cost Table Calculated (2-d array (|SS|+1) x (|TS|+1) will be set)
char** SR,		// Source string with insertion to T marks '*'
char** OP,		// Operation sequence('i', 'd', 's', or '.' (nop))
char** TR,       // Edited string with deletion form S mark '*'
				// NOTE: ST, OP, TR must be allocated inside the function as needed(minimum as possible)
	int* Mem_Allocated
) {

	int i, j, min;
	int ssize = strlen(SS) +1; // SS 길이 + 1 => Table row
	int tsize = strlen(TS) +1; // TS 길이 + 1 => Table column
	
	// Table 메모리는 main에서 이미 할당됨.
	// Table cost 초기화
	Table[0][0] = 0;
	for (j = 1; j < tsize; j++) { // TS 입장에서는 문자를 넣어야하므로 
		Table[0][j] = Table[0][j-1] + ins_cost;
	}
	for (i = 1; i < ssize; i++) { // SS 입장에서는 문자를 빼야하므로
		Table[i][0] = Table[i - 1][0] + del_cost;
	}

	

	// Table cost 계산
	for (i = 1; i < ssize; i++) {
		for (j = 1; j < tsize; j++) {
			if (SS[i - 1] == TS[j - 1]) // 해당 문자가 동일할때
				Table[i][j] = Table[i - 1][j - 1]; // 대각선의 cost와 동일
			else { // 다르다면 왼쪽, 왼쪽 위(대각선), 위쪽 중에 최솟값 찾기
				min = minimum(Table[i - 1][j - 1] + sub_cost, Table[i][j - 1] + ins_cost, Table[i - 1][j]+del_cost);
				Table[i][j] = min;
			}
		}
	}

	// 역추적을 통해  S , T, OP 길이 구하기
	int op_len = 0;
	// 맨 오른쪽 아래의 인덱스부터 추적시작
	i = ssize - 1; j = tsize - 1;
	
	
	int current = 0; // 현재 Table 값 저장하는 변수
	int sub, del, ins; // 셋 중에 어떤 작업을 수행해야하는지 알려주는 플래그 

	while (true) {
		current = Table[i][j];
		sub = del = ins = -1;
		if (i >= 1) {
			if (current == Table[i - 1][j] + del_cost) { // deletion
				del = 1;
			}
		}
		if (j >= 1) {
			if (current == Table[i][j - 1] + ins_cost) { // insertion
				ins = 1;
			}
		}
		if (i >= 1 && j >= 1) {
			// substitution & 그대로 => operation 길이를 세는 데 구분할 필요 없다
			if (current == Table[i - 1][j - 1] + sub_cost || SS[i - 1] == TS[j - 1]) { 
				sub = 1;
			}
		}

		if (del == 1 && ins == 1) { // compare del and ins
			if (del_cost < ins_cost) {
				del = 1; ins = 0;
			}
			else {
				ins = 1; del = 0;
			}
			
		}
			
		if (del == 1) { // deletion
			i -= 1;
		}
		else if (ins == 1) { // insertion
			j -= 1;
		}
		else { // substitution & 그대로 
			i -= 1; j -= 1;
		}
			
	
		op_len++;
		if (i <= 0 && j <= 0) break; // 더이상 비교할수 있는 인덱스가 없다
	
	}

	

	
	

	// 역추적을 통해 i , d, s 작성

	// 구한 길이 만큼 output string 길이 malloc
	op_len += 1;
	(*SR) = (char*)malloc(sizeof(char) * op_len);
	(*OP) = (char*)malloc(sizeof(char) * op_len);
	(*TR) = (char*)malloc(sizeof(char) * op_len);

	// allocation 한 SR, OP, TR 크기 합
	*Mem_Allocated = sizeof(char) * (op_len) * 3;

	// 문자열의 끝은 null
	op_len--;
	(*SR)[op_len] = '\0'; 
	(*OP)[op_len] = '\0'; 
	(*TR)[op_len] = '\0';


	// output string 뒤에서 부터 operation 역추적
	// 맨 오른쪽 밑에서 시작 => back tracking
	i = ssize - 1; j = tsize - 1;
	int idx = op_len-1; // 현재 문자열 위치
	
	while (op_len >= 1 && idx >=0) { 
			if (i < 0 || j < 0) break;
			current = Table[i][j];
			sub = del = ins = -1;
			if (i >= 1) {
				if (current == Table[i - 1][j] + del_cost) { // deletion
					del = 1;
				}
			}
			if (j >= 1) {
				if (current == Table[i][j - 1] + ins_cost) { // insertion
					ins = 1;
				}
			}
			if (i >= 1 && j >= 1) {
				if (SS[i - 1] == TS[j - 1]) { // 그대로
					(*SR)[idx] = SS[i - 1];
					(*TR)[idx] = TS[j - 1];
					(*OP)[idx] = '.';
					i -= 1; j -= 1;
					idx--;
					op_len--;
					//printf("op_len %d \n", op_len);
					continue;
				}
				if (current == Table[i - 1][j - 1] + sub_cost) { // substitution
					sub = 1;
				}
			}

			if (del == 1 && ins == 1) { // compare del and ins
				if (del_cost < ins_cost) { // del로 선택
					del = 1; ins = 0;
				}
				else { // ins로 선택
					ins = 1; del = 0;
				}

			}
			
			if (del == 1) { // deletion
				(*SR)[idx] = SS[i - 1];
				(*TR)[idx] = '*';
				(*OP)[idx] = 'd';
				i -= 1;
			}
			else if (ins == 1) { // insertion
				(*SR)[idx] = '*';
				(*TR)[idx] = TS[j - 1];
				(*OP)[idx] = 'i';
				j -= 1;

			}
			else { // substitution
				(*SR)[idx] = SS[i - 1];
				(*TR)[idx] = TS[j - 1];
				(*OP)[idx] = 's';
				i -= 1; j -= 1;
			}
		
		idx--;
		op_len--;
		//printf("op_len %d \n", op_len);
		
	}
	
}

