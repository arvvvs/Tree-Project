#include <vector>

class BTreeNode {
public:
	std::vector<int> data;
	std::vector<BTreeNode *> children;
	bool leaf;

	BTreeNode(bool leaf);
	void normalInsert(int item, int order);
	void splitChild(int index, BTreeNode * node, int order);
	void traverse();
	BTreeNode * search(int item);
};

class BTree {
public:
	int order;
	BTreeNode * root;

	BTree(int _order);
	void insert(int item);
	void traverse();
	BTreeNode * search(int item);
};