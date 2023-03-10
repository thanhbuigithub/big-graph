//
// Created by Bui Chi Thanh on 15/01/2023.
//

#ifndef BIGGRAPH_EDGE_H
#define BIGGRAPH_EDGE_H

#include "Node.h"

template<class T>
class EdgeI : Writer {
private:
    typedef NodeI<T> NodeI;
    NodeI curNodeI, endNodeI;
    int curEdge;
public:
    EdgeI() : curNodeI(), endNodeI(), curEdge(0) { }
    EdgeI(const NodeI& nodeI, const NodeI& endNodeI, const int& edgeN=0) : curNodeI(nodeI), endNodeI(endNodeI), curEdge(edgeN) { }
    EdgeI(const EdgeI& EdgeI) : curNodeI(EdgeI.curNodeI), endNodeI(EdgeI.endNodeI), curEdge(EdgeI.curEdge) { }

    EdgeI& operator = (const EdgeI& it) { if (this!=&it) { curNodeI=it.curNodeI; endNodeI=it.endNodeI; curEdge=it.curEdge; } return *this; }

    /// Increment iterator.
    EdgeI& operator++ (int) {
        return *this;
    }

    bool operator < (const EdgeI& it) const {
        return curNodeI < it.curNodeI || (curNodeI == it.curNodeI && curEdge < it.curEdge);
    }
    bool operator == (const EdgeI& it) const {
        return curNodeI == it.curNodeI && curEdge == it.curEdge;
    }
    bool operator != (const EdgeI& it) const {
        return !(*this == it);
    }

    /// Returns the source of the edge. Since the graph is undirected, this is the node with a smaller ID of the edge endpoints.
    int getSrcNId() const { return curNodeI.getId(); }
    /// Returns the destination of the edge. Since the graph is undirected, this is the node with a greater ID of the edge endpoints.
    int getDstNId() const { return curNodeI.getOutNbrNId(curEdge); }

    void writeBin(ofstream &ws) override {
        writeBinInt(ws, getSrcNId());
        writeBinInt(ws, getDstNId());
    }
    void writeTxt(ofstream &ws) override {
        writeTxtInt(ws, getSrcNId());
        writeTxtInt(ws, getDstNId(), "\t");
    }
    void print(ostream &os) const {
        os << getSrcNId() << "\t" << getDstNId();
    }
};

template<> class EdgeI<UDNode> : Writer {
private:
    typedef NodeI<UDNode> NodeI;
    NodeI curNodeI, endNodeI;
    int curEdge;
public:
    EdgeI() : curNodeI(), endNodeI(), curEdge(0) { }
    EdgeI(const NodeI& nodeI, const NodeI& endNodeI, const int& edgeN=0) : curNodeI(nodeI), endNodeI(endNodeI), curEdge(edgeN) { }
    EdgeI(const EdgeI& EdgeI) : curNodeI(EdgeI.curNodeI), endNodeI(EdgeI.endNodeI), curEdge(EdgeI.curEdge) { }

    EdgeI& operator = (const EdgeI& it) { if (this!=&it) { curNodeI=it.curNodeI; endNodeI=it.endNodeI; curEdge=it.curEdge; } return *this; }

    /// Increment iterator.
    EdgeI<UDNode>& operator++(int) {
        do {
            curEdge++;
            if (curEdge >= curNodeI.getOutDeg()) {
                curEdge = 0;
                curNodeI++;
                while (curNodeI < endNodeI && curNodeI.getOutDeg()==0) {
                    curNodeI++;
                }
            }
        } while (curNodeI < endNodeI && getSrcNId()>getDstNId());
        return *this;
    }

    bool operator < (const EdgeI& it) const {
        return curNodeI < it.curNodeI || (curNodeI == it.curNodeI && curEdge < it.curEdge);
    }
    bool operator == (const EdgeI& it) const {
        return curNodeI == it.curNodeI && curEdge == it.curEdge;
    }
    bool operator != (const EdgeI& it) const {
        return !(*this == it);
    }

    /// Returns the source of the edge. Since the graph is undirected, this is the node with a smaller ID of the edge endpoints.
    int getSrcNId() const { return curNodeI.getId(); }
    /// Returns the destination of the edge. Since the graph is undirected, this is the node with a greater ID of the edge endpoints.
    int getDstNId() const { return curNodeI.getOutNbrNId(curEdge); }

    void writeBin(ofstream &ws) override {
        writeBinInt(ws, getSrcNId());
        writeBinInt(ws, getDstNId());
    }
    void writeTxt(ofstream &ws) override {
        writeTxtInt(ws, getSrcNId());
        writeTxtInt(ws, getDstNId(), "\t");
    }
    void print(ostream &os) const {
        os << getSrcNId() << "\t" << getDstNId();
    }
};

template<> class EdgeI<DNode> : Writer {
private:
    typedef NodeI<DNode> NodeI;
    NodeI curNodeI, endNodeI;
    int curEdge;
public:
    EdgeI() : curNodeI(), endNodeI(), curEdge(0) { }
    EdgeI(const NodeI& nodeI, const NodeI& endNodeI, const int& edgeN=0) : curNodeI(nodeI), endNodeI(endNodeI), curEdge(edgeN) { }
    EdgeI(const EdgeI& EdgeI) : curNodeI(EdgeI.curNodeI), endNodeI(EdgeI.endNodeI), curEdge(EdgeI.curEdge) { }

    EdgeI& operator = (const EdgeI& it) { if (this!=&it) { curNodeI=it.curNodeI; endNodeI=it.endNodeI; curEdge=it.curEdge; } return *this; }

    /// Increment iterator.
    EdgeI<DNode>& operator++(int) {
        curEdge++;
        if (curEdge >= curNodeI.getOutDeg()) {
            curEdge = 0;
            curNodeI++;
            while (curNodeI < endNodeI && curNodeI.getOutDeg()==0) {
                curNodeI++;
            }
        }
        return *this;
    }

    bool operator < (const EdgeI& it) const {
        return curNodeI < it.curNodeI || (curNodeI == it.curNodeI && curEdge < it.curEdge);
    }
    bool operator == (const EdgeI& it) const {
        return curNodeI == it.curNodeI && curEdge == it.curEdge;
    }
    bool operator != (const EdgeI& it) const {
        return !(*this == it);
    }

    /// Returns the source of the edge. Since the graph is undirected, this is the node with a smaller ID of the edge endpoints.
    int getSrcNId() const { return curNodeI.getId(); }
    /// Returns the destination of the edge. Since the graph is undirected, this is the node with a greater ID of the edge endpoints.
    int getDstNId() const { return curNodeI.getOutNbrNId(curEdge); }

    void writeBin(ofstream &ws) override {
        writeBinInt(ws, getSrcNId());
        writeBinInt(ws, getDstNId());
    }
    void writeTxt(ofstream &ws) override {
        writeTxtInt(ws, getSrcNId());
        writeTxtInt(ws, getDstNId(), "\t");
    }
    void print(ostream &os) const {
        os << getSrcNId() << "\t" << getDstNId();
    }
};

#endif //BIGGRAPH_EDGE_H
