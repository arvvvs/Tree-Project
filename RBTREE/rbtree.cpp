#include<cctype>
#include<math.h>
#include<time.h>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include"rbtree.h"

using namespace std;
//creates the node
rbNode::rbNode(){
	right = NULL;
	left = NULL;
	parent = NULL;
	data = NULL;
	color = "black";
	treecount = NULL;
}
//sets left child of node
void rbNode::setLeft(rbNode* ileft){
	left = ileft;
}
//sets right subchild of node
void rbNode::setRight(rbNode* iright){
	right = iright;
}
//sets data of node
void rbNode::setData(int aData){
	data=aData;
}
//sets color of node to either black or red
void rbNode::setColor(string icolor){
	color = icolor;
}
//prints color for diagnostics
void rbNode::printColor(){
	cout<<color<<endl;
}
//counts trees by recursion ot check
int rbNode::returnTreeCount(rbNode* h){
	if(h->data == NULL){
		return -1;
	}
	else{
		return h->treecount;
	}
}
//returns color of node
string rbNode::returnColor(rbNode* h){
	return h->color;
}
//looks at individual node 
void rbNode::printSubHeight(rbNode* printHeight){
	cout<<printHeight->treecount<<endl;
}
//returns data in node
int rbNode::returnData(rbNode* h){
	if(h->data==NULL){
		return -1;
	}
	else{
		return h->data;
	}
}
//tocheck existance of tree
bool RBT::isEmpty(){
	if(root->data==NULL){
		return true;
	}
	else{
		return false;
	}
}
//to check if it is empty
bool rbNode::isEmpty(rbNode* node){
	if(node->data==NULL){
		return true;
	}
	else{
		return false;
	}
}
//setup red black tree
RBT::RBT(string ifile, string ofile){
	iFile.open(ifile);
	oFile.open(ofile);	
	if(!iFile.is_open()){ 
		cerr<<"error in opening files"<<endl;
	}
	root = NULL;

}
//stores input to a vector
void RBT::input(){
	string line;
	int toStore;
	while(getline(iFile, line)){
			toStore = atoi(line.c_str());
			toInsert.push_back(toStore);
			}	
}
//find out height of individual nodes
//by using recursion to count and find out the size of the largest count
int rbNode::nodeHeight(rbNode* x){
	if(x->data == NULL){
		return -1;}
	else{
		return 1+max(nodeHeight(x->left), nodeHeight(x->right));
	}
}
//height of tree total using above function
int RBT::treeHeight(){
	if(root->data == NULL){
		return -1;}
	else{
		rbNode f;
		return 1+max(f.nodeHeight(root->left), f.nodeHeight(root->right)); }
}
//function to print out data and color of node for individual checking
void rbNode::printData(rbNode* h){
	cout<<h->color<<endl;
	cout<<h->data<<endl;
}
//inserts from vector to tree
void RBT::insertToTree(){
	rbNode* f = new rbNode();
	if(root == NULL){
		createRoot();
	}	
	for(unsigned i = 0; i<toInsert.size(); i++){
		root = f->insert(root, toInsert.at(i));
	}	
}
//creates the root of tree
void RBT::createRoot(){
	rbNode* item = new rbNode();
	rbNode* itemL = new rbNode();
	rbNode* itemR = new rbNode();
	item -> data = NULL;
	itemL -> data = NULL;
	itemR -> data = NULL;
	item -> color = "black";
	itemL -> color = "black";
	itemR -> color = "black";
	root = item;
	root-> right = itemR;
	root -> left = itemL;
}
//inserts node into tree
//and rotates tree branches accordingly
rbNode* rbNode::insert(rbNode* h, int value){
	if(h->isEmpty(h)==true){
		rbNode* k = new rbNode();
		k->color = "red";
		k->data = value;
		k->left = new rbNode();
		k->left->color = "black";
		k->right = new rbNode();
		k->right->color = "black";
		return k;
	}	
	if(h->data < value){
		insert(h->left, value);
	}
	else if(h->data > value){
		insert(h->right, value);
	}	
	else{
		h->data = value;
	}
	if(h->right->color=="red" && h->left->color!="red"){
		h = rotateLeft(h);
	}
	if(h->left->color=="red" && h->left->left->color=="red"){
		h = rotateRight (h);
	}
	if(h->left->color == "red" && h->right->color=="red"){
		flipColors(h);
	}
	h->treecount = h->left->treecount + h->right->treecount + 1;
	return h;
}
//rotates tree right
rbNode* rbNode::rotateRight(rbNode* h){
	rbNode* x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = x->right->color;
	x->right->color = "red";
	x->treecount = h->treecount;
	h->treecount = h->left->treecount + h->right->treecount +1;
	return x;
}
//rotates left
rbNode* rbNode::rotateLeft(rbNode* h){
	rbNode* x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = x->left->color;
	x->left->color = "red";
	x->treecount = h->treecount;
	h->treecount = x->left->treecount + x->right->treecount +1;
}
//changes color
rbNode* rbNode::flipColors(rbNode* h){
	if(h->color == "red"){
		h->color = "black";
	}
	else if(h->color =="black"){
		h->color = "red";
	}
	if(h->left->color == "red"){
		h->left->color = "black";
	}
	else if(h->left->color == "black"){
		h->left->color = "red";
	}
	if(h->right->color == "red"){
		h->right->color = "black";
	}
	else if(h->right->color == "black"){
		h->right->color = "red";
	}
}
//find function
bool RBT::search(int value, rbNode* h){
	while(h->data != NULL){
		if(h->data < value){
			h=h->left;
		}
		else if(h->data > value){
			h=h->right;
		}
		else{
			return true;
		}
	}
	return false;
}
//runs it
void RBT::run(){
	clock_t t;
	t = clock();
	insertToTree();
	t = clock() - t;
	oFile<<((float) t)/CLOCKS_PER_SEC<<endl;
}
