#include "stdafx.h"

#include "BST.h"
#include <stack>

void BST::addElem(int v) {
	node* ptr = H;
	node* last = nullptr;

	while (true)
	/*	The loop ends when the first if condition is fulfilled.	*/
	{
		if (ptr == nullptr)
		/*	We have crossed the end of a branch,
		we schould create a new element here.	*/
		{
			ptr = new node;
			ptr->setVal(v);
			if (last != nullptr) {
			/*	We check if the BStree wasn't empty when
			we called addElem(v), if it is empty there is no Father/Root,
			we can't point any pointers to or from him.	*/
				if (*last <= v) {
				/*	Value v is bigger or equal the value of last node,
				we are the right child for last node.	*/
					last->setR(ptr);
					ptr->setF(last);
				}
				else {
				/*	Value v is less than the value of last node,
				we are the left child for last node.	*/
					last->setL(ptr);
					ptr->setF(last);
				}
			}
			else {
				H = ptr;
			}
			printf("creating new elem\n");
			return;
		}
		else if (*ptr <= v) {
		/*	We are pointing on an element that's value is smaller/equal 
		to the value v we go right. */
			last = ptr;

			ptr = ptr->nextR();
			printf("v >= H\n");
		}
		else {
		/*	We are pointing on an element that's value is bigger
		to the value v we go left. */
			last = ptr;
			ptr = ptr->nextL();
			printf("v < H\n");
		}
	}
}

node* BST::search(int v) {
	node* ptr = H;
	while (true)
	{
		if (ptr == nullptr) {
			/*	We have crossed the end of a branch,
			there is no elem with value v, as we would have found it
			if there was one.	*/
			printf("!!!\tWARNING YOU SEARCHED FOR AN NOTEXISTING ELEMENT, I SEND YOU NULLPTR HANDLE IT.\t!!!\n");
			return nullptr;
		}
		else if (*ptr == v) {
			return ptr;
		}
		else if (*ptr < v) {
			ptr = ptr->nextR();
			printf("v >= H\n");
		}
		else {
			ptr = ptr->nextL();
			printf("v < H\n");
		}
	}
}

void BST::removeByPointer(node* ptr){
	printf("%d\t", ptr);
	node* last = ptr->prevF();
	int v = ptr->getVal();
	if (ptr->nextL() == nullptr && ptr->nextR() == nullptr) {
		/*	In this case the elem we seek to delete is a leaf,
		this means it has no children.	*/
		printf("%d was a leaf, I am removing it.\n", v);
		if (last != nullptr) {
			//chech if it's not the root of the BST
			if (*last < v) {
				last->setR(nullptr);
			}
			else {
				last->setL(nullptr);
			}
		}
		delete ptr;
	}
	else if (ptr->nextL() != nullptr && ptr->nextR() != nullptr) {
		/*	Elem we seek to destroy has both children.
		We switch it's position with the smallest child
		in right branch.*/
		node* child = ptr->nextR()->maxLeft();
		ptr->setVal(child->getVal());
		printf("%d had both children, I am replacing it. It's left child is %d.\n", v, ptr->nextL()->getVal());
		removeByPointer(child);
	}
	else if (ptr->nextR() != nullptr) {
		/*	Elem we seek to destroy has right child only.	*/
		if (*last < v) {
			last->setR(ptr->nextR());
		}
		else {
			last->setL(ptr->nextR());
		}
		printf("%d had one child(%d), I am removing it.\n", v, ptr->nextR());
		delete ptr;
	}
	else if (ptr->nextL() != nullptr) {
		/*	Elem we seek to destroy has left child only.	*/
		if (*last < v) {
			last->setR(ptr->nextL());
		}
		else {
			last->setL(ptr->nextL());
		}
		printf("%d had one child(%d), I am removing it.\n", v, ptr->nextL());
		delete ptr;
	}
}

void BST::removeByValue(int v) {
	removeByPointer(search(v));
}


void BST::preorder(){
	if (H == nullptr) {
		return;
	}

	std::stack<node *> nodeStack; 
	nodeStack.push(H);

	while (!nodeStack.empty()) {
	/*	remember that stack is LIFO
	every step you add both children to
	the stack, but handle the left child first,
	further adding it's children to the stack.*/
		node* temp = nodeStack.top();
		printf("%d ", temp->getVal());
		nodeStack.pop();

		if (temp->nextR()!=nullptr) {
			nodeStack.push(temp->nextR());
		}
		if (temp->nextL()!=nullptr) {
			nodeStack.push(temp->nextL());
		}
	}
}


void BST::inorder() {
	if (H == nullptr) {
		return;
	}
	
	node* ptr = H;
	while (ptr->nextL() != nullptr) {

	}
}