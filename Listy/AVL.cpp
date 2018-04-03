#include "stdafx.h"
#include "AVL.h"
#include <stack>
#include <queue>
#include <algorithm> //for max


void LR(node * & root, node * A)
{
	node* B = A->nextL();
	node* C = B->nextR();
	node* p = A->prevF();

	B->setR(C->nextL());

	A->setL(C->nextR());

	C->setR(A);
	C->setL(B);

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(C);
		else p->setR(C);
	}
	else root = C;
}

void RL(node * & root, node * A)
{
	node* B = A->nextR();
	node* C = B->nextL();
	node* p = A->prevF();

	B->setL(C->nextR());

	A->setR(C->nextL());

	C->setL(A);
	C->setR(B);

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(C);
		else p->setR(C);
	}
	else root = C;
}

void LL(node * & root, node * A)
{
	node* B = A->nextL();
	node* p = A->prevF();

	A->setL(B->nextR());

	B->setF(p);
	B->setR(A);
	A->setF(B);

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(B);
		else p->setR(B);
	}
	else root = B;
}

void RR(node * & root, node * A)
{
	node* B = A->nextR();
	node* p = A->prevF();

	A->setR(B->nextL());

	B->setF(p);
	B->setL(A);
	A->setF(B);

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(B);
		else p->setR(B);
	}
	else root = B;
}


void AVL::rotate(node* iter) {
	while (iter != nullptr) {
		node* anchor = iter->prevF();
		node* ptr = iter;
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
				RR(H, ptr);
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
				RL(H, ptr);
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
				LR(H, ptr);
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
				LL(H, ptr);
			}
		}
		iter = anchor;
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