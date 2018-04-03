#include "stdafx.h"
#include "BST.h"
#include <stack>
#include <queue>
#include <algorithm> //for max


void BST::addElem(int v) {
    node* ptr = H;
    node* last = nullptr;

    if (v == 197)
        printf("Halo");

    while (true)
    /*    The loop ends when the first if condition is fulfilled.    */
    {
        if (ptr == nullptr)
        /*    We have crossed the end of a branch,
         we schould create a new element here.    */
        {
            ptr = new node;
            ptr->setVal(v);
            if (last != nullptr) {
                /*    We check if the AVLree wasn't empty when
                 we called addElem(v), if it is empty there is no Father/Root,
                 we can't point any pointers to or from him.    */
                if (*last <= v) {
                    /*    Value v is bigger or equal the value of last node,
                     we are the right child for last node.    */
                    last->setR(ptr);
                    ptr->setF(last);
                }
                else {
                    /*    Value v is less than the value of last node,
                     we are the left child for last node.    */
                    last->setL(ptr);
                    ptr->setF(last);
                }
            }
            else {
                H = ptr;
            }
            printf("creating new elem: %d\n",v);
            rotate(ptr);
            return;
        }
        else if (*ptr <= v) {
            /*    We are pointing on an element that's value is smaller/equal
             to the value v we go right. */
            last = ptr;

            ptr = ptr->nextR();
//            printf("v >= H\n");
        }
        else {
            /*    We are pointing on an element that's value is bigger
             to the value v we go left. */
            last = ptr;
            ptr = ptr->nextL();
//            printf("v < H\n");
        }
    }
}


node* BST::search(int v) {
    node* ptr = H;
    while (true)
    {
        if (ptr == nullptr) {
            /*    We have crossed the end of a branch,
             there is no elem with value v, as we would have found it
             if there was one.    */
            printf("!!!\tWARNING YOU SEARCHED FOR AN NOTEXISTING ELEMENT, I SEND YOU NULLPTR HANDLE IT.\t!!!\n");
            return nullptr;
        }
        else if (*ptr == v) {
            return ptr;
        }
        else if (*ptr < v) {
            ptr = ptr->nextR();
//            printf("v >= H\n");
        }
        else {
            ptr = ptr->nextL();
//            printf("v < H\n");
        }
    }
}


void BST::removeByPointer(node* ptr) {
    node* last = ptr->prevF();
    if (ptr->nextL() == nullptr && ptr->nextR() == nullptr) {
        /*    In this case the elem we seek to delete is a leaf,
         this means it has no children.    */
        printf("%d was a leaf, I am removing it.\n", ptr->getVal());
        if (last != nullptr) {
            //chech if it's not the root of the AVL
            if (*last < ptr->getVal()) {
                last->setR(nullptr);
            }
            else {
                last->setL(nullptr);
            }
        }
        delete ptr;
        if (last != nullptr) {
            rotate(last);
        }
    }
    else if (ptr->nextL() != nullptr && ptr->nextR() != nullptr) {
        /*    Elem we seek to destroy has both children.
         We switch it's position with the smallest child
         in right branch.*/
        node* child = ptr->nextR()->maxLeft();
        /*It is crucial to assign the value after we call removeByPointer,
         otherwise we might end up comparing child value with the freshly changed
         element (and that would be wrong, we have to compare it with the unchanged value).
         This might occur when the most left child of our right child is the right child
         itself.*/
        int remember = child->getVal();
        printf("%d had both children, I am replacing it. It's left child is %d.\n", ptr->getVal(), ptr->nextL()->getVal());
        removeByPointer(child);
        printf("I replaced it with %d. It's left child is %d.\n", ptr->getVal(), ptr->nextL()->getVal());
        ptr->setVal(remember);
    }
    else {
        /*    Elem we seek to destroy has one child only.    */

        /*this part decides which pointer to use
         -to left child
         -to right child        */
        node* which;
        if (ptr->nextL() != nullptr) {
            which = ptr->nextL();
        }
        else {
            which = ptr->nextR();
        }


        if (last == nullptr) {
            /*    if we are deleting the root,
             the algorithm is a piece of cake,
             we simple change root to point
             on the child    */
            H = which;
        }
        else {
            /*    We have to chech if we need to change
             our left pointer or right pointer.*/
            if (*last < *ptr) {
                last->setR(which);
            }
            else {
                last->setL(which);
            }
        }
        printf("%d had one child(%d), I am removing it.\n", ptr->getVal(), which->getVal());
        delete ptr;
        rotate(last);
    }
}


void BST::removeByValue(int v) {
    node* check = search(v);
    if (check != nullptr){
        removeByPointer(check);
    }
}


void BST::preorder(){
    if (H == nullptr) {
        return;
    }

    std::stack<node *> nodeStack;
    nodeStack.push(H);

    while (!nodeStack.empty()) {
        /*    remember that stack is LIFO
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
    std::stack<node *> nodeStack;
    node* temp = H;
    while (!nodeStack.empty() || temp) {
        if (temp) {
            nodeStack.push(temp);
            temp = temp->nextL();
        }
        else {
            temp = nodeStack.top();
            nodeStack.pop();
            printf("%d ", temp->getVal());
            temp = temp->nextR();
        }
    }
    printf("\n");
}


void BST::postorder() {
    if (H == nullptr) {
        return;
    }
    std::stack<node *> nodeStack;
    nodeStack.push(H);
    node* last = nullptr;
    node* temp = nullptr;
    while (!nodeStack.empty()) {
        temp = nodeStack.top();
        if (!last || last->nextL() == temp || last->nextR() == temp) {
            /*We check whether we go up or down the tree*/
            if (temp->nextL()) nodeStack.push(temp->nextL());
            else if (temp->nextR()) nodeStack.push(temp->nextR());
        }
        else if (temp->nextL() != last) {
            nodeStack.pop();
            if(last->nextL() == temp)   last->setL(nullptr);
            else                        last->setR(nullptr);
            delete temp;
        }
        else if (temp->nextR()) nodeStack.push(temp->nextR());
        last = temp;
    }
    H = nullptr;
}
