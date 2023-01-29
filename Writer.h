//
// Created by Bui Chi Thanh on 17/01/2023.
//

#ifndef BIGGRAPH_WRITER_H
#define BIGGRAPH_WRITER_H
#include <fstream>

using namespace std;

class Writer {
public:
    virtual void writeBin(ofstream& ws) {}
    virtual void writeTxt(ofstream& ws) {}

    static bool writeBinInt(ofstream& ws, const int& value);
    static bool writeTxtInt(ofstream& ws, const int& value, const string& delimiter = "");
    static bool writeTxtChar(ofstream& ws, char const *c);

    static bool writeBinString(ofstream& ws, string value);
    static bool writeTxtString(ofstream& ws, string value, const string& delimiter = "");
};


#endif //BIGGRAPH_WRITER_H
