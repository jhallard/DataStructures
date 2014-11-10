#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "BinarySearchTree.h"
#include <random>
#include <ctime>

using namespace std;

template<class ItemType>
void fileToTree(BinarySearchTree<ItemType> & temp, string filename,  bool random, int amount);
void visit(string & name);

int main()
{
	srand(time(NULL));

	const string filename = "names.txt"; // file name with the names to be put into the tree
	
	BinarySearchTree<string> tree;		// our binary search tree

	while(true)
	{
		fileToTree(tree, filename, true, 36);//rand()%9+6);			// get the names from the file to the tree
		// Print the Tree Diagram for the User
		if(tree.getHeight() < 7)
		{
			cout << "     Tree Diagram :\n\n";
			tree.BSTPrint();

			cout << "\n";
			//// Print the contents in order
			//void (*fptr)(string&);
			//fptr = visit;
			//cout << "\n\n\nIn order contents of tree :\n";
			//tree.inorderTraverse(fptr);
			//cout << "\n\n\n";
			getchar();//system("pause");
			//system("cls");
		}

		tree.clear();
	}


	//cout << "\n\n\n";
	//system("pause");

	//// Search for a name that is in there and one that is not
	//string name1 = "Nancy Drew";
	//string name2 = "Joey Saldano";

	//string temp = (tree.contains(name1))? " is " : " is not ";
	//	cout << name1 << temp << "contained in the tree. " << endl;
	// temp = (tree.contains(name2))? " is " : " is not ";
	//	cout << name2 << temp << "contained in the tree. " << endl;

		cout << "\n\n\n";
		getchar();

}

template<class ItemType>
void fileToTree(BinarySearchTree<ItemType> & temp, string filename, bool random, int amount)
{
	//srand(time(NULL));


	string STRING;
	ifstream infile;
	infile.open(filename);
	std::vector<std::string> names;
	while(!infile.eof()) // To get you all the lines.
    {
	    getline(infile,STRING); // Saves the line in STRING.
		names.push_back(STRING);
    }
	infile.close();

	for(int i = 0; i < amount; i++)
		(random)? temp.add(names[rand()%names.size()]) : temp.add(names[i]);
}

void visit(string & name)
{
	static int count = 1;
	cout << count << " : " << name << endl;
	count++;
}
