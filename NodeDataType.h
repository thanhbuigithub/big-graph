//
// Created by Bui Chi Thanh on 25/01/2023.
//

#ifndef BIGGRAPH_NODEDATATYPE_H
#define BIGGRAPH_NODEDATATYPE_H
#include "Node.h"

/// Class for data type `int` in Node.
class NodeDataInt : public NodeData {
private:
    int dat;
public:
    NodeDataInt(): dat() {};
    NodeDataInt(const int& dat): dat(dat) {};

    /// Read and Write Bin.
    void readBin(ifstream& rs) override {
        Reader::readBinInt(rs, 0);
    };
    void writeBin(ofstream& ws) override {
        Writer::writeBinInt(ws, dat);
    };

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override {
        Reader::readTxtInt(rs, 0);
    };
    void writeTxt(ofstream& ws) override {
        Writer::writeTxtInt(ws, dat);
    };

    /// Operator.
    NodeDataInt& operator = (const NodeDataInt& ni)  { dat = ni.dat; return *this; }

    /// Print console.
    void print(ostream& os) override {
        os << dat;
    }
};

#endif //BIGGRAPH_NODEDATATYPE_H
