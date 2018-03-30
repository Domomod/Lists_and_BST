//
//  main.cpp
//  Listy
//
//  Created by Krzysztof Sychla on 27.03.2018.
//  Copyright © 2018 Krzysztof Sychla. All rights reserved.
//

#include <iostream>
#include "listy.hpp"
#include "BST.h"


int main(int argc, const char * argv[]) {
    int tab[] = {19,11,10,5,2,14,4,6,9,15,7,3,1,8};
    
    BST tree;
    List l;
    for(int i=0;i<(sizeof(tab)/sizeof(*tab));i++){
        tree.addElem(tab[i]);
        l.add(tab[i]);
    }
    printf("Drzewo BST: \n");
    tree.preorder();
    tree.inorder();
    tree.postorder();
    
    
    return 0;
}
