#include "btree.h"
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#include<cctype>
#include<stdlib.h>
#include<ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
/*	BTree tree(4);
	tree.insert(20);
	tree.insert(40);
	tree.insert(50);
	tree.insert(80);
	tree.insert(3);
	tree.insert(1);
	tree.insert(25);
	tree.insert(10);
	tree.insert(100);
	tree.insert(75);
	tree.insert(15);
	tree.insert(22);
	tree.insert(45);
	tree.insert(120);
	tree.insert(200);
	tree.insert(48);
	tree.insert(18);
	tree.traverse();
	std::cout << std::endl;

	BTreeNode * result = tree.search(10);
	if(result != NULL) {
	for(int i = 0; i < result->data.size(); i++) {
		std::cout << result->data[i] << std::endl;
	}
}

	/*for(int i = 0; i < tree.root->data.size(); i++) {
		std::cout << tree.root->data[i] << std::endl;
	}
	for(int j = 0; j < tree.root->children.size(); j++) {
		for(int k = 0; k < tree.root->children[j]->data.size(); k++) {
			std::cout << tree.root->children[j]->data[k] << std::endl;
		}
	}*/
    string inFile;
    if(argc == 2){
        inFile = argv[1];
    }
else{
    cout<<"incorrect parameters"<<endl;
}
   vector<int> inputData;
   ifstream file(inFile);
    string line;
    int temp;
    while(getline(file, line)){
       temp = atoi(line.c_str());
       inputData.push_back(temp);
    } 
    BTree tree(4);
    cout<<inputData.size()<<endl;
    clock_t t;
    for(unsigned i=0; i<inputData.size(); i++){
        tree.insert(inputData.at(i));
    }
t = clock() -t;
cout<<"it took "<<((float)t)/CLOCKS_PER_SEC<<endl;
}
