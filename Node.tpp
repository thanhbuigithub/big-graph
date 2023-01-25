//
// Created by Bui Chi Thanh on 15/01/2023.
//

#include "Node.h"

template<class DataType>
int UDNode<DataType>::getDeg() {
    return idV.size();
}

template<class DataType>
bool UDNode<DataType>::isNbrNId(const int &nid) {
    return idV.find(nid) != idV.end();
}

template<class DataType>
void UDNode<DataType>::readBin(ifstream &rs) {
    Node<DataType>::readBin(rs);
    int size = Reader::readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.insert(Reader::readBinInt(rs, -1));
    }
}

template<class DataType>
void UDNode<DataType>::readTxt(ifstream &rs) {
    Node<DataType>::readTxt(rs);
    int size = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.insert(Reader::readTxtInt(rs, -1));
    }
}

template<class DataType>
void UDNode<DataType>::writeBin(ofstream &ws) {
    Node<DataType>::writeBin(ws);
    Writer::writeBinInt(ws, idV.size());
    for (int i : idV) {
        Writer::writeBinInt(ws, i);
    }
}

template<class DataType>
void UDNode<DataType>::writeTxt(ofstream &ws) {
    Node<DataType>::writeTxt(ws);
    Writer::writeTxtInt(ws, idV.size());
    for (int i : idV) {
        Writer::writeTxtInt(ws, i);
    }
}

template<class DataType>
void UDNode<DataType>::addNbrNId(const int &nid) {
    idV.insert(nid);
    sortNbrNId();
}

template<class DataType>
void UDNode<DataType>::addNbrNIds(const vector<int> &v) {
    idV.insert(v.begin(), v.end());
    sortNbrNId();
}

template<class DataType>
void UDNode<DataType>::delNbrNId(const int &nid) {
    idV.erase(nid);
}

template<class DataType>
bool UDNode<DataType>::isSortedNbrNId() const {
    /// Set is always sorted
    return true;
}

template<class DataType>
void UDNode<DataType>::sortNbrNId() {
    /// Set is always sorted -> do nothing
}

template<class DataType>
void DNode<DataType>::readBin(ifstream &rs) {
    Node<DataType>::readBin(rs);
    int sizeIn = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.insert(Reader::readBinInt(rs, -1));
    }
    int sizeOut = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.insert(Reader::readBinInt(rs, -1));
    }
}

template<class DataType>
void DNode<DataType>::readTxt(ifstream &rs) {
    Node<DataType>::readTxt(rs);
    int sizeIn = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.insert(Reader::readTxtInt(rs, -1));
    }
    int sizeOut = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.insert(Reader::readTxtInt(rs, -1));
    }
}

template<class DataType>
void DNode<DataType>::writeBin(ofstream &ws) {
    Node<DataType>::writeBin(ws);
    Writer::writeBinInt(ws, inIdV.size());
    for (int i : inIdV) {
        Writer::writeBinInt(ws, i);
    }
    Writer::writeBinInt(ws, outIdV.size());
    for (int i : outIdV) {
        Writer::writeBinInt(ws, i);
    }
}

template<class DataType>
void DNode<DataType>::writeTxt(ofstream &ws) {
    Node<DataType>::writeTxt(ws);
    Writer::writeTxtInt(ws, inIdV.size());
    for (int i : inIdV) {
        Writer::writeTxtInt(ws, i);
    }
    Writer::writeTxtInt(ws, outIdV.size());
    for (int i : outIdV) {
        Writer::writeTxtInt(ws, i);
    }
}

template<class DataType>
bool DNode<DataType>::isInNbrNId(const int &nid) {
    return inIdV.find(nid) != inIdV.end();
}

template<class DataType>
bool DNode<DataType>::isOutNbrNId(const int &nid) {
    return outIdV.find(nid) != outIdV.end();
}

template<class DataType>
void DNode<DataType>::sortInNbrNId() {
    /// Set is always sorted -> do nothing
}

template<class DataType>
void DNode<DataType>::sortOutNbrNId() {
    /// Set is always sorted -> do nothing
}

template<class DataType>
bool DNode<DataType>::isSortedInNbrNId() const {
    /// Set is always sorted
    return true;
}

template<class DataType>
bool DNode<DataType>::isSortedOutNbrNId() const {
    /// Set is always sorted
    return true;
}

template<class DataType>
void DNode<DataType>::addInNbrNId(const int &nid) {
    inIdV.insert(nid);
    sortInNbrNId();
}

template<class DataType>
void DNode<DataType>::addOutNbrNId(const int &nid) {
    outIdV.insert(nid);
    sortOutNbrNId();
}

template<class DataType>
void DNode<DataType>::addInNbrNIds(const vector<int> &v) {
    inIdV.insert(v.begin(), v.end());
    sortInNbrNId();
}

template<class DataType>
void DNode<DataType>::addOutNbrNIds(const vector<int> &v) {
    outIdV.insert(v.begin(), v.end());
    sortOutNbrNId();
}

template<class DataType>
void DNode<DataType>::delInNbrNId(const int &nid) {
    inIdV.erase(nid);
}

template<class DataType>
void DNode<DataType>::delOutNbrNId(const int &nid) {
    outIdV.erase(nid);
}
