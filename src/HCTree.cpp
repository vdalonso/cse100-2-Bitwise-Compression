#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    // TODO (checkpoint)
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // TODO (checkpoint)
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
	while(nqueue.size() != 1){
		HCNode* n1 = nqueue.top();
		nqueue.pop();
		if (leaves[int(n1->symbol)] == nullptr){
			leaves[int(n1->symbol)] = n1;
		}

		HCNode* n0 = nqueue.top();
		nqueue.pop();
		if (leaves[int(n0->symbol)] == nullptr){
			leaves[int(n0->symbol)] = n0;
		}
			
		if(n1->symbol > n0->symbol){
			HCNode* par = new HCNode ( (n1->count + n0->count) , n1->symbol , n0 , n1 , 0 );
			n1->p = n0->p = par;
			nqueue.push(par);

		}
		else{
			HCNode* par = new HCNode ( (n1->count + n0->count) , n0->symbol , n0 , n1 , 0 );
			n1->p = n0->p = par;
			nqueue.push(par);
		}

	}
	root = nqueue.top();
	//cout << leaves[66]->count << endl;
	//cout << leaves[66]->symbol << endl; 
	this->printTree();
    }
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint)
	//cout << "encoding" << endl;
	string c;
	string one ("1");
	string zero ("0");

	//cout << "wwww" << endl;
	HCNode* curr = leaves[symbol];
	//cout << curr->symbol <<endl;
	if(curr->p == nullptr)
		cout << "curr's parent is a nullptr." <<endl;
	
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
    return 0;  // TODO (checkpoint)
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
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
