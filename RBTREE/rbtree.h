#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class rbNode{
	private:
	public:
		int data;
		rbNode* right;
		rbNode* left;
		rbNode* parent;
		string color;
		int treecount;
		bool empty;
		rbNode();
		void setLeft(rbNode* ileft);
		void setRight(rbNode* iright);
		void setData(int aData);
		int returnData(rbNode* h);
		void printData(rbNode* h);
		string returnColor(rbNode* h);
		int returnTreeCount(rbNode* h);
		void setColor(string icolor);
		void printColor();
		void setParent(rbNode* parents);
		bool isEmpty(rbNode* node);
		void printSubHeight(rbNode* printHeight);
		int nodeHeight(rbNode* x);
		rbNode* insert(rbNode* h, int value); 
		rbNode* rotateRight(rbNode* h);
		rbNode* rotateLeft(rbNode* h);
		rbNode* flipColors(rbNode* h);

};
class RBT{
	private:
		rbNode* root;
		int height;
		ifstream iFile;
		ofstream oFile;
		vector<int> toInsert;
	public:
		RBT(string ifile, string ofile);
		void input();
		bool isEmpty();
		int treeHeight();
		void insertToTree();
		void createRoot();
		bool search(int value, rbNode* h);
		void run();


};



