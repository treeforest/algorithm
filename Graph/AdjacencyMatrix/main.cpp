#include <string>

#include "AdjacencyMatrix.hpp"
void TestUDGraph_Matrix();
void TestDGraph_Matrix();

typedef char VexType;
typedef int EdgeInfo;

typedef BOOL(*F)(VexType v1, VexType v2);
BOOL f(VexType v1, VexType v2) {
	if (v1 == v2) return TRUE;
	return FALSE;
}

int main() {

	TestUDGraph_Matrix();
	//TestDGraph_Matrix();

	return 0;
}

// ≤‚ ‘ŒﬁœÚÕº
void TestUDGraph_Matrix() {
	MGraph<char, int, string, F> G(f, UDG);
	G.InsertVex('a');
	G.InsertVex('b');
	G.InsertVex('c');
	G.InsertVex('d');

	string edge = "’‚ «±ﬂµƒ–≈œ¢";
	G.InsertEdge('a', 'b', &edge);
	G.InsertEdge('a', 'c', &edge);
	G.InsertEdge('a', 'd', &edge);
	G.InsertEdge('b', 'd', &edge);
	G.InsertEdge('c', 'd', &edge);
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
}

// ≤‚ ‘”–œÚÕº
void TestDGraph_Matrix() {
	MGraph<char, int, int, F> G(f, DN);
	G.InsertVex('a');
	G.InsertVex('b');
	G.InsertVex('c');
	G.InsertVex('d');

	int edge = 1;
	G.InsertEdge('a', 'b', &edge, TRUE);
	G.InsertEdge('b', 'a', &edge, TRUE);
	G.InsertEdge('a', 'c', &edge, TRUE);
	G.InsertEdge('c', 'a', &edge, TRUE);
	G.InsertEdge('a', 'd', &edge, TRUE);
	G.InsertEdge('b', 'd', &edge, TRUE);
	G.InsertEdge('c', 'd', &edge, TRUE);
	G.PrintInfo();
	cout << endl << endl;

	cout << "∂•µ„ c µƒÀ˜“˝∫≈£∫ " << G.LocateVex('c') << endl << endl;

	// …æ≥˝±ﬂ
	cout << "…æ≥˝±ﬂ <a,b>" << endl;
	G.DeleteEdge('a', 'b');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„ b
	cout << "…æ≥˝∂•µ„ b" << endl;
	G.DeleteVex('b');
	G.PrintInfo();
	cout << endl << endl;

	// …æ≥˝∂•µ„ a
	cout << "…æ≥˝∂•µ„ a" << endl;
	G.DeleteVex('a');
	G.PrintInfo();
	cout << endl << endl;
}
