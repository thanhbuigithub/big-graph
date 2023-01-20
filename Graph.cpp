//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Graph.h"

int UDGraph::addNode(int nid) {
    if (nid == -1) {
        nid = getAutoIId();
    }
    IAssert(isNode(nid), string_format("node id %d already exists", nid).c_str());
    if (isNode(nid)) {
        autoIId = max(autoIId, nid+1);
        return nid;
    }
    nodeM.insert(pair(nid, UDNode(nid)));
    return nid;
}

int UDGraph::addNode(const UDNode &node) {
    return addNode(node.getId());
}

int UDGraph::addNode(int nid, const vector<int>& idV) {
    if (nid == -1) {
        nid = getAutoIId();
    }
    IAssert(isNode(nid), string_format("node id %d already exists", nid).c_str());
    if (isNode(nid)) {
        autoIId = max(autoIId, nid+1);
        return nid;
    }
    UDNode node = UDNode(nid);
    node.id = nid;
    node.addNbrNIds(idV);
    nEdges += node.getDeg();
    for (int i : idV) {
        getNode(i).addNbrNId(nid);
    }
    return nid;
}

void UDGraph::delNode(const int &nid) {
    IAssert(!isNode(nid), string_format("node id %d does not exists", nid).c_str());
    if (!isNode(nid)) return;
    UDNode& node = getNode(nid);
    for (int e = 0; e < node.getDeg(); e++) {
        const int nbr = node.idV[e];
        if (nbr == nid || !isNode(nbr)) {
            nEdges--;
            continue;
        }
        UDNode& nbrNode = getNode(nbr);
        nbrNode.delNbrNId(nid);
    }
    nodeM.erase(nid);
}

void UDGraph::delNode(const UDNode &node) {
    delNode(node.getId());
}

bool UDGraph::isNode(const int &nid) const {
    return nodeM.find(nid) != nodeM.end();
}

int UDGraph::getEdges() const {
    return nEdges;
}

bool UDGraph::addEdge(const int &srcNId, const int &dstNId) {
    IAssert(!isNode(srcNId) || !isNode(dstNId), string_format("%d or %d not a node.", srcNId, dstNId).c_str());
    if(!isNode(srcNId) || !isNode(dstNId)) return false;
    if (isEdge(srcNId, dstNId)) { return true; } // edge already exists
    getNode(srcNId).addNbrNId(dstNId);
    if (srcNId != dstNId) { // not a self edge
        getNode(dstNId).addNbrNId(srcNId); }
    nEdges++;
    return true; // no edge id
}

bool UDGraph::addEdgeUpsert(const int &srcNId, const int &dstNId) {
    int newSrcNId(srcNId), newDstNId(dstNId);
    if (!isNode(srcNId)) { newSrcNId = addNode(srcNId); }
    if (!isNode(dstNId)) { newDstNId = addNode(dstNId); }
    return addEdge(newSrcNId, newDstNId);
}

void UDGraph::delEdge(const int &srcNId, const int &dstNId) {
    IAssert(!isNode(srcNId) || isNode(dstNId), string_format("%d or %d not a node.", srcNId, dstNId).c_str());
    if (!isNode(srcNId) || isNode(dstNId)) return;
    UDNode &srcNode = getNode(srcNId);
    if (srcNode.isNbrNId(dstNId)) {
        srcNode.delNbrNId(dstNId);
        nEdges--;
    }
    if (srcNId != dstNId) { // not a self edge
        UDNode &dstNode = getNode(dstNId);
        dstNode.delNbrNId(srcNId);
    }
}

bool UDGraph::isEdge(const int &srcNId, const int &dstNId) {
    if (!isNode(srcNId) || !isNode(dstNId)) return false;
    return getNode(srcNId).isNbrNId(dstNId);
}

void UDGraph::getNIdV(vector<int> &idV) const {
    for(auto &it : nodeM) {
        idV.push_back(it.first);
    }
}

bool UDGraph::isEmpty() const {
    return getNodes() == 0;
}

void UDGraph::clear() {
    nodeM.clear();
}

bool UDGraph::isOk() const {
    int isOk = true;
    for(auto &it : nodeM) {
        int nid = it.first;
        UDNode node = it.second;
        IAssert(!node.isSortedNbrNId(), string_format("List neighbor of node %d is not sorted.", nid).c_str());
        if (!node.isSortedNbrNId()) isOk = false;
        for(auto &nbrId : node.idV) {
            if (nbrId == nid) {
                continue;
            }
            IAssert(!isNode(nbrId), string_format("Edge %d --> %d: node %d does not exist.", nid, nbrId).c_str());
            if (isNode(nbrId)) {
            } else isOk = false;
        }
    }
    int edgeCnt = 0;
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) { edgeCnt++; }
    IAssert(edgeCnt != getEdges(), string_format("Number of edges counter is corrupted: GetEdges():%d, EdgeCount:%d.", getEdges(), edgeCnt).c_str());
    if (edgeCnt != getEdges()) isOk = false;

    return isOk;
}

void UDGraph::writeBin(ofstream &ws) {
    Graph::writeBin(ws);
    writeBinInt(ws, getEdges());
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.writeBin(ws);
    }
}

void UDGraph::writeTxt(ofstream &ws) {
    Graph::writeTxt(ws);
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        if (ei != beginEI()) writeTxtChar(ws, "\n");
        ei.writeTxt(ws);
    }
}

void UDGraph::readBin(ifstream &rs) {
    Graph::readBin(rs);
    int size = readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        int srcNId = readBinInt(rs, -1);
        int dstNId = readBinInt(rs, -1);
        addEdgeUpsert(srcNId, dstNId);
    }
}

void UDGraph::readTxt(ifstream &rs) {
    Graph::readTxt(rs);
    while (!rs.eof()) {
        int srcNId = readTxtInt(rs, -1);
        int dstNId = readTxtInt(rs, -1);
        if (srcNId == -1 || dstNId == -1) continue;
        addEdgeUpsert(srcNId, dstNId);
    }
}

void UDGraph::print(ostream &os) const {
    for (EdgeI ei = beginEI(); ei < endEI(); ei++) {
        ei.print(os);
        os << endl;
    }
}
