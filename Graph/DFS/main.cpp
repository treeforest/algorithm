#include "DFS.h"

int main() {
	//CGraph G(DG);
	CGraph G(UDN);

	G.InsertVex('a');// 0
	G.InsertVex('b');// 1
	G.InsertVex('c');// 2
	G.InsertVex('d');// 3
	G.InsertVex('e');// 4
	G.InsertVex('f');// 5
	G.InsertVex('g');// 5
	G.InsertVex('h');// 5

	G.InsertEdge('a', 'b');
	G.InsertEdge('a', 'e');
	G.InsertEdge('a', 'h');
	G.InsertEdge('b', 'c');
	G.InsertEdge('b', 'd');
	G.InsertEdge('c', 'd');
	G.InsertEdge('c', 'h');
	//G.InsertEdge('e', 'a');
	//G.InsertEdge('e', 'c');
	G.InsertEdge('e', 'f');
	G.InsertEdge('e', 'g');

	G.PrintInfo();

	G.DFSTraverse();

	return 0;
}