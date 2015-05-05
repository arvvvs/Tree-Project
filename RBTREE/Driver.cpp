include <iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>
#include<string>
#include"rbtree.h"

using namespace std;

int main(int argc, char *argv[]){
	string ifile;
	string ofile;
	if(argc ==3){
	ifile = argv[1];
	ofile = argv[2];	
	}
	else{
		cout<<"incorrect parameters"<<endl;
	}

	RBT rbt(ifile, ofile);
	rbt.input();
	rbt.run();
}
