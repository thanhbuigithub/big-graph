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
int Graph<T>::addNode(NodeData* dat) {
    int nid = getAutoIId();
    IAssert(isNode(nid), string_format("Failed to generate auto id. Nid exists: %d", nid).c_str());
    if (!isNode(nid)) {
        nodeM.insert(pair(nid, T(nid, dat)));
    }
    return nid;
}

template<class T>
int Graph<T>::addNode(int nid, NodeData* dat) {
    if (nid == -1) {
        nid = getAutoIId();
    }
    IAssert(isNode(nid), string_format("node id %d already exists", nid).c_str());
    if (isNode(nid)) {
        autoIId = max(autoIId, nid+1);
        return nid;
    }
    nodeM.insert(pair(nid, T(nid, dat)));
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
bool Graph<T>::addEdge(NodeData* srcData, NodeData* dstData) {
    int nidSrc = addNode(srcData);
    int nidDst = addNode(dstData);
    return addEdge(nidSrc, nidDst);
}

template<class T>
bool Graph<T>::addEdge(const int &srcNId, NodeData* srcData, const int &dstNId, NodeData* dstData) {
    T nSrc = getNode(srcNId);
    T nDst = getNode(dstNId);
    nSrc.setData(srcData);
    nDst.setData(dstData);
    return addEdgeUpsert(srcNId, dstNId);
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
    IAssert(!isNode(srcNId) || !isNode(dstNId), string_format("%d or %d not a node.", srcNId, dstNId).c_str());
    if (!isNode(srcNId) || !isNode(dstNId)) return;
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
    writeBinInt(ws, getNodes());
    writeBinInt(ws, getEdges());
    for (NodeI ni = beginNI(); ni < endNI(); ni++) {
        ni.writeBin(ws);
    }
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.writeBin(ws);
    }
}

template<class T>
void Graph<T>::writeTxt(ofstream &ws) {
    writeTxtInt(ws, getNodes());
    writeTxtChar(ws, "\n");
    for (NodeI ni = beginNI(); ni < endNI(); ni++) {
        if (ni != beginNI()) writeTxtChar(ws, "\n");
        ni.writeTxt(ws);
    }
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        writeTxtChar(ws, "\n");
        ei.writeTxt(ws);
    }
}

template<class T>
void Graph<T>::readBin(ifstream &rs) {
    int nodes = readBinInt(rs, 0);
    int edges = readBinInt(rs, 0);
    for (int i = 0; i < nodes; ++i) {
        int id = readBinInt(rs, -1);
        auto data = new NodeDataString();
        data->readBin(rs);
        addNode(id, data);
    }
    for (int i = 0; i < edges; ++i) {
        int srcNId = readBinInt(rs, -1);
        int dstNId = readBinInt(rs, -1);
        addEdge(srcNId, dstNId);
    }
}

template<class T>
void Graph<T>::readTxt(ifstream &rs) {
    int nodes = readTxtInt(rs, 0);
    if (nodes <= 0) return;
    string dat;
    getline(rs, dat);
    char deli;
    for (int i = 0; i < nodes; ++i) {
        int id = readTxtInt(rs, -1);
        IAssert(id < 0, string_format("Node %d has id < 0.", id).c_str());
        if (id < 0) return;
        rs.get(deli);
        auto data = new NodeDataString();
        data->readTxt(rs);
        addNode(id, data);
    }
    while (!rs.eof()) {
        int srcNId = readTxtInt(rs, -1);
        int dstNId = readTxtInt(rs, -1);
        if (srcNId == -1 || dstNId == -1) continue;
        addEdgeUpsert(srcNId, dstNId);
    }
}

template<class T>
void Graph<T>::print(ostream &os) {
    for (NodeI ni = beginNI(); ni < endNI(); ni++) {
        ni.print(os);
        os << endl;
    }
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.print(os);
        os << endl;
    }
}