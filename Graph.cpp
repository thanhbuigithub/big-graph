//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Graph.h"

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