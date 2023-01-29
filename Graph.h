//
// Created by Bui Chi Thanh on 15/01/2023.
//

#ifndef BIGGRAPH_GRAPH_H
#define BIGGRAPH_GRAPH_H

#include <map>
#include "Node.h"
#include "Edge.h"
#include "Define.h"
#include <cmath>
#include "NodeDataType.h"

using namespace std;

template<class T>
class Graph : public Reader, public Writer {
protected:
    int autoIId;
    int nEdges;
    map<int, T> nodeM;

protected:
    T& getNode(const int& nid) { return nodeM.at(nid); }
    const T& getNode(const int& nid) const { return nodeM.at(nid); }

public:
    Graph(): autoIId(0), nEdges(0), nodeM() {}
    Graph(int& n): autoIId(n), nEdges(0), nodeM() {}
    Graph(Graph& g): autoIId(g.autoIId), nEdges(g.nEdges), nodeM(g.nodeM) {}

    /// Returns the number of nodes.
    int getNodes() const { return nodeM.size(); }
    /// Adds a node with ID `nid` to the graph. Return ID of the node.
    int addNode(int nid = -1);
    /// Adds a node with data `dat` to the graph. Return ID of the node.
    int addNode(NodeData* dat);
    /// Adds a node with ID `nid` and data `dat` to the graph. Return ID of the node.
    int addNode(int nid, NodeData* dat);
    /// Adds a node with ID `node.getId()` to the graph. Return ID of the node.
    int addNode(const T& node);
    /// Adds a node with ID `nid` to the graph and creates edges to it from all nodes in vector `inIdV` and ``outIdV`. Return ID of the node.
    int addNode(int nid, const vector<int>& inIdV, const vector<int>& outIdV);
    /// Deletes node with ID `nid` from the graph.
    void delNode(const int& nid);
    /// Deletes node with ID `node.getId()` from the graph.
    void delNode(const T& node) { delNode(node.getId()); };
    /// Return `true` if ID `nid` is a node.
    bool isNode(const int& nid) const { return nodeM.find(nid) != nodeM.end(); };
    /// Returns an iterator referring to the first node in the graph.
    NodeI<T> beginNI() const { return NodeI<T>{nodeM.begin()}; }
    /// Returns an iterator referring to the past-the-end node in the graph.
    NodeI<T> endNI() const { return NodeI<T>{nodeM.end()}; }
    /// Returns an iterator referring to the node of ID nid in the graph.
    NodeI<T> getNI(const int& nid) const { return NodeI<T>{nodeM.find(nid)}; }

    /// Returns current auto increase id of the graph
    int getAutoIId() { int id(autoIId); autoIId++; return id; }

    /// Returns the number of edges .
    int getEdges() const { return nEdges; };
    /// Adds an edge between node `srcId` and node `dstId` to the graph. Return `true` if add successful
    bool addEdge(const int& srcNId, const int& dstNId);
    /// Adds an edge between node with `srcData` and node with `dstData` to the graph. Return `true` if add successful
    bool addEdge(NodeData* srcData, NodeData* dstData);
    /// Adds an edge between node `srcId` with `srcData` and node `dstId` with `dstData` to the graph. Return `true` if add successful
    bool addEdge(const int& srcNId, NodeData* srcData, const int& dstNId, NodeData* dstData);
    /// Adds an edge between node `srcId` and node `dstId` to the graph. If any of nodes do not exist, create them. Return `true` if add successful
    bool addEdgeUpsert(const int& srcNId, const int& dstNId);
    /// Deletes an edge between node `srcId` and node `dstId` from the graph.
    void delEdge(const int& srcNId, const int& dstNId);
    /// Tests whether an edge between node `srcId` and node `dstId` exists in the graph.
    bool isEdge(const int& srcNId, const int& dstNId);
    /// Returns an iterator referring to the first edge in the graph.
    EdgeI<T> beginEI() const {
        NodeI<T> ni = beginNI();
        EdgeI<T> ei(ni, endNI(), 0);
        if (!isEmpty() && (ni.getOutDeg() == 0 || ni.getId()>ni.getOutNbrNId(0))) {
            ei++;
        }
        return ei;
    }
    /// Returns an iterator referring to the past-the-end edge in the graph.
    EdgeI<T> endEI() const { return EdgeI(endNI(), endNI()); }
    /// Returns an iterator referring to edge (srcNId, dstNId) in the graph.
    EdgeI<T> getEI(const int& srcNId, const int& dstNId) const {
        const NodeI<T> srcNI = getNI(srcNId);
        const int dstIndex = srcNI.getNode().getOutNbrNId(dstNId);
        return EdgeI(srcNI, endNI(), dstIndex);
    };

    /// Gets a vector IDs of all nodes in the graph.
    void getNIdV(vector<int>& idV) const {
        for(auto &it : nodeM) {
            idV.push_back(it.first);
        }
    };

    /// Tests whether the graph is isEmpty.
    bool isEmpty() const { return getNodes() == 0; };
    /// Deletes all nodes and edges from the graph.
    void clear() { return nodeM.clear(); };
    /// Checks the graph data structure for internal consistency.
    virtual bool isOk() const { return false; };
    /// Export the graph to binary type
    void writeBin(ofstream& ws) override;
    /// Export the graph to text type
    void writeTxt(ofstream& ws) override;
    /// Import the graph from binary file
    void readBin(ifstream& rs) override;
    /// Import the graph from text file
    void readTxt(ifstream& rs) override;

    /// Print the graph.
    void print(ostream &os);
};

class UDGraph : public Graph<UDNode> {
public:
    UDGraph(): Graph<UDNode>() {}
    UDGraph(int&n): Graph<UDNode>(n) {}
    UDGraph(UDGraph& udGraph): Graph<UDNode>(udGraph) {}

    /// Checks the graph data structure for internal consistency.
    bool isOk() const override;
};

class DGraph : public Graph<DNode> {
public:
    DGraph(): Graph<DNode>() {}
    DGraph(int&n): Graph<DNode>(n) {}
    DGraph(DGraph& dGraph): Graph<DNode>(dGraph) {}

    /// Checks the graph data structure for internal consistency.
    bool isOk() const override;
};

#include "Graph.tpp"

#endif //BIGGRAPH_GRAPH_H
