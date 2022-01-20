#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int minimum(int a, int b, int c) { // 3���� ���� �� �ּڰ� ���ϱ�
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
	int ssize = strlen(SS) +1; // SS ���� + 1 => Table row
	int tsize = strlen(TS) +1; // TS ���� + 1 => Table column
	
	// Table �޸𸮴� main���� �̹� �Ҵ��.
	// Table cost �ʱ�ȭ
	Table[0][0] = 0;
	for (j = 1; j < tsize; j++) { // TS ���忡���� ���ڸ� �־���ϹǷ� 
		Table[0][j] = Table[0][j-1] + ins_cost;
	}
	for (i = 1; i < ssize; i++) { // SS ���忡���� ���ڸ� �����ϹǷ�
		Table[i][0] = Table[i - 1][0] + del_cost;
	}

	

	// Table cost ���
	for (i = 1; i < ssize; i++) {
		for (j = 1; j < tsize; j++) {
			if (SS[i - 1] == TS[j - 1]) // �ش� ���ڰ� �����Ҷ�
				Table[i][j] = Table[i - 1][j - 1]; // �밢���� cost�� ����
			else { // �ٸ��ٸ� ����, ���� ��(�밢��), ���� �߿� �ּڰ� ã��
				min = minimum(Table[i - 1][j - 1] + sub_cost, Table[i][j - 1] + ins_cost, Table[i - 1][j]+del_cost);
				Table[i][j] = min;
			}
		}
	}

	// �������� ����  S , T, OP ���� ���ϱ�
	int op_len = 0;
	// �� ������ �Ʒ��� �ε������� ��������
	i = ssize - 1; j = tsize - 1;
	
	
	int current = 0; // ���� Table �� �����ϴ� ����
	int sub, del, ins; // �� �߿� � �۾��� �����ؾ��ϴ��� �˷��ִ� �÷��� 

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
			// substitution & �״�� => operation ���̸� ���� �� ������ �ʿ� ����
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
		else { // substitution & �״�� 
			i -= 1; j -= 1;
		}
			
	
		op_len++;
		if (i <= 0 && j <= 0) break; // ���̻� ���Ҽ� �ִ� �ε����� ����
	
	}

	

	
	

	// �������� ���� i , d, s �ۼ�

	// ���� ���� ��ŭ output string ���� malloc
	op_len += 1;
	(*SR) = (char*)malloc(sizeof(char) * op_len);
	(*OP) = (char*)malloc(sizeof(char) * op_len);
	(*TR) = (char*)malloc(sizeof(char) * op_len);

	// allocation �� SR, OP, TR ũ�� ��
	*Mem_Allocated = sizeof(char) * (op_len) * 3;

	// ���ڿ��� ���� null
	op_len--;
	(*SR)[op_len] = '\0'; 
	(*OP)[op_len] = '\0'; 
	(*TR)[op_len] = '\0';


	// output string �ڿ��� ���� operation ������
	// �� ������ �ؿ��� ���� => back tracking
	i = ssize - 1; j = tsize - 1;
	int idx = op_len-1; // ���� ���ڿ� ��ġ
	
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
				if (SS[i - 1] == TS[j - 1]) { // �״��
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
				if (del_cost < ins_cost) { // del�� ����
					del = 1; ins = 0;
				}
				else { // ins�� ����
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

