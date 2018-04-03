#include "stdafx.h"
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
                printf("RR\n");
				node* A = ptr->nextR();
				node* oldPtr = ptr;
				node* c = ptr->nextL();
				node* p = A->nextL();
				node* e = A->nextR();

				ptr = A;
				ptr->setL(oldPtr);
				ptr->setR(e);
				ptr->setF(oldPtr->prevF());

				oldPtr->setF(ptr);
				oldPtr->setL(c);
				oldPtr->setR(p);

				if (p != nullptr) {
					p->setF(oldPtr);
				}
				if (c != nullptr) {
					c->setF(oldPtr);
				}
				if (e != nullptr) {
					e->setF(ptr);
				}
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
				printf("RL\n");
				node* oldPtr = ptr;
				node* B = ptr->nextR();
				node* A = B->nextL();
				node* g = ptr->nextL();
				node* e = A->nextL();
				node* f = A->nextR();
				node* d = B->nextR();

				ptr = A;
				ptr->setF(oldPtr->prevF());
				ptr->setL(oldPtr);
				ptr->setR(B);

				oldPtr->setF(A);
				oldPtr->setL(g);
				if (g != nullptr) g->setF(oldPtr);
				oldPtr->setR(e);
				if (e != nullptr) e->setF(oldPtr);

				B->setF(A);
				B->setL(f);
				if (f != nullptr)f->setF(B);
				B->setR(d);
				if (d != nullptr)d->setF(B);

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
				printf("LR\n");
				node* oldPtr = ptr;
				node* B = ptr->nextL();
				node* A = B->nextR();
				node* d = B->nextL();
				node* e = A->nextL();
				node* f = A->nextR();
				node* g = ptr->nextR();

				ptr = A;
				ptr->setF(oldPtr->prevF());
				ptr->setL(B);
				ptr->setR(oldPtr);

				B->setF(ptr);
				B->setL(d);
				if (d != nullptr)d->setF(B);
				B->setR(e);
				if (e != nullptr)e->setF(B);

				oldPtr->setF(ptr);
				oldPtr->setL(f);
				if (f != nullptr)f->setF(oldPtr);
				oldPtr->setR(g);
				if (g != nullptr)g->setF(oldPtr);
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
                printf("LL\n");
				node* A = ptr->nextL();
				node* oldPtr = ptr;
				node* c = ptr->nextR();
				node* p = A->nextL();
				node* e = A->nextR();

				ptr = A;
				ptr->setF(oldPtr->prevF());
				ptr->setR(oldPtr);
				ptr->setL(e);
				if (e != nullptr)e->setF(ptr);
				

				oldPtr->setF(ptr);
				oldPtr->setL(p);
				if (p != nullptr)p->setF(ptr);
				oldPtr->setR(c);
				if (c != nullptr)c->setF(ptr);
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

	while (nodeQueue.size() != 0) {
		depthLevel++;
		/*Erase all n depth nodes
		Add all n+1 nodes.		*/
		while (thisDepthCount > 0) {
			ptr = nodeQueue.front();
			if (ptr->nextL() != nullptr) {
				assert(ptr != ptr->nextL());
				nodeQueue.push(ptr->nextL());
			}
			if (ptr->nextR() != nullptr) {
				assert(ptr != ptr->nextR());
				nodeQueue.push(ptr->nextR());
			}
			nodeQueue.pop();
			thisDepthCount--;
		}
		thisDepthCount = nodeQueue.size();
	}
	return depthLevel;
}
