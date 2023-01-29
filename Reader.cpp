//
// Created by Bui Chi Thanh on 17/01/2023.
//

#include "Reader.h"

int Reader::readBinInt(ifstream &rs, const int &defaultValue) {
    if (!rs || !rs.is_open() || rs.bad()) return defaultValue;
    int value = defaultValue;
    rs.read((char *) &value, sizeof(int));
    return value;
}

int Reader::readTxtInt(ifstream &rs, const int &defaultValue) {
    if (!rs || !rs.is_open() || rs.bad()) return defaultValue;
    int value = defaultValue;
    rs >> value;
    return value;
}

string Reader::readBinString(ifstream &rs, string defaultValue) {
    if (!rs || !rs.is_open() || rs.bad()) return defaultValue;
    int size = 0;
    rs.read((char *) &size, sizeof(int));
    if (size <= 0) return defaultValue;
    ostringstream os;
    char c = 0;
    for (int i = 0; i < size; ++i) {
        rs.read((char *) &c, sizeof(char));
        os << c;
    }
    return os.str();
}

string Reader::readTxtString(ifstream &rs, string defaultValue) {
    if (!rs || !rs.is_open() || rs.bad()) return defaultValue;
    string dat;
    getline(rs, dat);
    return dat;
}
