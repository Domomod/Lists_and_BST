#include "AVL.h"
#include <stack>
#include <queue>
#include <algorithm> //for max


void AVL::rotate(node* ptr) {
	while (ptr != nullptr) {
		node* anchor = ptr->prevF();
		if (!isSubTreeAVL(ptr)) {
            printf("\nUpcoming rotation.\n");
			int rrLen = 0;
			int rlLen = 0;
			int lrLen = 0;
			int llLen = 0;

			if (ptr->nextR() != nullptr) {
				rrLen = subTreeLength(ptr->nextR()->nextR());
				rlLen = subTreeLength(ptr->nextR()->nextL());
			}
			if (ptr->nextL() != nullptr) {
				lrLen = subTreeLength(ptr->nextL()->nextR());
				llLen = subTreeLength(ptr->nextL()->nextL());
			}
			int maxLen = std::max(std::max(rrLen, rlLen), std::max(lrLen, llLen));

			
			if (rrLen == maxLen) { /* Right node Right branch */
			/*				|								|
						   ptr								A
						  /   \							  /   \
						 c     A						ptr    e
					    c     / \					   /   \    e
					 |	     p	 e	 		====>	  c     p    e
					 |	  	p	  e	 				 c       p    e
					2|   1|  	   e			
					 |    |			e
			*/
//                printf("RR\n");
				//not nullptr
				node* A = ptr->nextR();
				//maybe nullptr
				node* p = A->nextL();

				A->setF(anchor);
				A->setL(ptr);
				
				//make sure the sub tree is attached to the rest of the tree correctly
				if (ptr == H) {
					H = A;
				}
				else if (anchor != nullptr) {
					if (ptr == anchor->nextR()) {
						anchor->setR(A);
					}
					else {
						anchor->setL(A);
					}
				}

				ptr->setF(A);
				ptr->setR(p);
			}
			else if (rlLen == maxLen) { /* Right node Left branch */
			/*				|								|
						   ptr								A
						  /   \							  /   \
						g      B						ptr	   B
					   g     /  \					    / \	  / \
					 	   A	 d	^		====>	   g   e f   d
						  / \	  d	|				   g   e f   d
					     e   f		|	2			
						e	  f		v
			*/
//                printf("RL\n");
				node* B = ptr->nextR();
				node* A = B->nextL();
				node* e = A->nextL();
				node* f = A->nextR();
				node* g = ptr->nextL();

				A->setF(ptr->prevF());
				A->setL(ptr);
				A->setR(B);
				//make sure the sub tree is attached to the rest of the tree correctly
				if (ptr == H) {
					H = A;
				}
				else if (anchor != nullptr) {
					if (ptr == anchor->nextR()) {
						anchor->setR(A);
					}
					else {
						anchor->setL(A);
					}
				}

				B->setF(A);
				B->setL(f);

				ptr->setF(A);
				ptr->setR(e);	
			}
			else if (lrLen == maxLen) { /* Left node Right branch */
			/*				|								|
						   ptr								A
						  /   \							  /   \
						B      g						 B	  ptr
					  /   \     g					    / \	  / \
					 d	   A		^		====>	   d   e f   g
					d	  / \		|				   d   e f   g
					     e   f		|	2			
						e	  f		v
			*/
//                printf("LR\n");
				//those exist for sure
				node* B = ptr->nextL();
				node* A = B->nextR();
				//those might be nullptrs
				node* e = A->nextL();
				node* f = A->nextR();
				node* g = ptr->nextR();

				A->setF(ptr->prevF());
				A->setR(ptr);
				A->setL(B);
				//make sure the sub tree is attached to the rest of the tree correctly
				if (ptr == H) {
					H = A;
				}
				else if (anchor != nullptr) {
					if (ptr == anchor->nextR()) {
						anchor->setR(A);
					}
					else {
						anchor->setL(A);
					}
				}

				B->setF(A);
				B->setR(e);

				ptr->setF(A);
				ptr->setL(f);	
			}
			else { /* Left node Left branch */
			/*				|								|
						   ptr								A
						  /   \							  /   \
						 A     c					     e    ptr
					    / \     c				        e    /   \
					   e   p 	   |2		====>	   e    p     c
					  e  	p	   |				  e    p       c
					 e    | 	   |  			
					e     |1	   |
			*/
//                printf("LL\n");
				//not nullptr
				node* A = ptr->nextL();
				//maybe nullptr
				node* p = A->nextR();

				A->setF(ptr->prevF());
				A->setR(ptr);
				//make sure the sub tree is attached to the rest of the tree correctly
				if (ptr == H) {
					H = A;
				}
				else if (anchor != nullptr) {
					if (ptr == anchor->nextR()) {
						anchor->setR(A);
					}
					else {
						anchor->setL(A);
					}
				}

				ptr->setF(A);
				ptr->setL(p);
			}
		}
		ptr = ptr->prevF();
	}
}


bool AVL::isSubTreeAVL(node* ptr) {
	if (abs(subTreeLength(ptr->nextL()) - subTreeLength(ptr->nextR()))<=1) {
		return true;
	}
	return false;
}


int AVL::subTreeLength(node* ptr) {
/*	This algorithm is very simple and clever,
at firt we push to the queue root, we will call
it depth 0 node, we add it's children and remove
the root form the queue. Later on we repat this
process, we add the n+1 nodes and remove the n nodes,
where n is their depth.	When we run out of nodes, the
depth we are at is the height of the tree. 

This algorithm was proposed by portal GeeksForGeeks.org*/
	if (ptr == nullptr) {
		return 0;
	}
	int depthLevel = 0;

	std::queue<node *> nodeQueue;
	nodeQueue.push(ptr);

	int thisDepthCount = (int)nodeQueue.size();

	while (thisDepthCount != 0) {
		depthLevel++;
		/*Erase all n depth nodes
		Add all n+1 nodes.		*/
		while (thisDepthCount--) {
			ptr = nodeQueue.front();
			if (ptr->nextL() != nullptr) {
				nodeQueue.push(ptr->nextL());
			}
			if (ptr->nextR() != nullptr) {
				nodeQueue.push(ptr->nextR());
			}
			nodeQueue.pop();
		}
		thisDepthCount = (int)nodeQueue.size();
	}
	return depthLevel;
}
