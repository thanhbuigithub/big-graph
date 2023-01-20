//
// Created by Bui Chi Thanh on 17/01/2023.
//

#include "Writer.h"

bool Writer::writeBinInt(ofstream &ws, const int& value) {
    if (!ws || !ws.is_open() || ws.bad()) return false;
    ws.write((char *) &value, sizeof(int));
    return !ws.bad();
}

bool Writer::writeTxtInt(ofstream &ws, const int& value, const string& delimiter) {
    if (!ws || !ws.is_open() || ws.bad()) return false;
    ws << delimiter << value;
    return !ws.bad();
}

bool Writer::writeTxtChar(ofstream &ws, char const *c) {
    if (!ws || !ws.is_open() || ws.bad()) return false;
    ws << c;
    return !ws.bad();
}
