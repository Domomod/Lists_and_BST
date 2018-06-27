//
//  main.cpp
//  Listy
//
//  Created by Krzysztof Sychla on 27.03.2018.
//  Copyright © 2018 Krzysztof Sychla. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include "listy.hpp"
#include "BST.h"
#include "Timer.h"



int main(int argc, const char * argv[]) {
    int dane_temp[] = {11,25,13,4,5,6,9,14,12,15};
    
    BST tree;
    List list;
    Timer time;
    std::fstream dane;
    std::fstream list_file;
    std::fstream tree_file;
    int sizes[] = { 1000,2000,5000,10000,20000,30000,40000,60000,80000,100000 };
    
    
    dane.open("dane.txt", std::ios_base::in);
    list_file.open("list.txt", std::ios_base::out);
    tree_file.open("tree.txt", std::ios_base::out);
    
    int size_sizes = sizeof(sizes)/sizeof(*sizes);
    
    for (int sizeIdx = 0; sizeIdx < size_sizes; sizeIdx++){
        int data[sizes[ sizeIdx ]];
        
        for (int i=0;i<sizes[sizeIdx];i++){
            dane >> data[i];
        }
//        int data[] = {5,1,2,9,3,4,6,7};
        
        printf("Prossecing the list\n");
        printf("Creating the list\n");
        time.StartTimer();
        for (int i=0;i<sizes[sizeIdx];i++)
            list.add(data[i]);
        time.EndTimer();
        printf("Creating list took: %lld\n",time.GetDelta());
        
        printf("Searching the list\n");
        time.StartTimer();
        for (int i=0;i<sizes[sizeIdx];i+=sizes[sizeIdx]/10)
            list.search(data[i]);
        time.EndTimer();
        printf("Serching list took: %lld\n",time.GetDelta());
        
        printf("Deleting whole list\n");
        time.StartTimer();
        list.del_all();
        time.EndTimer();
        printf("Deleting list took: %lld\n",time.GetDelta());
        
        
        printf("Processing the tree\n");
        printf("Creating the tree\n");
        time.StartTimer();
        for (int i=0;i<sizes[sizeIdx];i++)
            tree.addElem(data[i]);
        time.EndTimer();
        printf("Creating tree took: %lld\n",time.GetDelta());
        
        printf("Searching the tree\n");
        time.StartTimer();
        for (int i=0;i<sizes[sizeIdx];i+=sizes[sizeIdx]/10)
            tree.search(data[i]);
        time.EndTimer();
        printf("Creating list took: %lld\n",time.GetDelta());
        
        printf("Deleting whole tree\n");
        time.StartTimer();
        tree.postorder();
        time.EndTimer();
        printf("Deleting tree took: %lld\n",time.GetDelta());
    }
    
    
    
    dane.close();
    list_file.close();
    tree_file.close();
    return 0;
}
