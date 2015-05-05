#include AVLTree.h

/*
A function to process the input data files into a vector that our trees can read from to eliminate I/O inconsistencies with timing.
\param string testFileName The name of the file to process
\return vector<int> The vector of ints that the trees will insert from.
*/
vector<int> processTestFile(string testFileName){
	vector<int> retVal;
	ifstream inFile;
	inFile.open(testFileName.c_str());
	string line;
	int temp;
	while (getline(inFile, line)){
		temp = atoi(line.c_str());
		retVal.push_back(temp);
	}
	return retVal;
}

/*
This function performs and times the tests for the different trees.
*/
void performTests(vector<int> inputData, AVLTree AVLTestTree){ //need to add for RBtree and Btree

	clock_t AVLInsertBegin = clock();
	for (int i = 0; i < inputData.size(); i++){
		AVLTreeNode *newNode = new AVLTreeNode;
		newNode->key = inputData[i];
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = NULL;
		newNode->balanceInfo = '=';
		AVLTestTree.insert(newNode);
	}
	clock_t AVLInsertEnd = clock();
	double AVLInsertTime = (double(AVLInsertEnd - AVLInsertBegin) / CLOCKS_PER_SEC);
	cout << "AVL took " << AVLInsertTime << " seconds to perform an insert of " << inputData.size() << " values." << endl;

	//clock_t RBInsertBegin = clock();
	//for (int i = 0; i < inputData.size(); i++){
	//																//Need to fill in RB insert info
	//}
	//clock_t RBInsertEnd = clock();
	//double RBInsertTime = (double(RBInsertEnd - RBInsertBegin) / CLOCKS_PER_SEC);
	//cout << "Red Black took " << RBInsertTime << " seconds to perform an insert of " << inputData.size() << " values." << endl;

	//clock_t BTreeInsertBegin = clock();
	//for (int i = 0; i < inputData.size(); i++){
	//																//Need to fill in B tree insert info
	//}
	//clock_t BTreeInsertEnd = clock();
	//double BTreeInsertTime = (double(BTreeInsertEnd - BTreeInsertBegin) / CLOCKS_PER_SEC);
	//cout << "B Tree took " << RBInsertTime << " seconds to perform an insert of " << inputData.size() << " values." << endl;

}

int main(int argc, char* argv[]){

	string Ascending1KTestFile = "Ascending1KTest.txt";
	string Ascending10KTestFile = "Ascending10KTest.txt";
	string Ascending1MTestFile = "Ascending1MTest.txt";
	string Descending1KTestFile = "Descending1KTest.txt";
	string Descending10KTestFile = "Descending10KTest.txt";
	string Descending1MTestFile = "Descending1MTest.txt";
	vector<int> inputData;
	inputData = processTestFile(Descending1MTestFile);

	AVLTree AVLTestTree;

	performTests(inputData, AVLTestTree);
}
