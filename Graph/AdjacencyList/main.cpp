#include <string>
#include "AdjacencyList.hpp"

void TestUDGraph_List();
void TestDGraph_List();

typedef char VertexType;
typedef string VertexInfo;
typedef int EdgeInfo;

typedef BOOL(*FuncType)(VertexType v1, VertexType v2);
BOOL compare(VertexType v1, VertexType v2) {
	if (v1 == v2) return TRUE;
	return FALSE;
}

int main() {
	
	//TestUDGraph_List();
	TestDGraph_List();

	return 0;
}

void TestUDGraph_List() {
	ALGraph<VertexType, VertexInfo, EdgeInfo, FuncType> G(compare, UDN);
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

	cout << "∂•µ„ c µƒÀ˜“˝∫≈£∫ " << G.LocateVex('c') << endl << endl;

	// …æ≥˝±ﬂ
	cout << "…æ≥˝±ﬂ (a,b)" << endl;
	G.DeleteEdge('a', 'b');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„
	cout << "…æ≥˝∂•µ„ c" << endl;
	G.DeleteVex('c');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„
	cout << "…æ≥˝∂•µ„ a" << endl;
	G.DeleteVex('a');
	G.PrintInfo();
	cout << endl << endl;
}

void TestDGraph_List() {
	ALGraph<VertexType, VertexInfo, EdgeInfo, FuncType> G(compare, DN);
	G.InsertVex('a');
	G.InsertVex('b');
	G.InsertVex('c');
	G.InsertVex('d');

	G.SetVex('a', " ’‚ «aµƒ∂•µ„–≈œ¢ ");

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

	// …æ≥˝±ﬂ
	cout << "…æ≥˝±ﬂ <b, d>: " << endl;
	G.DeleteEdge('b', 'd');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„
	cout << "…æ≥˝∂•µ„ c" << endl;
	G.DeleteVex('c');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„
	cout << "…æ≥˝∂•µ„ d" << endl;
	G.DeleteVex('d');
	G.PrintInfo();
	cout << endl << endl;
}
