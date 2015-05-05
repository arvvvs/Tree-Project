#include "btree.h"
#include <iostream>

BTreeNode::BTreeNode(bool leaf_) {
	leaf = leaf_;
}

//almost got it
void BTreeNode::splitChild(int index, BTreeNode * node, int order) {
	int accessIndex = order / 2;
	BTreeNode * newNode = new BTreeNode(node->leaf);//2nd half
	int middle = node->data[accessIndex];
	int i = 0;
	while(i < data.size()) {
		if(middle < data[i]) {
			break;
		}
		i++;
	}
	data.insert(data.begin() + i, middle);
	node->data.erase(node->data.begin() + accessIndex);
	while(node->data.size() > accessIndex) {
		newNode->data.push_back(node->data[accessIndex]);
		node->data.erase(node->data.begin() + accessIndex);
	}
	//new line;
	while(node->children.size() > accessIndex + 1) {
		newNode->children.push_back(node->children[accessIndex + 1]);
		node->children.erase(node->children.begin() + accessIndex + 1);
	}
	children.insert(children.begin() + index + 1, newNode);
}

void BTreeNode::normalInsert(int item, int order) {
	int i = 0;
	while(i < data.size()) {
		if(item < data[i]) {
			break;
		}
		i++;
	}
	if(leaf == true) {
		data.insert(data.begin() + i, item);
	} else {
		if(children[i]->data.size() >= order) {
			splitChild(i, children[i], order);
			if(data[i] < item) {
				i++;
			}
		}	
		children[i]->normalInsert(item, order);

	}
}

void BTreeNode::traverse() {
	int i = 0;
	while(i < data.size()) {
		if(leaf == false) {
			children[i]->traverse();
		}
		std::cout << data[i] << " ";
		i++;
	}
	if(leaf == false) {
		children[i]->traverse();
	}
}

BTreeNode * BTreeNode::search(int item) {
	int i = 0;
	while(i < data.size()) {
		if(item < data[i]) {
			break;
		} else if(item == data[i]) {
			break;
		}
		i++;
	}
	if(item == data[i]) {
		return this;
	}
	if(leaf == true) {
		return NULL;
	} 
	return children[i]->search(item);
}

BTree::BTree(int _order) {
	order = _order;
	root = NULL;
}

void BTree::traverse() {
	if(root != NULL) {
		root->traverse();
	}
}

void BTree::insert(int item) {
	if(root == NULL) {
		root = new BTreeNode(true);
		root->data.push_back(item);
	} else {
		if(root->data.size() == order) {
			BTreeNode * newRoot = new BTreeNode(false);
			newRoot->children.push_back(root);
			newRoot->splitChild(0, root, order);
			//after that call, newRoot will have one key from the split node
			if(newRoot->data[0] < item) {
				newRoot->children[1]->normalInsert(item, order);
			} else {
				newRoot->children[0]->normalInsert(item, order);
			}
			root = newRoot;
		} else {
			root->normalInsert(item, order);
		}
	}
}

BTreeNode * BTree::search(int item) {
	if(root == NULL) {
		return NULL;
	} else {
		return root->search(item);
	}
}



/*void BTree::insert(int item, BTreeNode * node) {
	if(node == NULL) {
		return;
	}
	int i = 0;
	bool inserted = false;
	while(i < node->data.size()) {
		if(item < node->data[i]) {
			if(node->leaf == true) {
				node->data.insert(node->data.begin() + i, item);
				inserted = true;
				break;
			} else {
				//make sure node isnt null
				insert(item, node->children[i]);
				inserted = true;
				break;
			}
		}
		i++;
	}
	if(inserted == false) {
		if(node->leaf == true) {
			node->data.push_back(item);
			inserted = true;
		} else {
			//make sure node isnt null
			insert(item, node->children[i]);
			inserted = true;
		}
	}
	//now handle overflow
	if(node->data.size() == order) {
		handleOverflow(node);
	}
}*/

/*void BTree::handleOverflow(BTreeNode * node) {
	int accessIndex = order / 2;
	if(node->parent == NULL) {
		node->parent = new BTreeNode(order);
		//node->parent->children[0] = node;
		node->parent->children.insert(node->parent->children.begin(), node);
		node->parent->data.push_back(node->data[accessIndex]);
		node->data.erase(node->data.begin() + accessIndex);
		//node->parent->children[0+1] = new BTreeNode(order);
		node->parent->children.insert(node->parent->children.begin() + 1, new BTreeNode(order));
		if(node->leaf == true) {
			node->parent->children[1]->leaf = true;
		}
		//node->parent->children[1]->leaf = true;
		node->parent->children[1]->parent = node->parent;
		while(node->data.size() > accessIndex) {
			node->parent->children[1]->data.push_back(node->data[accessIndex]);
			node->data.erase(node->data.begin() + accessIndex);
		}
		while(node->children.size() > accessIndex + 1) {
			node->parent->children[1]->children.push_back(node->children[accessIndex + 1]);
			node->children.erase(node->children.begin() + accessIndex + 1);
		}
		root = node->parent;
	} else {
		int index = insertInParent(node->data[accessIndex], node->parent);
		node->data.erase(node->data.begin() + accessIndex);
		BTreeNode * dummy = new BTreeNode(order);
		dummy->parent = node->parent;
		if(node->leaf == true) {
			dummy->leaf = true;
		}
		while(node->data.size() > accessIndex) {
			dummy->data.push_back(node->data[accessIndex]);
			node->data.erase(node->data.begin() + accessIndex);
		}
		//node->parent->children[index + 1] = dummy; //I THINK THIS SHOULD BE INSERT
		node->parent->children.insert(node->parent->children.begin() + index + 1, dummy);
		//delete dummy; //THIS IS WRONG
	}
}*/

/*int BTree::insertInParent(int item, BTreeNode * node) {
	int i = 0;
	while(i < node->data.size()) {
		if(item < node->data[i]) {
			break;
		}
		i++;
	}
	node->data.insert(node->data.begin() + i, item);
	return i;
}*/


