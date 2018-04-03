//
//  listy.hpp
//  Listy
//
//  Created by Krzysztof Sychla on 27.03.2018.
//  Copyright © 2018 Krzysztof Sychla. All rights reserved.
//

#pragma once

#include <stdio.h>

class SimpleNode{
public:
    int value;
    SimpleNode(){next = nullptr;}
    SimpleNode *next;
};

class List{
public:
    void add(int e);
    void del(int v);
    SimpleNode* search(int v);
    void show();
    void del_all();
    List(){head=nullptr;};
private:
    SimpleNode *head;
};

