#include "Graph_adj_list.h"
#include <queue>
using namespace std;

extern void errorExit(const char* s);

SLList2 pool;
unsigned long UsedMemoryForArray = 0;


void Read_Graph_adj_list(int Vnum, vertex* V, int Enum, edge* E) {
	// ���Ͽ��� �׷��� ������ �о� V�� E �迭�� �����Ѵ�.
	// V[ ].name�� E[ ].name�� ������ �ʿ䰡 ������ ���ǻ� �� �迭������
	//   index�� �����Ѵ�.
	// V[ ].S�� adjacent list header�� ���� ����ε� ���ȴ�.
	// ���� edge (i,j)�� ������ V[i].S�� edge index k�� push�ϰ�
	//  ���������� V[j].S�� k�� push�Ѵ�.
	// V[].flag�� E[].flag�� �ݵ�� false�� �����ؾ� �Ѵ�.

	// ***�� �Լ��� �ۼ��Ѵ�
	int i, vi, vj, cost;


	for (i = 0; i < Vnum; i++) {
		V[i].name = i;
		V[i].flag = false;
	}
	for (i = 0; i < Enum; i++) {
		scanf_s("%d %d %d", &vi, &vj, &cost);
		//printf("%d %d %d\n", vi, vj, cost);
		E[i].name = i;
		E[i].vf = vi;
		E[i].vr = vj;
		E[i].cost = 1;
		E[i].flag = false;
		SLL* p = pool.allocSLL();
		p->i = i;
		V[vi].S.push(p);
		SLL* q = pool.allocSLL();
		q->i = i;
		V[vj].S.push(q);



	}
	/*
	for (i = 0; i < Vnum; i++) {
		SLL* pt = V[i].S.top();
		printf("[%d]\n", i);
		while (pt != NULL) {
			printf("%d\n", pt->i);
			pt = pt->p;
		}

	}*/
	return;
}

void Free_Graph_adj_list(int Vnum, vertex* V) {
	// V �迭�� adjacency list�� ���Ҹ� pop()�� ����Ͽ�
	// ���  pool�� �ǵ��� �ش�
	int k;
	SLL* p;
	for (k = 0; k < Vnum; k++) {
		do {
			p = V[k].S.pop();
			pool.freeSLL(p);

		} while (V[k].S.empty() != 1);
	}

	// ***�� �Լ��� �ۼ��Ѵ�

}

int BFS_Tree_adj_list(
	int     src,   // source node index
	int     Vnum,  // number of vertices
	vertex* V,     // vertex structure array (starting index 0)
	int     Enum,  // number of edges
	edge* E     // edge structure array (starting index 0)
) {
	// BFS�� ����Ͽ� BFS tree�� ���ϴ� ������ flag�� true�� �����Ѵ�.
	// BFS ���� vertex�� �Է� ���Ͽ��� �����ȴ�(src).
	// V[]�� adjacent list Ž���� .top() ��� �Լ��� ����Ͽ�
	//  adj list ����� ��� �̸� ���󰡸� ���� vertex�� Ž���Ѵ�.
	// BFS tree�� ���� ������ cost ���� return �Ѵ�
	//   (not unique but ��� �� edge cost�� 1�̸� unique)
	// -- �Լ��� ��� parameter�� ���� �ʿ�� ����.
	// -- BFS�� ���� queue�� �ʿ��ϸ� STL�� queue�� ����ص� ����
	queue<int> q;

	// ***�� �Լ��� �ۼ��Ѵ�
	SLL* p;
	int VF, VR, edge, v;
	int BFS_cost = 0;
	int target;
	q.push(src);

	while (q.empty() != 1) {
		v = q.front();
		q.pop();
		for (p = V[v].S.top(); p != NULL; p = p->p) {
			edge = p->i;
			if (E[edge].flag != true) {

				VF = E[edge].vf; VR = E[edge].vr;

				if (VF == v)
					target = VR;
				else
					target = VF;
				if (V[target].flag == false) {
					E[edge].flag = true;
					q.push(target);
					V[target].flag = true;
					//printf("%d ==========\n", VR);
					BFS_cost += E[edge].cost;

				}

			}
		}
	}



	return BFS_cost;
}

// SLL management functions
// �Ʒ� �Լ����� 02_04_CSE3081_CPrg&DataStructure_�߰��ڷ�.pdf��
//   �����Ͽ� �� �Լ����� ä�� ����.
// ���ø� �ʿ��ϹǷ� ť�� ��� �Լ��� �Ʒ� �Լ� ����Ʈ�� ����

// stack member fuctions
void sllStack2::push(SLL* p) {
	// insert p to the top of stack ST
	p->p = ST;
	ST = p;
	return;
}

SLL* sllStack2::pop(void) {
	// remove and return p at the top of ST

	// ***�� �Լ��� �ۼ��Ѵ�
	SLL* p = ST;
	if (ST->p == NULL)
		ST = NULL;
	else
		ST = ST->p;
	return p;
}

SLL* sllStack2::top(void) {
	// return p at the top of ST
	return ST;
}

bool sllStack2::empty(void) {
	// return true if empty
	if (ST == NULL)
		return true;
	else
		return false;
}

// SLList2 member functions
SLL* SLList2::allocSLL(void) {		// allocate an SLL element
	SLL* p;

	// ***�� �Լ��� �ۼ��Ѵ�
	if (SLL_pool == NULL) {
		p = (SLL*)malloc(sizeof(SLL));
		if (p == NULL)
			errorExit("Error in Alloc_SLL");
		UsedMemoryForSLLs += sizeof(SLL);
		p->i = NONE;
	}
	else {
		p = SLL_pool;
		SLL_pool = p->p;
	}
	p->p = NULL;
	++SLL_cnt;
	return(p);
}

void SLList2::freeSLL(SLL* p) {		// free *p (move it to SLL_pool
	if (p->i == NONE) {
		errorExit("This is already freed(freeSLL).");
	}

	// ***�� �Լ��� �ۼ��Ѵ�
	p->i = NONE;
	p->p = SLL_pool;
	SLL_pool = p;
	--SLL_cnt;
}

void SLList2::freeSLL_pool(void) {	// clear SLL_pool
	SLL* p = SLL_pool;

	// ***�� �Լ��� �ۼ��Ѵ�
	while (p != NULL) {
		SLL_pool = p->p;
		free(p);
		UsedMemoryForSLLs -= sizeof(SLL);
		p = SLL_pool;
	}
	if (SLL_cnt != 0) {
		errorExit("Non-zero SLL_cnt after cleanup.");
	}
}