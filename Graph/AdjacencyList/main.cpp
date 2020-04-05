#include <string>
#include "AdjacencyList.hpp"

void TestUDGraph_List();
void TestDGraph_List();

typedef char VexType;
typedef int EdgeType;

typedef BOOL(*FuncType)(VexType v1, VexType v2);
BOOL compare(VexType v1, VexType v2) {
	if (v1 == v2) return TRUE;
	return FALSE;
}

int main() {
	TestUDGraph_List();
	TestDGraph_List();
	return 0;
}

void TestUDGraph_List() {
	ALGraph<VexType, EdgeType, FuncType> G(compare, UDG);
	G.InsertVex('a');
	G.InsertVex('b');
	G.InsertVex('c');
	G.InsertVex('d');

	G.InsertEdge('a', 'b');
	G.InsertEdge('a', 'c');
	G.InsertEdge('a', 'd');
	G.InsertEdge('b', 'd');
	G.InsertEdge('c', 'd');
	G.PrintInfo();
	cout << endl << endl;

	cout << "¶¥µã c µÄË÷ÒýºÅ£º " << G.LocateVex('c') << endl << endl;

	// É¾³ý±ß
	cout << "É¾³ý±ß (a,b)" << endl;
	G.DeleteEdge('a', 'b');
	G.PrintInfo();
	cout << endl << endl;

	// É¾³ý¶¥µã
	cout << "É¾³ý¶¥µã c" << endl;
	G.DeleteVex('c');
	G.PrintInfo();
	cout << endl << endl;

	// É¾³ý¶¥µã
	cout << "É¾³ý¶¥µã a" << endl;
	G.DeleteVex('a');
	G.PrintInfo();
	cout << endl << endl;
}

void TestDGraph_List() {
	ALGraph<VexType, EdgeType, FuncType> G(compare, DG);
	G.InsertVex('a');
	G.InsertVex('b');
	G.InsertVex('c');
	G.InsertVex('d');

	G.InsertEdge('a', 'b');
	G.InsertEdge('a', 'c');
	G.InsertEdge('a', 'd');
	G.InsertEdge('b', 'c');
	G.InsertEdge('b', 'd');
	G.InsertEdge('c', 'd');
	G.InsertEdge('c', 'a');
	G.InsertEdge('d', 'a');

	G.PrintInfo();
	cout << endl << endl;

	// É¾³ý±ß
	cout << "É¾³ý±ß <b, d>: " << endl;
	G.DeleteEdge('b', 'd');
	G.PrintInfo();
	cout << endl << endl;

	// É¾³ý¶¥µã
	cout << "É¾³ý¶¥µã c" << endl;
	G.DeleteVex('c');
	G.PrintInfo();
	cout << endl << endl;

	// É¾³ý¶¥µã
	cout << "É¾³ý¶¥µã d" << endl;
	G.DeleteVex('d');
	G.PrintInfo();
	cout << endl << endl;
}
