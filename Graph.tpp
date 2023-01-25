//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Graph.h"

template<class T>
int Graph<T>::addNode(int nid) {
    if (nid == -1) {
        nid = getAutoIId();
    }
    IAssert(isNode(nid), string_format("node id %d already exists", nid).c_str());
    if (isNode(nid)) {
        autoIId = max(autoIId, nid+1);
        return nid;
    }
    nodeM.insert(pair(nid, T(nid)));
    return nid;
}

template<class T>
int Graph<T>::addNode(const T &node) {
    return addNode(node.getId());
}

template<class T>
int Graph<T>::addNode(int nid, const vector<int>& inIdV, const vector<int>& outIdV) {
    if (nid == -1) {
        nid = getAutoIId();
    }
    IAssert(isNode(nid), string_format("node id %d already exists", nid).c_str());
    if (isNode(nid)) {
        autoIId = max(autoIId, nid+1);
        return nid;
    }
    T node = T(nid);
    node.id = nid;
    node.addInNbrNIds(inIdV);
    node.addOutNbrNIds(outIdV);
    nEdges += node.getDeg();
    for (int i : inIdV) {
        getNode(i).addOutNbrNIds(nid);
    }
    for (int i : outIdV) {
        getNode(i).addInNbrNIds(nid);
    }
    return nid;
}

template<class T>
void Graph<T>::delNode(const int &nid) {
    IAssert(!isNode(nid), string_format("node id %d does not exists", nid).c_str());
    if (!isNode(nid)) return;
    T& node = getNode(nid);
    for (int nbr : node.getNbrNIds()) {
        if (!isNode(nbr)) continue;
        nEdges--;
        if (nbr == nid) continue;
        T& nbrNode = getNode(nbr);
        nbrNode.delNbrNId(nid);
    }
    nodeM.erase(nid);
}

template<class T>
bool Graph<T>::addEdge(const int &srcNId, const int &dstNId) {
    IAssert(!isNode(srcNId) || !isNode(dstNId), string_format("%d or %d not a node.", srcNId, dstNId).c_str());
    if(!isNode(srcNId) || !isNode(dstNId)) return false;
    if (isEdge(srcNId, dstNId)) { return true; } // edge already exists
    getNode(srcNId).addOutNbrNId(dstNId);
    if (srcNId != dstNId) { // not a self edge
        getNode(dstNId).addInNbrNId(srcNId); }
    nEdges++;
    return true; // no edge id
}

template<class T>
bool Graph<T>::addEdgeUpsert(const int &srcNId, const int &dstNId) {
    int newSrcNId(srcNId), newDstNId(dstNId);
    if (!isNode(srcNId)) { newSrcNId = addNode(srcNId); }
    if (!isNode(dstNId)) { newDstNId = addNode(dstNId); }
    return addEdge(newSrcNId, newDstNId);
}

template<class T>
void Graph<T>::delEdge(const int &srcNId, const int &dstNId) {
    IAssert(!isNode(srcNId) || isNode(dstNId), string_format("%d or %d not a node.", srcNId, dstNId).c_str());
    if (!isNode(srcNId) || isNode(dstNId)) return;
    T &srcNode = getNode(srcNId);
    if (srcNode.isOutNbrNId(dstNId)) {
        srcNode.delOutNbrNId(dstNId);
        nEdges--;
    }
    if (srcNId != dstNId) { // not a self edge
        T &dstNode = getNode(dstNId);
        dstNode.delInNbrNId(srcNId);
    }
}

template<class T>
bool Graph<T>::isEdge(const int &srcNId, const int &dstNId) {
    if (!isNode(srcNId) || !isNode(dstNId)) return false;
    return getNode(srcNId).isOutNbrNId(dstNId);
}

template<class T>
void Graph<T>::writeBin(ofstream &ws) {
    writeBinInt(ws, getEdges());
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.writeBin(ws);
    }
}

template<class T>
void Graph<T>::writeTxt(ofstream &ws) {
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        if (ei != beginEI()) writeTxtChar(ws, "\n");
        ei.writeTxt(ws);
    }
}

template<class T>
void Graph<T>::readBin(ifstream &rs) {
    int size = readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        int srcNId = readBinInt(rs, -1);
        int dstNId = readBinInt(rs, -1);
        addEdgeUpsert(srcNId, dstNId);
    }
}

template<class T>
void Graph<T>::readTxt(ifstream &rs) {
    while (!rs.eof()) {
        int srcNId = readTxtInt(rs, -1);
        int dstNId = readTxtInt(rs, -1);
        if (srcNId == -1 || dstNId == -1) continue;
        addEdgeUpsert(srcNId, dstNId);
    }
}

template<class T>
void Graph<T>::print(ostream &os) {
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.print(os);
        os << endl;
    }
}

template<typename DataType>
bool UDGraph<DataType>::isOk() const {
    int isOk = true;
    for(auto &it : this->nodeM) {
        int nid = it.first;
        UDNode node = it.second;
        IAssert(!node.isSortedNbrNId(), string_format("List neighbor of node %d is not sorted.", nid).c_str());
        if (!node.isSortedNbrNId()) isOk = false;
        for(auto &nbrId : node.idV) {
            if (nbrId == nid) {
                continue;
            }
            IAssert(!this->isNode(nbrId), string_format("Edge %d --> %d: node %d does not exist.", nid, nbrId).c_str());
            if (this->isNode(nbrId)) {
            } else isOk = false;
        }
    }
    int edgeCnt = 0;
    for (EdgeI ei = this->beginEI(); ei < this->endEI(); ei++) { edgeCnt++; }
    IAssert(edgeCnt != this->getEdges(), string_format("Number of edges counter is corrupted: GetEdges():%d, EdgeCount:%d.", this->getEdges(), edgeCnt).c_str());
    if (edgeCnt != this->getEdges()) isOk = false;

    return isOk;
}