#include <iostream>
#include <stack>
#include <regex>
#include <sstream>
#include "BST.h"
using namespace std;

// Helpers
void BST::helperIn(TreeNode* root, vector<string> &vec) {
	if (root == nullptr) {
		return;
	}

	helperIn(root->left, vec);
	vec.push_back(root->name);
	helperIn(root->right, vec);
}

void BST::helperPre(TreeNode* root, vector<string> &vec) {
	if (root == nullptr) {
		return;
	}

	vec.push_back(root->name);
	helperPre(root->left, vec);
	helperPre(root->right, vec);
}

void BST::helperPost(TreeNode* root, vector<string> &vec) {
	if (root == nullptr) {
		return;
	}

	helperPost(root->left, vec);
	helperPost(root->right, vec);
	vec.push_back(root->name);
}

void BST::helperSearchName(TreeNode* root, vector<int> &vec, string name) {
	if (root == nullptr) {
		return;
	}

	if (root->name == name) {
		vec.push_back(root->id);
	}
	helperSearchName(root->left, vec, name);
	helperSearchName(root->right, vec, name);
}

int BST::height(TreeNode* root) { // DONE
	if (root == nullptr)
		return 0;
	else {
		int left = height(root->left);
		int right = height(root->right);

		return max(left, right) + 1;
	}
}



int BST::getBalanceFactor(TreeNode* node) { // DONE
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

TreeNode* BST::createNode(string name, int id) { // DONE
	TreeNode* node = new TreeNode();
	node->id = id;
	node->name = name;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;

	return node;
}

// Rotations
TreeNode* BST::right(TreeNode* root) { // DONE
	TreeNode* grandchild = root->left->right;
	TreeNode* newParent =  root->left;
	newParent->right = root;
	root->left = grandchild;
	return newParent;
}

TreeNode* BST::left(TreeNode* root) { // DONE
	TreeNode* grandchild = root->right->left;
	TreeNode* newParent =  root->right;
	newParent->left = root;
	root->right = grandchild;
	return newParent;
}

TreeNode* BST::rightLeft(TreeNode* root) { // DONE
	root->right = right(root->right);
	return left(root);
}

TreeNode* BST::leftRight(TreeNode* root) { // DONE
	root->left = left(root->left);
	return right(root);
}

// Manipulative Functions
TreeNode* BST::insert(TreeNode* root, string name, int id) { // DONE
	if (root == nullptr) {
		cout << "successful" << endl;
		return createNode(name, id);
	}

	if (id < root->id) {
		root->left = insert(root->left, name, id);
	}
	else if (id > root->id) {
		root->right = insert(root->right, name, id);
	}
 
	root->height = height(root);
	int balanceFactor = getBalanceFactor(root);

	// Left Left
	if (balanceFactor == 2 && id < root->left->id) {
		return right(root);
	}
	// Right Right
	if (balanceFactor == -2 && id > root->right->id) {
		return left(root);
	}

	// Left Right
	if (balanceFactor == 2 && id > root->left->id) {
		return leftRight(root);
	}

	// Right Left
	if (balanceFactor == -2 && id < root->right->id) {
		return rightLeft(root);
	}

	return root;
}

TreeNode* BST::remove(TreeNode* root, int id) { // DONE
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
		return root;
	}

	else if (id < root->id) {
		root->left = remove(root->left, id);
	}

	else if (id > root->id) {
		root->right = remove(root->right, id);
	}

	else {
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			cout << "successful" << endl;
			return nullptr;
			
		}
		else if (root->left == nullptr) {
			TreeNode* temp = root->right;
			delete root->right;
			cout << "successful" << endl;
			return temp;
		}
		else if (root->right == nullptr) {
			TreeNode* temp = root->left;
			delete root->left;
			cout << "successful" << endl;
			return temp;
		}
		else {
			TreeNode* temp = root->left;
			while (temp && temp->right != nullptr) {
				temp = temp->right;
			}
			root->id = temp->id;
			root->name = temp->name;

			root->left = remove(root->left, temp->id);
		}
	}
	root->height = height(root);
	return root;
}

void BST::searchId(TreeNode* root, int id) { // DONE
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
	}
	else if (id == root->id) {
		cout << root->name << endl;
	}
	else if (root->id < id) {
		searchId(root->right, id);
	}
	else if (root->id > id) {
		searchId(root->left, id);
	}
}

void BST::searchName(TreeNode* root, string name) { // DONE
	vector<int> vec;

	if (root == nullptr) {
		cout << "unsuccessful" << endl;
	}
	else if (name == root->name) {
		helperSearchName(root, vec, name);

		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << endl;
		}
	}
	else if (root->name < name) {
		searchName(root->right, name);
	}
	else if (root->name > name) {
		searchName(root->left, name);
	}
}

// Printing Functions
void BST::printInorder(TreeNode* root) { // DONE
	vector<string> vec;
	helperIn(root, vec);

	bool first = true;
	for (int i = 0; i < vec.size(); i++) {
		if (first) {
			cout << vec[i];
		}
		else {
			cout << ", " << vec[i];
		}
		first = false;
	}
}

void BST::printPreorder(TreeNode* root) { // DONE
	vector<string> vec;
	helperPre(root, vec);

	bool first = true;
	for (int i = 0; i < vec.size(); i++) {
		if (first) {
			cout << vec[i];
		}
		else {
			cout << ", " << vec[i];
		}
		first = false;
	}
}

void BST::printPostorder(TreeNode* root) { // DONE
	vector<string> vec;
	helperPost(root, vec);

	bool first = true;
	for (int i = 0; i < vec.size(); i++) {
		if (first) {
			cout << vec[i];
		}
		else {
			cout << ", " << vec[i];
		}
		first = false;
	}
}

void BST::printLevelCount(TreeNode* root) { // DONE
	if (root == nullptr) 
		cout << 0;
	else {
		cout << height(root);
	}
}

// Other
void BST::removeInorder(int n) { // TODO
}

int main() {
	// int numCommands;
	// cin >> numCommands;

	// for (int i = 0; i <= numCommands; i++) {
	// 	string line;
	// 	getline(cin, line);

	// 	istringstream in(line);

	// 	string command;
	// 	in >> command;

	// 	if (command == "insert") {
	// 		string next;
	// 		getline(in, next, '"');

	// 		string name;
	// 		in >> name;

	// 		regex valid("^[a-zA-Z]+$");
	// 		if (regex_match(name, valid)) {
	// 			string next;
	// 			getline(in, next, '"');

	// 			string ufid;
	// 			in >> ufid;

	// 			if (ufid.length() == 8) {
	// 				int id = stoi(ufid);
	// 				t.root = t.insert(t.root, name, id);
	// 				cout << "successful";
	// 			}
	// 		}
	// 	}

	// }

	
	
	BST t;
	t.root = nullptr;
	t.root = t.insert(t.root, "A", 10);
	t.root = t.insert(t.root, "B", 20);
	t.root = t.insert(t.root, "C", 30);
	t.root = t.insert(t.root, "C", 35);
	t.root = t.insert(t.root, "D", 40);
	t.root = t.insert(t.root, "E", 50);
	t.root = t.insert(t.root, "F", 60);
	t.searchId(t.root, 38);
	t.searchName(t.root, "C");

	t.printInorder(t.root);
	cout << endl;
	t.printPreorder(t.root);
	cout << endl;
	t.printPostorder(t.root); 
	cout << endl;
	t.printLevelCount(t.root);
}


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/