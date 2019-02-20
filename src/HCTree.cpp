#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    // TODO (checkpoint)
    for(unsigned int i = 0 ; i < leaves.size() ; i++)
	delete leaves[i];
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // TODO (checkpoint) done.
    if (root != nullptr)
	delete this;
    else {
	//cout << freqs[0] <<endl;
	//create a priority_queue, push nodes into them (256).
	std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> nqueue;
	for(unsigned int i = 0; i < freqs.size() ; i++){
		HCNode* n = new HCNode(freqs[i] , char(i) , 0 , 0 , 0);
		//n->count = freqs[i];
		//n->symbol = i;
		nqueue.push(n);
	}
	//EXTRA: print out contents of priority_queue with correct priority!
	//while(!nqueue.empty()){
	//	cout << nqueue.top()->symbol << endl;
	//	nqueue.pop();
	//}
	//NOTE 2/6/19 @ 5:33pm: 
	//implementation of building a tree bottom up is more complicated than i thought.	
	while(nqueue.top()->count == 0)
		nqueue.pop();
	//vector<HCNode*> leaves;
	//leaves.assign(256, nullptr);
	
	//QUESTION: what symbol do i use for the intermediate nodes?
	
	if(nqueue.size() == 1){
		HCNode* single = nqueue.top();
		leaves[int(single->symbol)] = single;
	}
	
	else{
	while(nqueue.size() != 1){
		//cout << "in the while loop \n";
		
		

		HCNode* n1 = nqueue.top();
		nqueue.pop();
		if (leaves[int(n1->symbol)] == nullptr)
			leaves[int(n1->symbol)] = n1;


		HCNode* n0 = nqueue.top();
		nqueue.pop();
		if (leaves[int(n0->symbol)] == nullptr){
			leaves[int(n0->symbol)] = n0;
		}
			
		if(n1->symbol > n0->symbol){
			HCNode* par = new HCNode ( (n1->count + n0->count) , n1->symbol , n1 , n0 , 0 );
			n1->p = n0->p = par;
			nqueue.push(par);

		}
		else{
			HCNode* par = new HCNode ( (n1->count + n0->count) , n0->symbol , n1 , n0 , 0 );
			n1->p = n0->p = par;
			nqueue.push(par);
		}	

	}
	}
	root = nqueue.top();
	//cout << leaves[66]->count << endl;
	//cout << leaves[66]->symbol << endl; 
	//this->printTree();
    }
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint) done.
	//cout << "encoding" << endl;
	string c;
	string one ("1");
	string zero ("0");

	//cout << int(symbol) << endl;
	//cout << leaves[symbol]->symbol <<endl;
	//cout << "--------------------------------------\n";
	HCNode* curr = leaves[symbol];
	//cout << root->symbol << endl;
	//cout << curr->symbol <<endl;

	if(curr->p == nullptr)
		return;	
	while( curr->p != nullptr){
		if(curr == curr->p->c0){
			if(c.empty())
				c = zero;
			else
				c = zero + c;	
		}
		else{
			if(c.empty())
				c = one;
			else
				c = one + c;
		}
		curr = curr->p;
	}
	out << c;	

}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    //return 0;  // TODO (checkpoint) done.
    //still sending a value when we reach the EOF, how do we prevent that??
	char z = '0';
	HCNode * curr = root;
	

	if(in.eof())
		return 0;
	while (curr->c0 != nullptr && curr->c1 != nullptr){
		char c;
		in.get(c);
		//cout << "curent node is: " << curr->symbol << curr->count << endl;
		//cout << c << endl;
		//if ( c == char(-1))
		//	return; 
		if ( c == z)
			curr = curr->c0;
		else
			curr = curr->c1;
	}
	//cout << "symbol getting printed is :" << curr->symbol << endl;
	return curr->symbol;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
	string c;
	string one = ("1");
	string zero = ("0");
	HCNode * curr = leaves[symbol];

	if(curr->p == nullptr)
		return;	
	while( curr->p != nullptr){
		if(curr == curr->p->c0){
			if(c.empty())
				c = zero;
			else
				c = zero + c;	
		}
		else{
			if(c.empty())
				c = one;
			else
				c = one + c;
		}
		curr = curr->p;
	}
	//cout << c << endl;
	//reads the string that represents the encoded symbol and writes them as bits.
	for(unsigned int i = 0; i < c.length() ; i++){
	//cout << "this is the bit in 'c' : " << c[i] << endl;
		if(c[i] == '0'){
			out.writeBit(0);
			//cout << 0;
		}
		else{
			out.writeBit(1);
			//cout << 1;
		}	
	}
	//cout << endl;
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
    return 0;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}

void HCTree::printLeaves(ostream& out) const {
	for(unsigned int j = 0; j < leaves.size() ; j++){
		if(leaves[j] != nullptr){
			out << leaves[j]->count << endl;
		}
		else
			out << "0" << endl;
	}

}
