/*
Header file for AVL Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>

using namespace std;

struct AVLTreeNode
{
	int key;
	AVLTreeNode *leftChild;
	AVLTreeNode *rightChild;
	AVLTreeNode *parent;
	char balanceInfo;
};

class AVLTree
{
private:
	AVLTreeNode   *root;
public:
	AVLTree();
	void insert(AVLTreeNode *node);
	bool search(int value);
	void rebalanceTree(AVLTreeNode *ancestor, AVLTreeNode *newNode);
	void adjustBalanceInfo(AVLTreeNode *end, AVLTreeNode *start);
	void rotateLeft(AVLTreeNode *node);
	void rotateRight(AVLTreeNode *node);
	void adjustLeftTree(AVLTreeNode *end, AVLTreeNode *start);
	void adjustRightTree(AVLTreeNode *end, AVLTreeNode *start);
};
