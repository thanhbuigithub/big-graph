//
// Created by Bui Chi Thanh on 17/01/2023.
//

#ifndef BIGGRAPH_READER_H
#define BIGGRAPH_READER_H
#include <fstream>
#include <sstream>

using namespace std;

class Reader {
public:
    virtual void readBin(ifstream& rs) {};
    virtual void readTxt(ifstream& rs) {};

    static int readBinInt(ifstream& rs, const int& defaultValue);
    static int readTxtInt(ifstream& rs, const int& defaultValue);

    static string readBinString(ifstream& rs, string defaultValue);
    static string readTxtString(ifstream& rs, string defaultValue);
};


#endif //BIGGRAPH_READER_H
