#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    istream & in;
    int nbits;
    unsigned char buf;
    unsigned int nbytes;

    void fill();

public:
    BitInputStream(istream & i);
    bool readBit();
};

#endif // BITINPUTSTREAM_HPP
