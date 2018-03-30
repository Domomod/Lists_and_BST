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

	node* search(int v);
	void removeByPointer(node* ptr);
	void removeByValue(int v);
	void rotate();

	void preorder(); //KLP
	void inorder();
	void postorder();

private:
	node * H;
};
