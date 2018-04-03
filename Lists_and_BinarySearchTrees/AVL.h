#pragma once
#include "node.h"
#include "BST.h"
class AVL : public BST
{
public:
	AVL() {
		H = nullptr;
	
	//H.setVal(v);
	}
	void rotate(node* ptr);

	static int subTreeLength(node* ptr);
	static bool isSubTreeAVL(node* ptr);
};
