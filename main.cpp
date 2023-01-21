#include <iostream>
#include <unordered_map>
#include "Node.h"
#include "Graph.h"

void testExportTxt(UDNode* test) {
    ofstream ws("test.graph.txt", ios::out);
    test->writeTxt(ws);
    ws.close();
}

void testImportTxt(UDNode* test) {
    ifstream rs("test.graph.txt", ios::in);
    test->readTxt(rs);
    rs.close();
}

void testExportBin(UDNode* test) {
    ofstream ws("test.graph.bin", ios::out);
    test->writeBin(ws);
    ws.close();
}

void testImportBin(UDNode* test) {
    ifstream rs("test.graph.bin", ios::in);
    test->readBin(rs);
    rs.close();
}

void testGraph() {
//    ofstream ws1("test.graph.txt", ios::out);
//    ofstream ws2("test.graph.bin", ios::out | ios::binary);
    ifstream rs1("test.graph.txt", ios::in);
    ifstream rs2("test.graph.bin", ios::in | ios::binary);
    DGraph* graph = new DGraph();
//    graph->addEdgeUpsert(4,0);
//    graph->addEdgeUpsert(5,4);
//    graph->addEdgeUpsert(5,2);
//    graph->addEdgeUpsert(3,5);
//    graph->addEdgeUpsert(3,4);
//    graph->addEdgeUpsert(2,3);
//    graph->addEdgeUpsert(1,2);
//    graph->addEdgeUpsert(0,1);
//    graph->addEdgeUpsert(0,5);
//    graph->writeTxt(ws1);
//    graph->writeBin(ws2);
//
//    graph->readTxt(rs1);
//    graph->print(cout);
    graph->readBin(rs2);
    graph->print(cout);

//    ws1.close();
//    ws2.close();
    rs1.close();
    rs2.close();
}

int main() {
//    UDNode* test = new UDNode(101);
//    for (int i = 0; i < 10; ++i) {
//        test->addNbrNId(110 + i);
//    }
//
//    test->print(cout);
//    cout << endl;
//    testExportBin(test);
//    UDNode* test1 = new UDNode(-1);
//    testImportBin(test1);
//    test1->print(cout);
//    cout << sizeof(int);
    testGraph();
    return 0;
}