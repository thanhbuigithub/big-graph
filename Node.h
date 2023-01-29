//
// Created by Bui Chi Thanh on 15/01/2023.
//

#ifndef BIGGRAPH_NODE_H
#define BIGGRAPH_NODE_H
#include <vector>
#include <map>
#include <set>
#include "Reader.h"
#include "Writer.h"
#include "Define.h"

using namespace std;

/// Abstract class for data in Node.
class NodeData {
public:
    /// Read and Write Bin.
    virtual void readBin(ifstream& rs) = 0;
    virtual void writeBin(ofstream& ws) = 0;

    /// Read and Write Txt.
    virtual void readTxt(ifstream& rs) = 0;
    virtual void writeTxt(ofstream& ws) = 0;

    /// Print console.
    virtual void print(ostream& os) = 0;
};

class Node : public Reader, public Writer {
protected:
    int id;
    NodeData* dat;

public:
    /// Constructor.
    Node(): id(-1), dat(nullptr) {}
    Node(const int& id): id(id), dat(nullptr) {}
    Node(const int& id, NodeData* dat): id(id), dat(dat) {}
    Node(NodeData* dat): id(-1), dat(dat) {}
    Node(Node* node): id(node->id), dat(node->dat) {}

    /// Id.
    int getId() const { return id; }

    /// Data.
    NodeData* getData() const { return dat; }
    void setData(NodeData* data) { dat = data; }

    /// Degree.
    virtual int getDeg() { return 0; };
    virtual int getInDeg() { return 0; };
    virtual int getOutDeg() { return 0; };

    /// Get neighbor node.
    virtual int getNbrNId(const int& index) { return -1; };
    virtual int getInNbrNId(const int& index) { return -1; };
    virtual int getOutNbrNId(const int& index) { return -1; };
    virtual vector<int> getNbrNIds() { return {}; }

    /// Get neighbor index nth in node with ID `nid`.
    virtual int getNbrIndex(const int& nid) { return -1; };
    virtual int getInNbrIndex(const int& nid) { return -1; };
    virtual int getOutNbrIndex(const int& nid) { return -1; };

    /// Check if a node with ID `node.id` is neighbor.
    bool isNbr(const Node& node) { return isNbrNId(node.id); };
    bool isInNbr(const Node& node) { return isInNbrNId(node.id); };
    bool isOutNbr(const Node& node) { return isOutNbrNId(node.id); };

    /// Check if a node with ID `nid` is neighbor node.
    virtual bool isNbrNId(const int& nid) { return false; };
    virtual bool isInNbrNId(const int& nid) { return false; };
    virtual bool isOutNbrNId(const int& nid) { return false; };

    /// Sort vector of neighbor node.
    virtual void sortNbrNId() {};
    virtual void sortInNbrNId() {};
    virtual void sortOutNbrNId() {};

    /// Check if vector of neighbor node is sorted.
    virtual bool isSortedNbrNId() const { return false; };
    virtual bool isSortedInNbrNId() const { return false; };
    virtual bool isSortedOutNbrNId() const { return false; };

    /// Add a neighbor node.
    virtual void addNbrNId(const int& nid) {};
    virtual void addInNbrNId(const int& nid) {};
    virtual void addOutNbrNId(const int& nid) {};

    /// Add a vector of neighbor node.
    virtual void addNbrNIds(const vector<int>& v) {};
    virtual void addInNbrNIds(const vector<int>& v) {};
    virtual void addOutNbrNIds(const vector<int>& v) {};

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
};

class UDNode : public Node {
public:
    /// Vector of neighbor node id.
    set<int> idV;

    /// Constructor.
    UDNode(): Node(), idV() {}
    UDNode(const int& id): Node(id), idV() {}
    UDNode(const int& id, NodeData* data): Node(id, data), idV() {}
    UDNode(NodeData* data): Node(data), idV() {}
    UDNode(Node* node): Node(node->getId()), idV() {}
    UDNode(UDNode* udNode): Node(udNode->id), idV(udNode->idV) {}

    /// Degree.
    int getDeg() override;
    int getInDeg() override { return getDeg(); };
    int getOutDeg() override { return getDeg(); };

    /// Get neighbor node.
    int getNbrNId(const int& index) override {
        if (index < idV.size()) {
            auto it = idV.begin();
            std::advance(it, index);
            return *it;
        }
        return -1;
    }
    int getInNbrNId(const int& index) override { return getNbrNId(index); }
    int getOutNbrNId(const int& index) override { return getNbrNId(index); }
    vector<int> getNbrNIds() override {
        vector<int> v;
        copy(idV.begin(), idV.end(), v.begin());
        return v;
    }

    /// Get neighbor index nth in node with ID `nid`.
    int getNbrIndex(const int& nid) override {
        auto it1 = idV.find(nid);
        return distance(idV.begin(), it1);
    };
    int getInNbrIndex(const int& nid) override { return getNbrIndex(nid); };
    int getOutNbrIndex(const int& nid) override { return getNbrIndex(nid); };

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
};

class DNode : public Node {
public:
    /// Vector of in node ids and out node ids.
    set<int> inIdV, outIdV;

    /// Constructor
    DNode(): Node(), inIdV(), outIdV() {}
    DNode(const int& id): Node(id), inIdV(), outIdV() {}
    DNode(const int& id, NodeData* data): Node(id, data), inIdV(), outIdV() {}
    DNode(NodeData* data): Node(data), inIdV(), outIdV() {}
    DNode(Node* node): Node(node->getId()), inIdV(), outIdV() {}
    DNode(DNode* dNode): Node(dNode->id), inIdV(dNode->inIdV), outIdV(dNode->outIdV) {}

    /// Degree.
    int getDeg() override { return getInDeg() + getOutDeg(); };
    int getInDeg() override { return inIdV.size(); };
    int getOutDeg() override { return outIdV.size(); };

    /// Get neighbor node.
    int getNbrNId(const int& index) override { return index < inIdV.size() ? (getInNbrIndex(index)) : (getOutNbrNId(index)); }
    int getInNbrNId(const int& index) override {
        if (index < inIdV.size()) {
            auto it = inIdV.begin();
            std::advance(it, index);
            return *it;
        }
        return -1;
    }
    int getOutNbrNId(const int& index) override {
        if (index < outIdV.size()) {
            auto it = outIdV.begin();
            std::advance(it, index);
            return *it;
        }
        return -1;
    }
    vector<int> getNbrNIds() override {
        vector<int> v {};
        v.reserve( inIdV.size() + outIdV.size() ); // preallocate memory
        v.insert( v.end(), inIdV.begin(), inIdV.end() );
        v.insert( v.end(), outIdV.begin(), outIdV.end() );
        return v;
    }

    /// Get neighbor index nth in node with ID `nid`.
    int getNbrIndex(const int& nid) override {
        return isInNbrNId(nid) ? getInNbrIndex(nid) : getOutNbrIndex(nid);
    };
    int getInNbrIndex(const int& nid) override {
        auto it = inIdV.find(nid);
        return distance(inIdV.begin(), it);
    };
    int getOutNbrIndex(const int& nid) override {
        auto it = outIdV.find(nid);
        return distance(outIdV.begin(), it);
    };

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
    void addNbrNIds(const vector<int>& v) override { IAssertM("Method `addNbrNIds` don't support for Directed Graph"); };
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
class NodeI : Writer {
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
    bool operator != (const NodeI& ni) const { return nodeMI != ni.nodeMI; }

    /// Returns current node.
    T getNode() const { return nodeMI->second; };
    /// Returns ID of the current node.
    int getId() const { return getNode().getId(); }
    /// Returns ID of the current node.
    NodeData* getData() const { return getNode().getData(); }
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

    void writeBin(ofstream &ws) override {
        writeBinInt(ws, getId());
        getData()->writeBin(ws);
    }
    void writeTxt(ofstream &ws) override {
        writeTxtInt(ws, getId());
        writeTxtChar(ws, ",");
        getData()->writeTxt(ws);
    }
};

#endif //BIGGRAPH_NODE_H
