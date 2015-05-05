#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>

using namespace std;

/*
AVL Tree Constructor. It just initializes the root pointer to NULL.
*/
AVLTree::AVLTree()
{
	root = NULL;
}

/*
The AVL insert function.
It inserts a new node into the correct place in the tree then calls rebalanceTree to correctly balance the tree.
\param AVLTreeNode *newNode The new node that needs to be inserted into the tree.
*/
void AVLTree::insert(AVLTreeNode *newNode)
{
	AVLTreeNode *temp, *back, *ancestor;

	temp = root;
	back = NULL;
	ancestor = NULL;

	if (root == NULL)
	{
		root = newNode;
		return;
	}

	while (temp != NULL)
	{
		back = temp;
		if (temp->balanceInfo != '=')
			ancestor = temp;
		if (newNode->key < temp->key)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}

	newNode->parent = back;  
	if (newNode->key < back->key)
	{
		back->leftChild = newNode;
	}
	else     
	{
		back->rightChild = newNode;
	}

	rebalanceTree(ancestor, newNode);
}

/*
The AVL Search function.
Essentially the same as a biary search function it traverses the tree until it either hits the end or finds the value.
\param int value The value to look for in the tree.
\return bool It returns true if the value is found false if it is not.
*/
bool AVLTree::search(int value){
	AVLTreeNode *temp;
	bool found = false;

	temp = root;

	while (temp != NULL){
		if (temp->key == value){
			return true;
		}
		else if (temp->key < value){
			temp = temp->rightChild;
		}
		else{
			temp = temp->leftChild;
		}
	}
	return false;
}

/*
This function rebalances the tree to maintain the AVL property. It has to deal with six different cases of tree balance.
\param AVLTreeNode *ancestor the parent node that may be out of balance.
\param AVLTreeNode *newNode The new node that was just inserted that might have put the tree out of balance.
*/
void AVLTree::rebalanceTree(AVLTreeNode *ancestor, AVLTreeNode *newNode)
{
	if (ancestor == NULL)
	{
		if (newNode->key < root->key)       
			root->balanceInfo = 'L';
		else
			root->balanceInfo = 'R';   
		adjustBalanceInfo(root, newNode);
	}
	else if (((ancestor->balanceInfo == 'L') && (newNode->key > ancestor->key)) ||
		((ancestor->balanceInfo == 'R') && (newNode->key < ancestor->key)))
	{
		ancestor->balanceInfo = '=';
		adjustBalanceInfo(ancestor, newNode);
	}
	else if ((ancestor->balanceInfo == 'R') && (newNode->key > ancestor->rightChild->key))
	{
		ancestor->balanceInfo = '=';
		rotateLeft(ancestor);
		adjustBalanceInfo(ancestor->parent, newNode);
	}
	else if ((ancestor->balanceInfo == 'L') && (newNode->key < ancestor->leftChild->key))
	{
		ancestor->balanceInfo = '=';
		rotateRight(ancestor);       
		adjustBalanceInfo(ancestor->parent, newNode);
	}
	else if ((ancestor->balanceInfo == 'L') && (newNode->key > ancestor->leftChild->key))
	{
		rotateLeft(ancestor->leftChild);
		rotateRight(ancestor);
		adjustLeftTree(ancestor, newNode);
	}
	else
	{
		rotateRight(ancestor->rightChild);
		rotateLeft(ancestor);
		adjustRightTree(ancestor, newNode);
	}
}

/*
This function is called to adjust the balance info stored in the tree nodes.
\param AVLTreeNode *end The node for the function to end on.
\param AVLTreeNode *start The node for the function to start on.
*/
void AVLTree::adjustBalanceInfo(AVLTreeNode *end, AVLTreeNode *start)
{
	AVLTreeNode *temp = start->parent;
	while (temp != end)
	{
		if (start->key < temp->key)
			temp->balanceInfo = 'L';
		else
			temp->balanceInfo = 'R';
		temp = temp->parent;
	}
}

/*
This function is used by the rebalance function to perform a left rotation upon a node and handle all of the pointer manipulation.
\param AVLTreeNode *node The node to base the rotation around.
*/
void AVLTree::rotateLeft(AVLTreeNode *node)
{
	AVLTreeNode *temp = node->rightChild;
	node->rightChild = temp->leftChild;
	if (temp->leftChild != NULL)
		temp->leftChild->parent = node;
	if (node->parent == NULL)
	{
		root = temp;
		temp->parent = NULL;
	}
	else if (node->parent->leftChild == node)
		node->parent->leftChild = temp;
	else
		node->parent->rightChild = temp;

	temp->leftChild = node;
	AVLTreeNode *parentParent;
	if (temp->parent != NULL){
		parentParent = temp->parent->parent;
	}
	node->parent = temp;
	if (temp->parent != NULL && temp->parent->parent == temp){
		temp->parent = parentParent;
	}
}

/*
This function is used by the rebalance function to perform a right rotation upon a node and handle all of the pointer manipulation.
\param AVLTreeNode *node The node to base the rotation around.
*/
void AVLTree::rotateRight(AVLTreeNode *node)
{
	AVLTreeNode *temp = node->leftChild;
	node->leftChild = temp->rightChild;
	if (temp->rightChild != NULL)
		temp->rightChild->parent = node;
	if (node->parent == NULL)
	{
		root = temp;
		temp->parent = NULL;
	}
	else if (node->parent->leftChild == node)
		node->parent->leftChild = temp;
	else
		node->parent->rightChild = temp;

	temp->rightChild = node;
	AVLTreeNode *parentParent;
	if (temp->parent != NULL){
		parentParent = temp->parent->parent;
	}
	node->parent = temp;
	if (temp->parent != NULL && temp->parent->parent == temp){
		temp->parent = parentParent;
	}
}

/*
This function helps adjust the balance info throughout the left subtree of a node. Unless it is the root of the tree.
\param AVLTreeNode *end The node whose left subtree needs to be looked at.
\param AVLTreeNode *newNode The new node added that might have thrown off the trees balance.
*/
void AVLTree::adjustLeftTree(AVLTreeNode *end, AVLTreeNode *newNode)
{
	if (end == root)
		end->balanceInfo = '=';
	else if (newNode->key < end->parent->key)
	{
		end->balanceInfo = 'R';
		adjustBalanceInfo(end->parent->leftChild, newNode);
	}
	else
	{
		end->balanceInfo = '=';
		end->parent->leftChild->balanceInfo = 'L';
		adjustBalanceInfo(end, newNode);
	}
}

/*
This function helps adjust the balance info throughout the right subtree of a node. Unless it is the root of the tree.
\param AVLTreeNode *end The node whose left subtree needs to be looked at.
\param AVLTreeNode *newNode The new node added that might have thrown off the trees balance.
*/
void AVLTree::adjustRightTree(AVLTreeNode *end, AVLTreeNode *newNode)
{
	if (end == root)
		end->balanceInfo = '=';
	else if (newNode->key > end->parent->key)
	{
		end->balanceInfo = 'L';
		adjustBalanceInfo(end->parent->rightChild, newNode);
	}
	else
	{
		end->balanceInfo = '=';
		end->parent->rightChild->balanceInfo = 'R';
		adjustBalanceInfo(end, newNode);
	}
}
