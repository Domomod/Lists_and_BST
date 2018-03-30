#include "BST.h"
#include <stack>

void BST::addElem(int v) {
	node* pntr = H;
	node* last = nullptr;

	while (true)
	/*	The loop ends when the first if condition is fulfilled.	*/
	{
		if (pntr == nullptr)
		/*	We have crossed the end of a branch,
		we schould create a new element here.	*/
		{
			pntr = new node;
			pntr->setVal(v);
			if (last != nullptr) {
			/*	We check if the BStree wasn't empty when
			we called addElem(v), if it is empty there is no Father/Root,
			we can't point any pointers to or from him.	*/
				if (*last <= v) {
				/*	Value v is bigger or equal the value of last node,
				we are the right child for last node.	*/
					last->setR(pntr);
					pntr->setF(last);
				}
				else {
				/*	Value v is less than the value of last node,
				we are the left child for last node.	*/
					last->setL(pntr);
					pntr->setF(last);
				}
			}
			else {
				H = pntr;
			}
			printf("creating new elem\n");
			return;
		}
		else if (*pntr <= v) {
		/*	We are pointing on an element that's value is smaller/equal 
		to the value v we go right. */
			last = pntr;

			pntr = pntr->nextR();
			printf("v >= H\n");
		}
		else {
		/*	We are pointing on an element that's value is bigger
		to the value v we go left. */
			last = pntr;
			pntr = pntr->nextL();
			printf("v < H\n");
		}
	}
}


void BST::rem(int v) {
	node* pntr = H;
	node* last = nullptr;
	while (true)
	{
		if (pntr == nullptr) {
		/*	We have crossed the end of a branch,
		there is no elem with value v, as we would have found it
		if there was one.	*/
			printf("No such elem \n");
			return;
		}
		else if (*pntr == v) {
		/*	We have found the element we want to destroy.
		There are 4 cases, in one of them we change *pntr
		value and delete diffrent element.*/	
			if (pntr->nextL() == nullptr && pntr->nextR() == nullptr) {
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
				delete pntr;
			}
			else if (pntr->nextL() != nullptr && pntr->nextR() != nullptr) {
			/*	Elem we seek to destroy has both children.
			We switch it's position with the smallest child 
			in right branch.*/
				node* child = pntr->nextR();
				while (child->nextL()!=nullptr) {
				/*	Go as far to the left as it's possible*/
					child = child->nextL();
				}
				
				/*if (child->prevF()->getVal() <= child->getVal()) {
					child->prevF()->setR(nullptr);
				}
				else {
					child->prevF()->setL(nullptr);
				}
				pntr->setR(child->nextR());*/
				int val = child->getVal();
				rem(child->getVal());
				pntr->setVal(child->getVal());
				//child->prevF()->setL(nullptr);
				printf("%d had both children, I am removing it. It's left child is %d.\n", v, pntr->nextL()->getVal());
				delete child; 
			}
			else if (pntr->nextR() != nullptr){
			/*	Elem we seek to destroy has left child only.	*/
				if (*last < v) {
					last->setR(pntr->nextR());
				}
				else {
					last->setL(pntr->nextR());
				}
				printf("%d had one child(right), I am removing it.\n", v);
				delete pntr;
			}
			else if (pntr->nextL() != nullptr) {
			/*	Elem we seek to destroy has right child only.	*/
				if (*last < v) {
					last->setR(pntr->nextL());
				}
				else {
					last->setL(pntr->nextL());
				}
				printf("%d had one child(left), I am removing it.\n", v);
				delete pntr;
			}
			return;
		}
		else if (*pntr < v) {
			last = pntr;

			pntr = pntr->nextR();
			printf("v >= H\n");
		}
		else {
			last = pntr;
			pntr = pntr->nextL();
			printf("v < H\n");
		}
	}
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
    printf("\n");
}


void BST::inorder(){
	if (H == nullptr) {
		return;
	}
    std::stack<node *> nodeStack;
    node* temp = H;
    while(!nodeStack.empty() || temp){
        if(temp){
            nodeStack.push(temp);
            temp = temp->nextL();
        }else{
            temp = nodeStack.top();
            nodeStack.pop();
            printf("%d ",temp->getVal());
            temp = temp->nextR();
        }
    }
    printf("\n");
}

void BST::postorder(){
    if (H == nullptr) {
        return;
    }
    std::stack<node *> nodeStack;
    nodeStack.push(H);
    node* last = nullptr;
    node* temp = nullptr;
    while(!nodeStack.empty()){
        temp = nodeStack.top();
        if(!last || last->nextL()==temp || last->nextR()==temp){
            /*We check wheter we go up or down the tree*/
            if(temp->nextL()) nodeStack.push(temp->nextL());
            else if(temp->nextR()) nodeStack.push(temp->nextR());
        }else if(temp->nextL()!=last){
            printf("%d ",temp->getVal());
            nodeStack.pop();
        }else if(temp->nextR()) nodeStack.push(temp->nextR());
        last = temp;
    }
    printf("\n");
}
