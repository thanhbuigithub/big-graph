//
// Created by Bui Chi Thanh on 15/01/2023.
//

#ifndef BIGGRAPH_GRAPH_H
#define BIGGRAPH_GRAPH_H

#include <map>
#include "Node.h"
#include "Edge.h"
#include "Define.h"
#include "math.h"

using namespace std;

class Graph : public Reader, public Writer {
protected:
    int autoIId;
    int nEdges;

public:
    Graph(): autoIId(0), nEdges(0) {}
    Graph(int& n): autoIId(n), nEdges(0) {}
    Graph(Graph& g): autoIId(g.autoIId), nEdges(g.nEdges) {}

    void writeBin(ofstream &ws) override {};
    void writeTxt(ofstream &ws) override {};
    void readBin(ifstream &rs) override {};
    void readTxt(ifstream &rs) override {};

    friend class UDGraph;
};

class UDGraph : protected Graph {
private:
    map<int, UDNode> nodeM;

private:
    UDNode& getNode(const int& nid) { return nodeM.at(nid); }
    const UDNode& getNode(const int& nid) const { return nodeM.at(nid); }

public:
    UDGraph(): Graph(), nodeM() {}
    UDGraph(int&n): Graph(n), nodeM() {}
    UDGraph(UDGraph& udGraph): Graph(udGraph.autoIId), nodeM(udGraph.nodeM) {}

    /// Returns the number of nodes.
    int getNodes() const { return nodeM.size(); }
    /// Adds a node with ID `nid` to the graph. Return ID of the node.
    int addNode(int nid = -1);
    /// Adds a node with ID `node.getId()` to the graph. Return ID of the node.
    int addNode(const UDNode& node);
    /// Adds a node with ID `nid` to the graph and creates edges to it from all nodes in vector `idV`. Return ID of the node.
    int addNode(int nid, const vector<int>& idV);
    /// Deletes node with ID `nid` from the graph.
    void delNode(const int& nid);
    /// Deletes node with ID `node.getId()` from the graph.
    void delNode(const UDNode& node);
    /// Return `true` if ID `nid` is a node.
    bool isNode(const int& nid) const;
    /// Returns an iterator referring to the first node in the graph.
    NodeI<UDNode> beginNI() const { return NodeI<UDNode>{nodeM.begin()}; }
    /// Returns an iterator referring to the past-the-end node in the graph.
    NodeI<UDNode> endNI() const { return NodeI<UDNode>{nodeM.end()}; }
    /// Returns an iterator referring to the node of ID nid in the graph.
    NodeI<UDNode> getNI(const int& nid) const { return NodeI<UDNode>{nodeM.find(nid)}; }

    /// Returns current auto increase id of the graph
    int getAutoIId() { int id(autoIId); autoIId++; return id; }

    /// Returns the number of edges .
    int getEdges() const;
    /// Adds an edge between node `srcId` and node `dstId` to the graph. Return `true` if add successful
    bool addEdge(const int& srcNId, const int& dstNId);
    /// Adds an edge between node `srcId` and node `dstId` to the graph. If any of nodes do not exist, create them. Return `true` if add successful
    bool addEdgeUpsert(const int& srcNId, const int& dstNId);
    /// Deletes an edge between node `srcId` and node `dstId` from the graph.
    void delEdge(const int& srcNId, const int& dstNId);
    /// Tests whether an edge between node `srcId` and node `dstId` exists in the graph.
    bool isEdge(const int& srcNId, const int& dstNId);
    /// Returns an iterator referring to the first edge in the graph.
    EdgeI<UDNode> beginEI() const {
        NodeI<UDNode> ni = beginNI();
        EdgeI<UDNode> ei(ni, endNI(), 0);
        if (!isEmpty() && (ni.getOutDeg() == 0 || ni.getId()>ni.getOutNbrNId(0))) {
            ei++;
        }
        return ei;
    }
    /// Returns an iterator referring to the past-the-end edge in the graph.
    EdgeI<UDNode> endEI() const { return EdgeI(endNI(), endNI()); }
    /// Returns an iterator referring to edge (srcNId, dstNId) in the graph.
    EdgeI<UDNode> getEI(const int& srcNId, const int& dstNId) const;

    /// Gets a vector IDs of all nodes in the graph.
    void getNIdV(vector<int>& idV) const;

    /// Tests whether the graph is isEmpty.
    bool isEmpty() const;
    /// Deletes all nodes and edges from the graph.
    void clear();
    /// Checks the graph data structure for internal consistency.
    bool isOk() const;
    /// Export the graph to binary type
    void writeBin(ofstream& ws) override;
    /// Export the graph to text type
    void writeTxt(ofstream& ws) override;
    /// Import the graph from binary file
    void readBin(ifstream& rs) override;
    /// Import the graph from text file
    void readTxt(ifstream& rs) override;

    /// Print the graph.
    void print(ostream &os) const;
};

#endif //BIGGRAPH_GRAPH_H
