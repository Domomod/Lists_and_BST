//
//  listy.cpp
//  Listy
//
//  Created by Krzysztof Sychla on 27.03.2018.
//  Copyright © 2018 Krzysztof Sychla. All rights reserved.
//
#include "stdafx.h"
#include "listy.hpp"
#include <stdio.h>


void List::add(int element){
    SimpleNode *elem = new SimpleNode;
    
    elem->value = element;
    // assigning value to our element
    if(head == nullptr) head = elem;
    else{
        SimpleNode *current = head;
        SimpleNode *last = nullptr;
        /*  we need two pointers,
        one pointing to the current element,
         and one pointing to the last element  */
        while(current != nullptr && current->value < elem->value){
            /* we iterate through the list,
             until we find an element which
             value is bigger than our value */
            last = current;
            current = current->next;
        }
        if(current == head){
            /* if our list is empty,
             we make our head,
             the first element */
            elem->next = current;
            head = elem;
            return;
        }
        last->next = elem;
        if(current!=nullptr){
            elem->next = current;
        }
        else{
            elem->next=nullptr;
        }
    }
}

 void List::del(int value){
     SimpleNode *temp = head;
     SimpleNode *before = head;
     while(temp){
         if(temp->value == value){
             /* we have to iterate through
              the list and find the value
              we are looking for, then delete it */
             if(value == head->value){
				 before = temp;
				 head = temp->next;
				 delete before;
                 return;
             }
             before->next = temp->next;
             delete temp;
             return;
         }
         before = temp;
         temp = temp->next;
     }
 }

 SimpleNode* List::search(int value){
     SimpleNode *temp = head;
     while(temp){
         if(temp->value == value){
             return temp;
         }
         temp = temp->next;
     }
     return nullptr;
 }

 void List::show(){
     SimpleNode *temp = head;
     while(temp){
         printf("%d ",temp->value);
         temp = temp->next;
     }
     printf("\n");
 }

void List::del_all(){
    SimpleNode *temp = head;
    while(temp){
        /* we delete all elements,
         starting with the head */
		SimpleNode* last = temp;
		temp = temp->next;
        del(last->value);
    }
}

