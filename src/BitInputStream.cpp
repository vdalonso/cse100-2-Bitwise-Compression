#include "BitInputStream.hpp"

// TODO (final) DONE.
// constructor.
BitInputStream::BitInputStream(istream & i) : in(i), nbits(8), buf(0) {}

//nbits goes 0,1,2...8,0,1,2,...
//once all 8 bits of a byte are read, we will get another byte from stream.
//will return 0/1 depending on the bit in position nbits(0-7) (reading from left to right).
bool BitInputStream::readBit() {
    //return false;  // TODO (final)
    if(nbits == 8 ){
	fill();
    }
    unsigned char nextBit = buf >> (7-nbits);
    nextBit = nextBit << 7;
    nbits++;
    
    if(nextBit == 0)
	return 0;
    else
	return 1;
	
}

void BitInputStream::fill() {
	buf = in.get();
	nbytes++;
	//cout << "character read: " << (int)buf << endl;
	//cout << "bytes read: " << nbytes << endl;
	nbits = 0;
}
