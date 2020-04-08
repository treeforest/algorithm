#include "AdjacencyMatrix.h"
#include <string>
#include <iostream>
using namespace std;
void Test_Matrix();

int __cdecl main() {
	Test_Matrix();

	return 0;
}

// 接口测试
void Test_Matrix() {
	//MGraph G(UDG);
	MGraph G(DG);

	string a = "a";
	string b = "b";
	string c = "c";
	string d = "d";

	// InsertVex
	G.InsertVex((VexType)a.c_str(), a.length());
	G.InsertVex((VexType)b.c_str(), b.length());
	G.InsertVex((VexType)c.c_str(), c.length());
	G.InsertVex((VexType)d.c_str(), d.length());

	// SetVex
	cout << "SetVex" << endl;
	string vexInfo = "Hello this is VexInfo \0\0 ！！！";
	G.SetVex((VexType)a.c_str(), a.length(), (VexInfo)vexInfo.c_str(), vexInfo.length(), TRUE);

	// GetVex
	string tmp;
	cout << "GetVex" << endl;
	VexInfo aInfo = G.GetVex((VexType)a.c_str(), a.length());
	tmp = string(aInfo, sdslen(aInfo));
	sdsfree(aInfo);
	cout << tmp << endl;

	VexInfo cInfo = G.GetVex((VexType)c.c_str(), c.length());
	tmp = string(cInfo, sdslen(cInfo));
	cout << tmp << endl;
	sdsfree(cInfo);
	cout << endl << endl;

	// InsertEdge
	G.InsertArc((VexType)a.c_str(), a.length(), (VexType)b.c_str(), b.length(), (ArcInfo)"这是(a, b)边信息", strlen("这是(a, b)边信息"));
	G.InsertArc((VexType)a.c_str(), a.length(), (VexType)c.c_str(), c.length(), (ArcInfo)"这是(a, c)边信息", strlen("这是(a, c)边信息"));
	G.InsertArc((VexType)a.c_str(), a.length(), (VexType)d.c_str(), d.length(), (ArcInfo)"这是(a, d)边信息", strlen("这是(a, d)边信息"));
	G.InsertArc((VexType)b.c_str(), b.length(), (VexType)d.c_str(), d.length(), (ArcInfo)"这是(b, d)边信息", strlen("这是(b, d)边信息"));
	G.InsertArc((VexType)c.c_str(), c.length(), (VexType)d.c_str(), d.length(), (ArcInfo)"这是(c, d)边信息", strlen("这是(c, d)边信息"));
	G.PrintInfo();
	cout << endl << endl;

	// GetEdge
	cout << "GetEdge" << endl;
	ArcInfo ad = G.GetArc((VexType)a.c_str(), a.length(), (VexType)d.c_str(), d.length());
	cout << string(ad, sdslen(ad));
	sdsfree(ad);
	cout << endl << endl;

	// DeleteEdge
	cout << "删除边 (a,b)" << endl;
	G.DeleteArc((VexType)a.c_str(), a.length(), (VexType)b.c_str(), b.length());
	G.PrintInfo();
	cout << endl << endl;

	// DeleteVex
	cout << "删除顶点 c" << endl;
	G.DeleteVex((VexType)c.c_str(), c.length());
	G.PrintInfo();
	cout << endl << endl;
}