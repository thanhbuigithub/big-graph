#include <iostream>
#include <unordered_map>
#include "Node.h"
#include "NodeDataType.h"
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
    auto* graph = new DGraph();
//    auto n0 = graph->addNode(new NodeDataString("AAA"));
//    auto n1 = graph->addNode(new NodeDataString("BBB"));
//    auto n2 = graph->addNode(new NodeDataString("CCC"));
//    auto n3 = graph->addNode(new NodeDataString("DDD"));
//    auto n4 = graph->addNode(new NodeDataString("EEE"));
//    auto n5 = graph->addNode(new NodeDataString("FFF"));
//    graph->addEdge(n5,n4);
//    graph->addEdge(n5,n2);
//    graph->addEdge(n3,n5);
//    graph->addEdge(n3,n4);
//    graph->addEdge(n2,n3);
//    graph->addEdge(n1,n2);
//    graph->addEdge(n0,n1);
//    graph->addEdge(n0,n5);
//    graph->writeTxt(ws1);
//    graph->writeBin(ws2);

    graph->readTxt(rs1);
    graph->delEdge(5, 0);
    graph->print(cout);
//    graph->readBin(rs2);
//    graph->print(cout);
    cout << graph->isOk();
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

//    ifstream rs1("test.txt", ios::in);
//    string value;
//    getline(rs1, value, ',');
//    cout << value << endl;
//    getline(rs1, value);
//    cout << value << endl;
//    getline(rs1, value, ',');
//    cout << value << endl;
//    getline(rs1, value);
//    cout << value << endl;
    return 0;
}