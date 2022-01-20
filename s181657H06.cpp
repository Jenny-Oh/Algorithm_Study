#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

#define NONE -1
#define INF 1000000000

typedef struct elm_edge {
	int  vf, vr;  // e = (vf, vr) where vf, vr are vertex array indices
	int  cost;    // edge cost
	bool flag;    // true if the edge is in the SP spanning tree, false otherwise 
	int  fp, rp;  // adj list ptr of forward and reverse (-1 if none)
} edge;

typedef struct elm_vertex {
	int  f_hd, r_hd;	// adj list header(-1 if none)
	int  distance;		// distance from src to this vertex
	int  heap_idx;		// minHeap index
	bool inS;			// true if SP length found(true when move from V-S to S) 
} vertex;



void insert(vertex *V, int v_idx, int *len_heap, int *minheap) {

	int cur = ++(*len_heap); // current index in minheap
	minheap[cur] = v_idx;
	V[v_idx].heap_idx = cur;

	int parent = cur / 2;
	int tmp, tmp2;
	while (parent >= 1) {
		if (V[minheap[cur / 2]].distance > V[minheap[cur]].distance) {
			// parent distance > child distance => swap is needed
			// swap minheap element
			
			tmp = minheap[parent];
			minheap[parent] = minheap[cur];
			minheap[cur] = tmp;
			
			// swap heap index
			tmp2 = V[minheap[parent]].heap_idx;
			V[minheap[parent]].heap_idx = V[minheap[cur]].heap_idx;
			V[minheap[cur]].heap_idx = tmp2;
			
			cur = parent;
			parent = cur/  2;  // move up
		}
		else break;
	}


} 



int delete_min(vertex* V, int* minheap, int* len_heap) {
	int min_h = minheap[1];
	V[min_h].heap_idx = -1;


	minheap[1] = minheap[*len_heap];
	minheap[*len_heap] = -1;
	
	int cur = 1;
	int child = cur * 2; 
	int tmp, tmp2;
	(*len_heap)--;
	
	if (child < *len_heap) {
		if (V[minheap[child + 1]].distance <= V[minheap[child]].distance) // left or right
			child++;
	}
	
	
	while ((child + 1)< *len_heap) {
		if (V[minheap[child]].distance < V[minheap[cur]].distance) {
			// parent distance > child distance
			// swap minheap element
			tmp = minheap[child];
			minheap[child] = minheap[cur];
			minheap[cur] = tmp;

			// swap heap index
			tmp2 = V[minheap[child]].heap_idx;
			V[minheap[child]].heap_idx = V[minheap[cur]].heap_idx;
			V[minheap[cur]].heap_idx = tmp2;

			cur = child;
			child *= 2;
			if ( child < *len_heap)  {
				if (V[minheap[child+ 1]].distance <= V[minheap[child]].distance) // left or right
					child++;
			}

		}
		else break;
		
	}

	return min_h;
	
}


void move_up(vertex* V, int v_idx, int* minheap, int* len_heap) {
	// to maintain the heap property, move the elements
	int cur = V[v_idx].heap_idx;
	int tmp, tmp2;

	int parent = cur / 2;
	while (parent >= 1) {
		if (V[minheap[parent]].distance > V[minheap[cur]].distance) {
			// for cross reference
			
			// swap minheap element
			tmp = minheap[parent];
			minheap[parent] = minheap[cur];
			minheap[cur] = tmp;

			// swap heap index
			tmp2 = V[minheap[parent]].heap_idx;
			V[minheap[parent]].heap_idx = V[minheap[cur]].heap_idx;
			V[minheap[cur]].heap_idx = tmp2;
			
			
			cur = parent;
			parent = cur / 2;
		}
		else break;
	}

}


int SPT_Dijkstra(
	int src,	// source vertex index
	// graph structure array
	// 1. the adjacency list structure is the same as PHW02
	// 2. additional fields are added for Dijkstra's algorithm(see .h file)
	int Vnum, vertex *V,	// Vertex array size and the array
	int Enum, edge *E,		// Edge array size and the array

	int *minHeap	// array for min heap (array size = Vnum+1)
		// heap index range is 1 ~ (Vnum - 1) note: src must not in the initial heap
		// just arry is passed. must construct min-heap in this function

	// OUTPUT
	// 1. V[].distance : shortest path length from src to this vertex
	// 2. shortest path spanning tree : set E[].flag = true if the edge is in the tree
	// 3. return the sum of edge costs in the shortest path spanning tree.
	//    should be small as possible (think a way to make it small)
) {
	int treeCost = 0;
	// *** �� �Լ��� �ۼ����� ***
	// �ݵ�� min-heap�� ����Ͽ� O((n+m)logn) �˰����� �����ؾ� �Ѵ�(�ƴϸ� trivial�� ���α׷���)
	// heap ���� �� �ʿ��� �Լ��� �����Ӱ� �ۼ��Ͽ� �߰��Ѵ�.
	// �׷��� global ����, dynamic array ���� �߰��� ������� �ʴ´�(������ �ʿ� ����)
	
	int len_heap = 0;
	// initialize src vertex 
	V[src].distance = 0;
	V[src].inS = true;

	// front 
	int cur;
	for (cur = V[src].f_hd; cur != NONE; cur = E[cur].fp) {
		V[E[cur].vr].distance = E[cur].cost;
		insert(V, E[cur].vr, &len_heap, minHeap);
		
	}
	// rear
	for (cur = V[src].r_hd; cur != NONE; cur = E[cur].rp) {
		V[E[cur].vf].distance = E[cur].cost;
		insert(V, E[cur].vf, &len_heap, minHeap);
	}
	// if there's vertex left
	for (cur = 0; cur < Vnum; cur++) {
		if (cur == src) continue;
		if (V[cur].distance == INF)
			insert(V, cur, &len_heap, minHeap);
	}


	// adjust heap
	int i, u, w;
	for (i = 0; i < Vnum - 1; i++) {
		u = delete_min(V, minHeap, &len_heap);
		V[u].inS = true;
		// front
		for (cur = V[u].f_hd; cur != NONE; cur = E[cur].fp) {
			w = E[cur].vr;
			// distance ���� => minHeap ������
			if (V[w].inS == false && (V[u].distance + E[cur].cost) < V[w].distance) {
				V[w].distance = V[u].distance + E[cur].cost;
				move_up(V, w, minHeap, &len_heap);
			}
		}
		// rear
		for (cur = V[u].r_hd; cur != NONE; cur = E[cur].rp) {
			w = E[cur].vf;
			if (V[w].inS == false && (V[u].distance + E[cur].cost) < V[w].distance) {
				// distance ���� => minHeap ������
				V[w].distance = V[u].distance + E[cur].cost;
				move_up(V, w, minHeap, &len_heap);
			}
		}
	}

	// find minimum cost path
	
	int flag = 0;
	int min_cost = 0; 
	for (i = 0; i < Vnum; i++) {
		if (i == src)
			continue;
		flag = 0;
		// front first
		for (cur = V[i].f_hd; cur != NONE; cur = E[cur].fp) {
			w = E[cur].vr;
			if (V[i].distance == V[w].distance + E[cur].cost) {
				min_cost += E[cur].cost;
				E[cur].flag = true;
				flag = 1;
				break;
			}
		}

		// if not found => check rear 
		for (cur = V[i].r_hd; !flag && cur != NONE; cur = E[cur].rp) {
			w = E[cur].vf;
			if (V[i].distance == V[w].distance + E[cur].cost) {
				min_cost += E[cur].cost;
				E[cur].flag = true;
				flag = 1;
				break;
			}
		}
		
		
	}
	
	
	treeCost = min_cost;

	return treeCost;
}

void Read_Graph(int Vnum, vertex *V, int Enum, edge *E) {
	// Graph �ڷᱸ���� ����� �Լ�
	// *** �� �Լ��� �߰����� ***
	// PHW02�� Read_Graph_adj_array()�� �� ������ �ڷᱸ���� ���� ��¦ �����Ͽ� ����Ѵ�
	// ��, Read_Graph_adj_array()���� ���ʿ��� ������ ������ �� ���.
	
	int i, vi, vj, cost;
	
	for (i = 0; i < Vnum; i++) { // vertex �ʱ�ȭ
		V[i].distance = INF;
		V[i].inS = false;
		V[i].f_hd = NONE;
		V[i].r_hd = NONE;
	}
	for (i = 0; i < Enum; i++) { // edge �ʱ�ȭ
		E[i].cost = -1;
		E[i].flag = false;
		E[i].vf = NONE;
		E[i].vr = NONE;
		E[i].rp = NONE;
		E[i].fp = NONE;
	}
	for (i = 0; i < Enum; i++) {
		scanf("%d %d %d", &vi, &vj, &cost); // �� �� ���� edge ������ �о�´�
		E[i].vf = vi;
		E[i].vr = vj;
		E[i].cost = cost;


		if (V[vi].f_hd != NONE) // vi �ڸ�(f_hdȮ��)�� vertex �� ������� ������ edge�� �����ؾ��Ѵ�
			E[i].fp = V[vi].f_hd;
		V[vi].f_hd = i;


		if (V[vj].r_hd != NONE) // ���� �۾��� vj�� ���ؼ��� �����ϱ� ����(r_hd Ȯ��)
			E[i].rp = V[vj].r_hd;
		V[vj].r_hd = i;


	}

	


}

// the following functions are for testing if the submitted program is correct.
int  Tree_Check(int Vnum, vertex *V, int Enum, edge *E, int *visited);
bool SPT_test(int src, int Vnum, vertex *V, int Enum, edge *E, int *minHeap);
void Error_Exit(const char *s);

int main ( void ) {
	int		src;
	vertex *V;		int Vnum;
	edge   *E;		int Enum;
	int    *minHeap;
	int    Tree_cost;
	int    Tnum; 		// # of test cases
	clock_t start, finish;
	double cmpt;

	scanf_s("%d", &Tnum);		// read # of tests

	for (int t = 0; t < Tnum; t++ ) {
		scanf_s("%d %d %d", &Vnum, &Enum, &src);
		V = new vertex [Vnum];
		E = new edge [Enum];
		minHeap = new int[Vnum + 1];	// heap array allocation
		if ( V == NULL || E == NULL || minHeap == NULL ) {
			Error_Exit("Memory Allocation Error");
		}
		Read_Graph(Vnum, V, Enum, E);

		/**/start = clock();	// start timer

		Tree_cost = SPT_Dijkstra(src, Vnum, V, Enum, E, minHeap);	// code by students

		/**/finish = clock();	// stop timer
		cmpt = ((double)(finish - start)) / (double)CLK_TCK;

		// �Ʒ� Tree_Check�� SPT_test �Լ��� ÷���� SPT_test.obj ���Ͽ� �ִ�.
		// �� �׽�Ʈ���� ������ ���Ͽ� ���α׷��� �����ϸ� ���� �߸��� ���̴�(�����ص� 0��)
        if (Tree_Check(Vnum, V, Enum, E, minHeap) == 0) {
			Error_Exit("   ERROR The result is not a spanning tree");
		}
		if (SPT_test(src, Vnum, V, Enum, E, minHeap) == false) {
			Error_Exit("** Something wrong in applying Dijkstra's");
		}
		if ( t != 0 ) 
			printf("\n");

		printf("**T%d (Dijkstra) (V = %d, E = %d, time = %.3f sec) Tree Cost = %d\n", 
			t+1, Vnum, Enum, cmpt, Tree_cost);

		delete [] minHeap; delete [] V; delete [] E;
	}
	return 0;
}

void Error_Exit (const char *s ) {
  printf("%s\n", s);
  exit(-1);
}
