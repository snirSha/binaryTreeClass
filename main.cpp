#include<iostream>
#include<cstdlib>

#include"Tree.cpp"

using namespace std;

int main()
{
	int TreeKeys[16] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80 };
	Tree myTree;

	cout << "Printing the tree in order\n Before adding numbers\n";

	myTree.print();

	for (int i = 0; i < 16; i++) {
		myTree.insert(TreeKeys[i]);
	}

	cout << "Printing the tree in order\nAfter adding numbers\n";

	myTree.print();

	cout << endl;

	cout<<"The smallest value in the tree" <<myTree.findSmallest()<<endl;

	return 0;
}