#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include "listy.hpp"
#include "BST.h"
#include "Timer.h"
#include "AVL.h"

void clear(std::string name) {
	std::fstream file;
	file.open(name, std::ios_base::out);
	file << "";
	file.close();
}



int main(int argc, const char * argv[]) {

	srand(time(NULL));


	AVL tree;
	List list;
	Timer time;
	std::fstream dane;
	std::fstream list_creating_file;
	std::fstream list_searching_file;
	std::fstream list_deleting_file;
	std::fstream tree_creating_file;
	std::fstream tree_searching_file;
	std::fstream tree_deleting_file;
	int sizes[] = { 1000,2000,5000,10000,20000,30000,40000,60000,80000,100000 };

	clear("list_c.txt");
	clear("list_s.txt");
	clear("list_d.txt");
	clear("tree_c.txt");
	clear("tree_s.txt");
	clear("tree_d.txt");

	dane.open("dane.txt", std::ios_base::in);
	list_creating_file.open("list_c.txt", std::ios_base::app);
	list_searching_file.open("list_s.txt", std::ios_base::app);
	list_deleting_file.open("list_d.txt", std::ios_base::app);
	tree_creating_file.open("tree_c.txt", std::ios_base::app);
	tree_searching_file.open("tree_s.txt", std::ios_base::app);
	tree_deleting_file.open("tree_d.txt", std::ios_base::app);

	int size_sizes = sizeof(sizes) / sizeof(*sizes);

	printf("HALO");

	for (int sizeIdx = 0; sizeIdx < size_sizes; sizeIdx++) {
		int *data = new int[sizes[sizeIdx]];

		for (int i = 0; i<sizes[sizeIdx]; i++) {
			dane >> data[i];
		}
		//        printf("%d\n",sizes[ sizeIdx ]);
		time.StartTimer();
		for (int i = 0; i<sizes[sizeIdx]; i++)
			list.add(data[i]);
		time.EndTimer();
		list_creating_file << time.GetDelta() << "\n";
		//        printf("Listy- dodawanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());

		time.StartTimer();
		for (int i = 0; i<sizes[sizeIdx]; i += sizes[sizeIdx] / 10)
			list.search(data[i]);
		time.EndTimer();
		list_searching_file << time.GetDelta() << "\n";
		//        printf("Listy- przeszukiwanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());

		time.StartTimer();
		list.del_all();
		time.EndTimer();
		list_deleting_file << time.GetDelta() << "\n";
		//        printf("Listy- usuwanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());


		time.StartTimer();
		for (int i = 0; i<sizes[sizeIdx]; i++) {
			tree.addElem(data[i]);
		}
		time.EndTimer();
		tree_creating_file << time.GetDelta() << "\n";
		//        printf("Drzewa- dodawanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());

		time.StartTimer();
		for (int i = 0; i<sizes[sizeIdx] / 10; i++) {
			tree.search(data[rand() % sizes[sizeIdx]]);
		}
		time.EndTimer();
		tree_searching_file << time.GetDelta() << "\n";
		//        printf("Drzewa- przeszukiwanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());

		time.StartTimer();
		tree.postorder();
		time.EndTimer();
		tree_deleting_file << time.GetDelta() << "\n";
		//        printf("Drzewa- usuwanie %d: %lld\n",sizes[sizeIdx],time.GetDelta());
		delete[] data;
	}

	printf("PAPA\n");

	dane.close();
	list_creating_file.close();
	list_searching_file.close();
	list_deleting_file.close();
	tree_creating_file.close();
	tree_searching_file.close();
	tree_deleting_file.close();
	return 0;
}