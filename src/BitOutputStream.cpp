#include "BitOutputStream.hpp"

// TODO (final) DONE.
// Constructor.
BitOutputStream::BitOutputStream(ostream & o) : out(o), nbits(0) , buf(0) {}

void BitOutputStream::writeBit(bool bit) {
    // TODO (final)
    if(nbits == 8){
	flush();
    }
    //NOTE: must implement the case where there is no more bits to read
    //but there remains some more bits to be flushed (1-7 bits).
    //in this case pad the byte with 0 in the remaining right hand side of the written bits.
    
    //writing from leftmost bit to rightmost.
    if (bit){
	buf = buf << 1;
	buf = buf | 0x01;
    }
    else {
	buf = buf << 1;
	buf = buf | 0x00;
    }
    nbits++;

}

void BitOutputStream::flush() {
    // TODO (final)
    out.put(buf);			//write the buffer to the ostream.
    out.flush();			//flush the ostream.
    buf = 0;				//empty the buffer.
    nbits = 0;				//bitwise buffer is empty, so there are 0 bits inside buffer.
}
