#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint): DONE!
    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (ASCII)" << endl;

    std::ifstream file;
    file.open(infile , ios::binary);
    vector<int> freq;
    freq.assign(256, 0);

    char c;
    bool empty = 1;
    while (file.get(c)){
//	if(c < 0){
//		continue;
//	}
//	cout << (byte)c << endl;	
	freq[(byte)c]++;
    }

    std::ofstream outf;
    outf.open(outfile , ios::binary);

    //check if infile is empty. if so printout frequencies and exit.
    for(unsigned int j = 0 ; j < freq.size() ; j++){
	if( freq[j] != 0)
		empty = 0;
    }
    if(empty){
	for(unsigned int i = 0; i < freq.size() ; i++)
		outf << freq[i] << endl;	
	return;
    }
	
    HCTree tree;
    tree.build(freq);
    tree.printTree();

    file.clear();
    file.seekg(0);
    //Write the header out
    for(unsigned int i = 0; i < freq.size() ; i++)
	outf << freq[i] << endl;	

    char b;
    while(file.get(b)){
//	if(b >= 0)
		tree.encode((byte)b , outf);
    } 
    file.close();
    outf.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;

    std::ifstream file;
    file.open(infile , ios::in | ios::binary);
    vector<int> freq;
    freq.assign(256, 0);

    char c;
    bool empty = 1;
    while (file.get(c)){
	if(c < 0){
		continue;
	}
	
	freq[(unsigned char) c]++;
    }

    //build the BitOutputStream object to write the header and later on write bits.
    std::ofstream outf;
    outf.open(outfile , ios::binary);
    BitOutputStream out(outf);

    //check if infile is empty. if so simply print the header and exit.
    //for loop runs 256 times. inner for loop runs 16 times per each outer iteration.
    //this whole alg. will write the header bit by bit using out.writebit();
    for(unsigned int i = 0 ; i < freq.size() ; i++){
	if( freq[i] != 0)
		empty = 0;
	for(int j = 31 ; j >= 0 ; j--){
		bool bit = (freq[i] >> j) & 1;
		out.writeBit(bit);
	}

    }
    //NOTE: this flush is here to flush the last 8 bits inside the buf
    //since it wont happen until writeBit is called.
    out.flush();

    //if this file is empty, don't bother building a tree.
    if(empty){
	return;
    }

    //Construction of HC Tree.
    HCTree tree;
    tree.build(freq);
    tree.printTree();

    file.clear();
    file.seekg(0);
    
    //start reading in bytes from the file and do bitwise encoding.
    char b;
    int count = 0;
    while(file.get(b)){
	if(b >= 0)
		tree.encode(b , out);
	count++;
    }
    cout << count << endl; 
    file.close();
    outf.close();

    
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
