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
    return find(idV.begin(), idV.end(), nid) != idV.end();
}

template<class DataType>
void UDNode<DataType>::readBin(ifstream &rs) {
    Node<DataType>::readBin(rs);
    int size = Reader::readBinInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.push_back(Reader::readBinInt(rs, -1));
    }
}

template<class DataType>
void UDNode<DataType>::readTxt(ifstream &rs) {
    Node<DataType>::readTxt(rs);
    int size = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < size; ++i) {
        idV.push_back(Reader::readTxtInt(rs, -1));
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
    idV.push_back(nid);
    sortNbrNId();
}

template<class DataType>
void UDNode<DataType>::addNbrNIds(const vector<int> &v) {
    idV.insert(idV.end(), v.begin(), v.end());
    sortNbrNId();
}

template<class DataType>
void UDNode<DataType>::delNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(idV.begin(), idV.end(), nid);
    if (i != idV.end()) {
        idV.erase(i);
    }
}

template<class DataType>
bool UDNode<DataType>::isSortedNbrNId() const {
    if (idV.size() <= 1) return true;
    for (int i = 0; i < idV.size() - 1; ++i) {
        if (idV[i] > idV[i+1]) return false;
    }
    return true;
}

template<class DataType>
void UDNode<DataType>::sortNbrNId() {
    sort(idV.begin(), idV.end());
}

template<class DataType>
void DNode<DataType>::readBin(ifstream &rs) {
    Node<DataType>::readBin(rs);
    int sizeIn = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.push_back(Reader::readBinInt(rs, -1));
    }
    int sizeOut = Reader::readBinInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.push_back(Reader::readBinInt(rs, -1));
    }
}

template<class DataType>
void DNode<DataType>::readTxt(ifstream &rs) {
    Node<DataType>::readTxt(rs);
    int sizeIn = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeIn; ++i) {
        inIdV.push_back(Reader::readTxtInt(rs, -1));
    }
    int sizeOut = Reader::readTxtInt(rs, 0);
    for (int i = 0; i < sizeOut; ++i) {
        outIdV.push_back(Reader::readTxtInt(rs, -1));
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
    return find(inIdV.begin(), inIdV.end(), nid) != inIdV.end();
}

template<class DataType>
bool DNode<DataType>::isOutNbrNId(const int &nid) {
    return find(outIdV.begin(), outIdV.end(), nid) != outIdV.end();
}

template<class DataType>
void DNode<DataType>::sortInNbrNId() {
    sort(inIdV.begin(), inIdV.end());
}

template<class DataType>
void DNode<DataType>::sortOutNbrNId() {
    sort(outIdV.begin(), outIdV.end());
}

template<class DataType>
bool DNode<DataType>::isSortedInNbrNId() const {
    if (inIdV.size() <= 1) return true;
    for (int i = 0; i < inIdV.size() - 1; ++i) {
        if (inIdV[i] > inIdV[i+1]) return false;
    }
    return true;
}

template<class DataType>
bool DNode<DataType>::isSortedOutNbrNId() const {
    if (outIdV.size() <= 1) return true;
    for (int i = 0; i < outIdV.size() - 1; ++i) {
        if (outIdV[i] > outIdV[i+1]) return false;
    }
    return true;
}

template<class DataType>
void DNode<DataType>::addInNbrNId(const int &nid) {
    inIdV.push_back(nid);
    sortInNbrNId();
}

template<class DataType>
void DNode<DataType>::addOutNbrNId(const int &nid) {
    outIdV.push_back(nid);
    sortOutNbrNId();
}

template<class DataType>
void DNode<DataType>::addInNbrNIds(const vector<int> &v) {
    inIdV.insert(inIdV.end(), v.begin(), v.end());
    sortInNbrNId();
}

template<class DataType>
void DNode<DataType>::addOutNbrNIds(const vector<int> &v) {
    outIdV.insert(outIdV.end(), v.begin(), v.end());
    sortOutNbrNId();
}

template<class DataType>
void DNode<DataType>::delInNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(inIdV.begin(), inIdV.end(), nid);
    if (i != inIdV.end()) {
        inIdV.erase(i);
    }
}

template<class DataType>
void DNode<DataType>::delOutNbrNId(const int &nid) {
    __wrap_iter<int*> i = find(outIdV.begin(), outIdV.end(), nid);
    if (i != outIdV.end()) {
        outIdV.erase(i);
    }
}
