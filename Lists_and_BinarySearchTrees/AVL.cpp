#include "stdafx.h"
#include "AVL.h"
#include <stack>
#include <queue>
#include <algorithm> //for max


void LR(node * & root, node * & A)
{
	//printf("LR");
	node* B = A->nextL();
	node* C = B->nextR();
	node* p = A->prevF();

	B->setR(C->nextL());

	A->setL(C->nextR());

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(C);
		else p->setR(C);
	}
	else root = C;

	C->setR(A);
	C->setL(B);
	C->setF(p);

	if (A != nullptr && B != nullptr) {
		if (A->getHeight() > B->getHeight()) {
			A->updateHeight();
			B->updateHeight();
		}
		else {
			B->updateHeight();
			A->updateHeight();
		}
	}
	else if (A != nullptr)
		A->updateHeight();
	else if (B != nullptr)
		B->updateHeight();
}


void RL(node * & root, node * & A)
{
	//printf("RL");
	node* B = A->nextR();
	node* C = B->nextL();
	node* p = A->prevF();

	B->setL(C->nextR());

	A->setR(C->nextL());

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(C);
		else p->setR(C);
	}
	else root = C;

	C->setL(A);
	C->setR(B);
	C->setF(p);

	if (A != nullptr && B != nullptr) {
		if (A->getHeight() > B->getHeight()) {
			A->updateHeight();
			B->updateHeight();
		}
		else {
			B->updateHeight();
			A->updateHeight();
		}
	}
	else if (A != nullptr)
		A->updateHeight();
	else if (B != nullptr)
		B->updateHeight();
}


void LL(node * & root, node * & A)
{
	//printf("LL");
	node* B = A->nextL();
	node* p = A->prevF();

	A->setL(B->nextR());

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(B);
		else p->setR(B);
	}
	else root = B;

	B->setF(p);
	B->setR(A);
	A->setF(B);

	A->updateHeight();
	B->updateHeight();

}


void RR(node * & root, node * & A)
{
	//printf("RR");
	node* B = A->nextR();
	node* p = A->prevF();

	A->setR(B->nextL());

	if (p != nullptr)
	{
		if (p->nextL() == A) p->setL(B);
		else p->setR(B);
	}
	else root = B;

	B->setF(p);
	B->setL(A);
	A->setF(B);

	A->updateHeight();
	B->updateHeight();
	if (p != nullptr)
		p->updateHeight();
}


void AVL::rotate(node* & iter) {
	while (iter != nullptr) {
		node* anchor = iter->prevF();
		node* ptr = iter;
		if (!isSubTreeAVL(ptr)) {

			//printf("%d\n", ptr->getHeight());
			if (ptr->getBalanceFactor() > 1) {

				int temp = 0;
				if (ptr->nextR() != nullptr)
					temp = ptr->nextR()->getBalanceFactor();
				if (temp > 0)
					RR(H, ptr);
				else
					RL(H, ptr);
			}
			else if (ptr->getBalanceFactor() < -1) {
				int temp = 0;
				if (ptr->nextL() != nullptr)
					temp = ptr->nextL()->getBalanceFactor();
				if (temp > 0)
					LR(H, ptr);
				else
					LL(H, ptr);
			}
		}
		iter = anchor;
	}
}


bool AVL::isSubTreeAVL(node* ptr) {
	if (abs(ptr->getBalanceFactor())<2) {
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