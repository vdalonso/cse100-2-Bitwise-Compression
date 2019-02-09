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
    //tree.printTree();

    file.clear();
    file.seekg(0);
    //std::ofstream outf;
    //outf.open(outfile , ios::binary);

    for(unsigned int i = 0; i < freq.size() ; i++)
	outf << freq[i] << endl;	

    char b;
    while(file.get(b)){
	if(b >= 0)
		tree.encode(b , outf);
    } 
    file.close();
    outf.close();
   // encodeF.close();
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
