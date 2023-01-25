//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Graph.h"
#include "iostream"
bool UDGraph::isOk() const {
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
    for (EdgeI ei = this->beginEI(); ei < this->endEI(); ei++) {
        edgeCnt++;
    }
    IAssert(edgeCnt != this->getEdges(), string_format("Number of edges counter is corrupted: GetEdges():%d, EdgeCount:%d.", this->getEdges(), edgeCnt).c_str());
    if (edgeCnt != this->getEdges()) isOk = false;

    return isOk;
}

bool DGraph::isOk() const {
    int isOk = true;
    for(auto &it : this->nodeM) {
        int nid = it.first;
        DNode node = it.second;
        IAssert(!node.isSortedInNbrNId(), string_format("List in neighbor of node %d is not sorted.", nid).c_str());
        IAssert(!node.isSortedOutNbrNId(), string_format("List out neighbor of node %d is not sorted.", nid).c_str());
        if (!node.isSortedNbrNId() || !node.isSortedOutNbrNId()) isOk = false;
        for(auto &nbrId : node.getNbrNIds()) {
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
    IAssert(edgeCnt != this->getEdges(), string_format("Number of edges counter is corrupted: getEdges(): %d, edgeCount: %d.", this->getEdges(), edgeCnt).c_str());
    if (edgeCnt != this->getEdges()) isOk = false;

    return isOk;
}