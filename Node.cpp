//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Node.h"

int UDNode::getDeg() {
    return idV.size();
}

bool UDNode::isNbrNId(const int &nid) {
    return idV.find(nid) != idV.end();
}

void UDNode::readBin(ifstream &rs) {
    Node::readBin(rs);
    int size = Reader::readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.insert(Reader::readBinInt(rs, -1));
    }
}

void UDNode::readTxt(ifstream &rs) {
    Node::readTxt(rs);
    int size = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.insert(Reader::readTxtInt(rs, -1));
    }
}

void UDNode::writeBin(ofstream &ws) {
    Node::writeBin(ws);
    Writer::writeBinInt(ws, idV.size());
    for (int i : idV) {
        Writer::writeBinInt(ws, i);
    }
}

void UDNode::writeTxt(ofstream &ws) {
    Node::writeTxt(ws);
    Writer::writeTxtInt(ws, idV.size());
    for (int i : idV) {
        Writer::writeTxtInt(ws, i);
    }
}

void UDNode::addNbrNId(const int &nid) {
    idV.insert(nid);
    sortNbrNId();
}

void UDNode::addNbrNIds(const vector<int> &v) {
    idV.insert(v.begin(), v.end());
    sortNbrNId();
}

void UDNode::delNbrNId(const int &nid) {
    idV.erase(nid);
}

bool UDNode::isSortedNbrNId() const {
    /// Set is always sorted
    return true;
}

void UDNode::sortNbrNId() {
    /// Set is always sorted -> do nothing
}

void DNode::readBin(ifstream &rs) {
    Node::readBin(rs);
    int sizeIn = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.insert(Reader::readBinInt(rs, -1));
    }
    int sizeOut = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.insert(Reader::readBinInt(rs, -1));
    }
}

void DNode::readTxt(ifstream &rs) {
    Node::readTxt(rs);
    int sizeIn = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.insert(Reader::readTxtInt(rs, -1));
    }
    int sizeOut = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.insert(Reader::readTxtInt(rs, -1));
    }
}

void DNode::writeBin(ofstream &ws) {
    Node::writeBin(ws);
    Writer::writeBinInt(ws, inIdV.size());
    for (int i : inIdV) {
        Writer::writeBinInt(ws, i);
    }
    Writer::writeBinInt(ws, outIdV.size());
    for (int i : outIdV) {
        Writer::writeBinInt(ws, i);
    }
}

void DNode::writeTxt(ofstream &ws) {
    Node::writeTxt(ws);
    Writer::writeTxtInt(ws, inIdV.size());
    for (int i : inIdV) {
        Writer::writeTxtInt(ws, i);
    }
    Writer::writeTxtInt(ws, outIdV.size());
    for (int i : outIdV) {
        Writer::writeTxtInt(ws, i);
    }
}

bool DNode::isInNbrNId(const int &nid) {
    return inIdV.find(nid) != inIdV.end();
}

bool DNode::isOutNbrNId(const int &nid) {
    return outIdV.find(nid) != outIdV.end();
}

void DNode::sortInNbrNId() {
    /// Set is always sorted -> do nothing
}

void DNode::sortOutNbrNId() {
    /// Set is always sorted -> do nothing
}

bool DNode::isSortedInNbrNId() const {
    /// Set is always sorted
    return true;
}

bool DNode::isSortedOutNbrNId() const {
    /// Set is always sorted
    return true;
}

void DNode::addInNbrNId(const int &nid) {
    inIdV.insert(nid);
    sortInNbrNId();
}

void DNode::addOutNbrNId(const int &nid) {
    outIdV.insert(nid);
    sortOutNbrNId();
}

void DNode::addInNbrNIds(const vector<int> &v) {
    inIdV.insert(v.begin(), v.end());
    sortInNbrNId();
}

void DNode::addOutNbrNIds(const vector<int> &v) {
    outIdV.insert(v.begin(), v.end());
    sortOutNbrNId();
}

void DNode::delInNbrNId(const int &nid) {
    inIdV.erase(nid);
}

void DNode::delOutNbrNId(const int &nid) {
    outIdV.erase(nid);
}