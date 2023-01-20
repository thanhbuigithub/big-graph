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
