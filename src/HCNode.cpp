#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically:
 *  give higher priority to the one with the smaller symbol (viewing the symbol as an integer
 *  from 0 to 255).
 */
bool HCNode::operator<(const HCNode& other) {
    //return false;  TODO (checkpoint)
    //case where this instances' count is lower ie: has higher priority
    if (this->count < other.count)
	return false;
    //case where the other HCNodes' count is lower ie: has higher priority
    else if (other.count < this->count)
	return true;
    //case where their count is tied. Compare their symbol/symbol/char
    //if this instances' symbol is smaller, give it priority. Else, give it to the other.
    else{
	if(this->symbol < other.symbol)
		return false;
	else
		return true;
    }
}
