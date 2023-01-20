//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Node.h"

int UDNode::getDeg() {
    return idV.size();
}

bool UDNode::isNbrNId(const int &nid) {
    return find(idV.begin(), idV.end(), nid) != idV.end();
}

void UDNode::readBin(ifstream &rs) {
    Node::readBin(rs);
    int size = readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.push_back(readBinInt(rs, -1));
    }
}

void UDNode::readTxt(ifstream &rs) {
    Node::readTxt(rs);
    int size = readTxtInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.push_back(readTxtInt(rs, -1));
    }
}

void UDNode::writeBin(ofstream &ws) {
    Node::writeBin(ws);
    writeBinInt(ws, idV.size());
    for (int i : idV) {
        writeBinInt(ws, i);
    }
}

void UDNode::writeTxt(ofstream &ws) {
    Node::writeTxt(ws);
    writeTxtInt(ws, idV.size());
    for (int i : idV) {
        writeTxtInt(ws, i);
    }
}

void UDNode::addNbrNId(const int &nid) {
    idV.push_back(nid);
    sortNbrNId();
}

void UDNode::addNbrNIds(const vector<int> &v) {
    idV.insert(idV.end(), v.begin(), v.end());
    sortNbrNId();
}

void UDNode::delNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(idV.begin(), idV.end(), nid);
    if (i != idV.end()) {
        idV.erase(i);
    }
}

bool UDNode::isSortedNbrNId() const {
    if (idV.size() <= 1) return true;
    for (int i = 0; i < idV.size() - 1; ++i) {
        if (idV[i] > idV[i+1]) return false;
    }
    return true;
}

void UDNode::sortNbrNId() {
    sort(idV.begin(), idV.end());
}

void DNode::readBin(ifstream &rs) {
    Node::readBin(rs);
    int sizeIn = readBinInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.push_back(readBinInt(rs, -1));
    }
    int sizeOut = readBinInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.push_back(readBinInt(rs, -1));
    }
}

void DNode::readTxt(ifstream &rs) {
    Node::readTxt(rs);
    int sizeIn = readTxtInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.push_back(readTxtInt(rs, -1));
    }
    int sizeOut = readTxtInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.push_back(readTxtInt(rs, -1));
    }
}

void DNode::writeBin(ofstream &ws) {
    Node::writeBin(ws);
    writeBinInt(ws, inIdV.size());
    for (int i : inIdV) {
        writeBinInt(ws, i);
    }
    writeBinInt(ws, outIdV.size());
    for (int i : outIdV) {
        writeBinInt(ws, i);
    }
}

void DNode::writeTxt(ofstream &ws) {
    Node::writeTxt(ws);
    writeTxtInt(ws, inIdV.size());
    for (int i : inIdV) {
        writeTxtInt(ws, i);
    }
    writeTxtInt(ws, outIdV.size());
    for (int i : outIdV) {
        writeTxtInt(ws, i);
    }
}

bool DNode::isInNbrNId(const int &nid) {
    return find(inIdV.begin(), inIdV.end(), nid) != inIdV.end();
}

bool DNode::isOutNbrNId(const int &nid) {
    return find(outIdV.begin(), outIdV.end(), nid) != outIdV.end();
}

void DNode::sortInNbrNId() {
    sort(inIdV.begin(), inIdV.end());
}

void DNode::sortOutNbrNId() {
    sort(outIdV.begin(), outIdV.end());
}

bool DNode::isSortedInNbrNId() const {
    if (inIdV.size() <= 1) return true;
    for (int i = 0; i < inIdV.size() - 1; ++i) {
        if (inIdV[i] > inIdV[i+1]) return false;
    }
    return true;
}

bool DNode::isSortedOutNbrNId() const {
    if (outIdV.size() <= 1) return true;
    for (int i = 0; i < outIdV.size() - 1; ++i) {
        if (outIdV[i] > outIdV[i+1]) return false;
    }
    return true;
}

void DNode::addInNbrNId(const int &nid) {
    inIdV.push_back(nid);
    sortInNbrNId();
}

void DNode::addOutNbrNId(const int &nid) {
    outIdV.push_back(nid);
    sortOutNbrNId();
}

void DNode::addInNbrNIds(const vector<int> &v) {
    inIdV.insert(inIdV.end(), v.begin(), v.end());
    sortInNbrNId();
}

void DNode::addOutNbrNIds(const vector<int> &v) {
    outIdV.insert(outIdV.end(), v.begin(), v.end());
    sortOutNbrNId();
}

void DNode::delInNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(inIdV.begin(), inIdV.end(), nid);
    if (i != inIdV.end()) {
        inIdV.erase(i);
    }
}

void DNode::delOutNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(outIdV.begin(), outIdV.end(), nid);
    if (i != outIdV.end()) {
        outIdV.erase(i);
    }
}
