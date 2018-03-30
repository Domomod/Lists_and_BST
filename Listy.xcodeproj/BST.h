#pragma once
#include "node.h"

class BST
{
public:
	BST() {
		H = nullptr;
		//H.setVal(v);
	}

	void addElem(int v);

	void rem(int v);
	void rot();

	void preorder(); //KLP
	void inorder(); //LKP
	void postorder(); //TODO

private:
	node * H;
};
