//
// Created by Bui Chi Thanh on 25/01/2023.
//

#ifndef BIGGRAPH_NODEDATATYPE_H
#define BIGGRAPH_NODEDATATYPE_H
#include <utility>

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
        string value = Reader::readBinString(rs, "0");
        dat = stoi(value);
    };
    void writeBin(ofstream& ws) override {
        Writer::writeBinString(ws, to_string(dat));
    };

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override {
        dat = Reader::readTxtInt(rs, 0);
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

/// Class for data type `int` in Node.
class NodeDataString : public NodeData {
private:
    string dat;
public:
    NodeDataString(): dat() {};
    NodeDataString(string dat): dat(std::move(dat)) {};

    /// Read and Write Bin.
    void readBin(ifstream& rs) override {
        dat = Reader::readBinString(rs, "");
    };
    void writeBin(ofstream& ws) override {
        Writer::writeBinString(ws, dat);
    };

    /// Read and Write Txt.
    void readTxt(ifstream& rs) override {
        dat = Reader::readTxtString(rs, "");
    };
    void writeTxt(ofstream& ws) override {
        Writer::writeTxtString(ws, dat);
    };

    /// Operator.
    NodeDataString& operator = (const NodeDataString& ni)  { dat = ni.dat; return *this; }

    /// Print console.
    void print(ostream& os) override {
        os << dat;
    }
};

#endif //BIGGRAPH_NODEDATATYPE_H
