//
// Created by Bui Chi Thanh on 15/01/2023.
//

#ifndef BIGGRAPH_NODE_H
#define BIGGRAPH_NODE_H
#include <vector>
#include <map>
#include "Reader.h"
#include "Writer.h"

using namespace std;

class Node : public Reader, public Writer {
protected:
    int id;

public:
    /// Constructor.
    Node(): id(-1) {}
    Node(const int& id): id(id) {}
    Node(const Node& node): id(node.id) {}

    /// Id.
    int getId() const { return id; }

    /// Degree.
    virtual int getDeg() { return 0; };
    virtual int getInDeg() { return 0; };
    virtual int getOutDeg() { return 0; };

    /// Get neighbor node.
    virtual int getNbrNId(const int& index) const { return -1; };
    virtual int getInNbrNId(const int& index) const { return -1; };
    virtual int getOutNbrNId(const int& index) const { return -1; };

    /// Check if a node with ID `node.id` is neighbor.
    bool isNbr(const Node& node) { return isNbrNId(node.id); };
    bool isInNbr(const Node& node) { return isInNbrNId(node.id); };
    bool isOutNbr(const Node& node) { return isOutNbrNId(node.id); };

    /// Check if a node with ID `nid` is neighbor node.
    virtual bool isNbrNId(const int& nid) { return false; };
    virtual bool isInNbrNId(const int& nid) { return false; };
    virtual bool isOutNbrNId(const int& nid) { return false; };

    /// Sort vector of neighbor node.
    virtual void sortNbrNId() = 0;
    virtual void sortInNbrNId() = 0;
    virtual void sortOutNbrNId() = 0;

    /// Check if vector of neighbor node is sorted.
    virtual bool isSortedNbrNId() const { return false; };
    virtual bool isSortedInNbrNId() const { return false; };
    virtual bool isSortedOutNbrNId() const { return false; };

    /// Add a neighbor node.
    virtual void addNbrNId(const int& nid) = 0;
    virtual void addInNbrNId(const int& nid) = 0;
    virtual void addOutNbrNId(const int& nid) = 0;

    /// Add a vector of neighbor node.
    virtual void addNbrNIds(const vector<int>& v) = 0;
    virtual void addInNbrNIds(const vector<int>& v) = 0;
    virtual void addOutNbrNIds(const vector<int>& v) = 0;

    /// Delete a neighbor node.
    virtual void delNbrNId(const int& nid) = 0;
    virtual void delInNbrNId(const int& nid) = 0;
    virtual void delOutNbrNId(const int& nid) = 0;

    /// Read and Write Bin.
    void readBin(ifstream& rs) override { id = readBinInt(rs, -1); }
    void writeBin(ofstream& ws) override { writeBinInt(ws, id); }

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override { id = readTxtInt(rs, -1); }
    void writeTxt(ofstream& ws) override { writeTxtInt(ws, id, ""); }

    /// Print console.
    virtual void print(ostream& os) { os << id; }

    /// Friend class.
    friend class UDNode;
    friend class DNode;
};

class UDNode : public Node {
private:
    /// Vector of neighbor node id.
    vector<int> idV;

public:
    /// Constructor.
    UDNode(): Node(), idV() {}
    UDNode(const int& id): Node(id), idV() {}
    UDNode(const Node& node): Node(node.id), idV() {}
    UDNode(const UDNode& udNode): Node(udNode.id), idV(udNode.idV) {}

    /// Degree.
    int getDeg() override;
    int getInDeg() override { return getDeg(); };
    int getOutDeg() override { return getDeg(); };

    /// Get neighbor node.
    int getNbrNId(const int& index) const override { return index < idV.size() ? idV[index] : -1; }
    int getInNbrNId(const int& index) const override { return getNbrNId(index); }
    int getOutNbrNId(const int& index) const override { return getNbrNId(index); }

    /// Check if a node with ID `nid` is neighbor node.
    bool isNbrNId(const int &nid) override;
    bool isInNbrNId(const int &nid) override { return isNbrNId(nid); };
    bool isOutNbrNId(const int &nid) override { return isNbrNId(nid); };

    /// Sort vector of neighbor node.
    void sortNbrNId() override;
    void sortInNbrNId() override { sortNbrNId(); };
    void sortOutNbrNId() override { sortNbrNId(); };

    /// Check if vector of neighbor node is sorted.
    bool isSortedNbrNId() const override;
    bool isSortedInNbrNId() const override { return isSortedNbrNId(); };
    bool isSortedOutNbrNId() const override { return isSortedNbrNId(); };

    /// Add a neighbor node.
    void addNbrNId(const int& nid) override;
    void addInNbrNId(const int& nid) override { addNbrNId(nid); };
    void addOutNbrNId(const int& nid) override { addNbrNId(nid); };

    /// Add a vector of neighbor node.
    void addNbrNIds(const vector<int>& v) override;
    void addInNbrNIds(const vector<int>& v) override { addNbrNIds(v); };
    void addOutNbrNIds(const vector<int>& v) override { addNbrNIds(v); };

    /// Delete a neighbor node.
    void delNbrNId(const int& nid) override;
    void delInNbrNId(const int& nid) override { delNbrNId(nid); };
    void delOutNbrNId(const int& nid) override { delNbrNId(nid); };

    /// Read and Write Bin.
    void readBin(ifstream& rs) override;
    void writeBin(ofstream& ws) override;

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override;
    void writeTxt(ofstream& ws) override;

    /// Print console.
    void print(ostream &os) override {
        Node::print(os);
        os << " " << idV.size() << endl;
        for (int i : idV) {
            os << i << " ";
        }
    }

    /// Friend Class.
    friend class UDGraph;
};

class DNode : private Node {
private:
    vector<int> inIdV, outIdV;

public:
    /// Constructor
    DNode(): Node(), inIdV(), outIdV() {}
    DNode(const int& id): Node(id), inIdV(), outIdV() {}
    DNode(const Node& node): Node(node.id), inIdV(), outIdV() {}
    DNode(const DNode& dNode): Node(dNode.id), inIdV(dNode.inIdV), outIdV(dNode.outIdV) {}

    /// Degree.
    int getDeg() override { return getInDeg() + getOutDeg(); };
    int getInDeg() override { return inIdV.size(); };
    int getOutDeg() override { return outIdV.size(); };

    /// Get neighbor node.
    int getNbrNId(const int& index) const override { return index < inIdV.size() ? inIdV[index] : (getOutNbrNId(index)); }
    int getInNbrNId(const int& index) const override { return index < inIdV.size() ? inIdV[index] : -1; }
    int getOutNbrNId(const int& index) const override { return index < outIdV.size() ? outIdV[index] : -1; }

    /// Check if a node with ID `nid` is neighbor node.
    bool isNbrNId(const int &nid) override { return isInNbrNId(nid) || isOutNbrNId(nid); };
    bool isInNbrNId(const int &nid) override;
    bool isOutNbrNId(const int &nid) override;

    /// Sort vector of neighbor node.
    void sortNbrNId() override { sortInNbrNId(); sortOutNbrNId(); };
    void sortInNbrNId() override;
    void sortOutNbrNId() override;

    /// Check if vector of neighbor node is sorted.
    bool isSortedNbrNId() const override { return isSortedInNbrNId() && isSortedOutNbrNId(); };
    bool isSortedInNbrNId() const override;
    bool isSortedOutNbrNId() const override;

    /// Add a neighbor node.
    void addNbrNId(const int& nid) override { addInNbrNId(nid); addOutNbrNId(nid); };
    void addInNbrNId(const int& nid) override;
    void addOutNbrNId(const int& nid) override;

    /// Add a vector of neighbor node.
    void addNbrNIds(const vector<int>& v) override { addInNbrNIds(v); addOutNbrNIds(v); };
    void addInNbrNIds(const vector<int>& v) override;
    void addOutNbrNIds(const vector<int>& v) override;

    /// Delete a neighbor node.
    void delNbrNId(const int& nid) override { delInNbrNId(nid); delOutNbrNId(nid); };
    void delInNbrNId(const int& nid) override;
    void delOutNbrNId(const int& nid) override;

    /// Read and Write Bin.
    void readBin(ifstream& rs) override;
    void writeBin(ofstream& ws) override;

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override;
    void writeTxt(ofstream& ws) override;

    /// Print console.
    void print(ostream &os) override {
        Node::print(os);
        os << " " << inIdV.size() << " " << outIdV.size() << endl;
        for (int i : inIdV) {
            os << i << " ";
        }
        for (int i : outIdV) {
            os << i << " ";
        }
    }
};


/// Node iterator. Only forward iteration (operator++) is supported.
template <typename T>
class NodeI {
private:

    typedef typename map<int, T>::const_iterator MapIterator;
    MapIterator nodeMI;
public:
    NodeI() : nodeMI() {}
    NodeI(const MapIterator& it) : nodeMI(it) { }
    NodeI(const NodeI& ni) : nodeMI(ni.nodeMI) { }

    /// Assignment
    NodeI& operator = (const NodeI& ni) { nodeMI = ni.nodeMI; return *this; }

    /// Increment iterator.
    NodeI& operator++ (int) { nodeMI++; return *this; }
    /// Decrement iterator.
    NodeI& operator-- (int) { nodeMI--; return *this; }

    /// Comparison
    bool operator < (const NodeI& ni) const { return std::distance(nodeMI, ni.nodeMI) > 0; }
    bool operator == (const NodeI& ni) const { return nodeMI == ni.nodeMI; }

    /// Returns current node.
    T getNode() const { return nodeMI->second; };
    /// Returns ID of the current node.
    int getId() const { return getNode().getId(); }
    /// Returns degree of the current node.
    int getDeg() const { return getNode().getDeg(); }
    /// Returns in-degree of the current node (returns same as value GetDeg() since the graph is undirected).
    int getInDeg() const { return getNode().getInDeg(); }
    /// Returns out-degree of the current node (returns same as value GetDeg() since the graph is undirected).
    int getOutDeg() const { return getNode().getOutDeg(); }
    /// Sorts vector of neighbor node of the current node.
    void sortNbrNId() { getNode().sortNbrNId(); }
    /// Sorts vector of in neighbor node of the current node.
    void sortInNbrNId() { getNode().sortInNbrNId(); }
    /// Sorts vector of in neighbor node of the current node.
    void sortOutNbrNId() { getNode().sortOutNbrNId(); }
    /// Returns ID of NodeN-th neighboring node.
    int getNbrNId(const int& index) const { return getNode().getNbrNId(index); }
    /// Returns ID of NodeN-th in-node (the node pointing to the current node).
    int getInNbrNId(const int& index) const { return getNode().getInNbrNId(index); }
    /// Returns ID of NodeN-th out-node (the node the current node points to).
    int getOutNbrNId(const int& index) const { return getNode().getOutNbrNId(index); }
    /// Tests whether node with ID NId is a neighbor of the current node.
    bool isNbrNId(const int& nid) const { return getNode().isNbrNId(nid); }
    /// Tests whether node with ID NId points to the current node.
    bool isInNbrNId(const int& nid) const { return getNode().isInNbrNId(nid); }
    /// Tests whether the current node points to node with ID NId.
    bool IsOutNbrNId(const int& nid) const { return getNode().IsOutNbrNId(nid); }

    friend class UDGraph;
};
#endif //BIGGRAPH_NODE_H
