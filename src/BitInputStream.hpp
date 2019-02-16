#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    istream & in;
    int nbits;
    unsigned char buf;

public:
    BitInputStream(istream & i);
    bool readBit();
};

#endif // BITINPUTSTREAM_HPP
