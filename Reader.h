//
// Created by Bui Chi Thanh on 17/01/2023.
//

#ifndef BIGGRAPH_READER_H
#define BIGGRAPH_READER_H
#include <fstream>

using namespace std;

class Reader {
public:
    virtual void readBin(ifstream& rs) {};
    virtual void readTxt(ifstream& rs) {};

    static int readBinInt(ifstream& rs, const int& defaultValue);
    static int readTxtInt(ifstream& rs, const int& defaultValue);
};


#endif //BIGGRAPH_READER_H
