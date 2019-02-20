#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (ASCII)" << endl;

     
    std::ifstream file(infile);
    vector<int> freq;
    freq.assign(256 , 0);
    string c;
    //bool empty = 1;
    int count = 0;
    int largest = 0;

    for( int i = 0 ; i < 256 ; i++) {
	getline(file , c);
	int count = stoi(c, nullptr , 10);
	//cout << count << endl;
	freq[i] = count;
    }
    std::ofstream ofile;
    ofile.open(outfile , ios::binary);

    for(unsigned int j = 0; j < freq.size() ; j++){
	if(freq[j] != 0){
		count++;;
		if(freq[j] > freq[largest])
			largest = j;
	}
    }
    if(count <= 1){
	if(count == 0)
		return;
	else if (count == 1){
		//cout << "there si only one symbol in file \n";
		for( int i = 0 ; i < freq[largest] ; i++)
			ofile << (byte)largest;
		return;
	}

    }

    HCTree tree;
    tree.build(freq);



    while(!file.eof()){
	byte x = tree.decode(file);
	if (file.eof())
		break;
	else
		ofile << x ;
    }

}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;

    std::ifstream file(infile);
    vector<int> freq;
    freq.assign(256 , 0);
    string c;
    //bool empty = 1;
    int count = 0;
    int largest = 0;

    BitInputStream in(file);
    
    //inserting the integer values into frequencies vector to build tree.
    for(int i = 0 ; i < 256 ; i++){
	unsigned int symbol = 0;
	for(int j = 31 ; j >= 0 ; j--){
		//unsigned int bit = 0;
		//bit = in.readBit();
		//if (i == 65)
		//	cout << bit;
		freq[i] = freq[i] | (in.readBit() << j);
	}
	//cout << "--------------------------------------------------------------------\n";
	//cout << "count: " << symbol << endl;
    }
//    for(int j = 0; j < freq.size() ;  j++)
//	cout << "symbol number " << j << " apears : " << freq[j] << "  times. \n"; 
    HCTree tree;
    tree.build(freq);
    tree.printTree();

    file.close();


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
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
