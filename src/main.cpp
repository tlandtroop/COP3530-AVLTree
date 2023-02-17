#include <algorithm>
#include <iostream>
#include <ratio>
using namespace std;

class BST {
	public:
		struct TreeNode {
			string name;
			int id;
			int height;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : name(""), id(0), left(nullptr), right(nullptr) {}
		};
		TreeNode* root;
		
		// Rotations
		TreeNode* right(TreeNode* node);
		TreeNode* left(TreeNode* node);
		TreeNode* rightLeft(TreeNode* node);
		TreeNode* leftRight(TreeNode* node);

		// Manipulating functions
		TreeNode* insert(TreeNode* root,string name, int id);
		void remove(TreeNode* root, int id);
		void searchId(TreeNode* root, int id);
		void searchName(TreeNode* root, string name);

		// Printing functions
		void printInorder(TreeNode* root);
		void printPreorder(TreeNode* root);
		void printPostorder(TreeNode* root);
		void printLevelCount(TreeNode* root);
		void removeInorder(int n);

	private:
		// Helper functions
		int height(TreeNode* root);
		int getBalanceFactor(TreeNode* node);
		TreeNode* createNode(string name, int id);
};

// Helpers
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

BST::TreeNode* BST::createNode(string name, int id) { // DONE
	TreeNode* node = new TreeNode();
	node->id = id;
	node->name = name;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;

	return node;
}

// Rotations
BST::TreeNode* BST::right(TreeNode* root) { // DONE
	TreeNode* grandchild = root->left->right;
	TreeNode* newParent =  root->left;
	newParent->right = root;
	root->left = grandchild;
	return newParent;
}

BST::TreeNode* BST::left(TreeNode* root) { // DONE
	TreeNode* grandchild = root->right->left;
	TreeNode* newParent =  root->right;
	newParent->left = root;
	root->right = grandchild;
	return newParent;
}

BST::TreeNode* BST::rightLeft(TreeNode* root) { // DONE
	root->right = right(root->right);
	return left(root);
}

BST::TreeNode* BST::leftRight(TreeNode* root) { // DONE
	root->left = left(root->left);
	return right(root);
}

// Manipulative Functions
BST::TreeNode* BST::insert(TreeNode* root, string name, int id) { // DONE
	if (root == nullptr) {
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

void BST::remove(TreeNode* root, int id) { // FIXME
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
	}
	else if (id < root->id) {
		remove(root->left, id);
	}
	else if (id > root->id) {
		remove(root->right, id);
	}
	else {
		if (root->left == nullptr) {
			delete root;
			cout << "successful" << endl;
		}
		else if (root->right == nullptr) {
			delete root;
			cout << "successful" << endl;
		}
		else {
			TreeNode* current = root->right;
			while (current->left != nullptr) {
				current = current->left;
			}
			root->id = current->id;
			root->name = current->name;
			remove(root->right, current->id);
		}

	}

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

void BST::searchName(TreeNode* root, string name) { // FIXME
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
	}
	else if (name == root->name) {
		cout << root->id << endl;
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
	if (root == nullptr)
		cout << "";
	else {
		printInorder(root->left);
		cout << root->name << ", ";
		printInorder(root->right);
	}
}

void BST::printPreorder(TreeNode* root) { // DONE
	if (root == nullptr)
		cout << "";
	else {
		cout << root->id << ", ";
		printPreorder(root->left);
		printPreorder(root->right);
	}
}

void BST::printPostorder(TreeNode* root) { // DONE
	if (root == nullptr)
		cout << "";
	else {
		printPostorder(root->left);
		printPostorder(root->right);
		cout << root->name << ", ";
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
	// TODO: Parsing and inputs
	BST t;
	t.root = nullptr;
	t.root = t.insert(t.root, "A", 10);
	t.root = t.insert(t.root, "B", 20);
	t.root = t.insert(t.root, "C", 30);
	t.root = t.insert(t.root, "D", 40);
	t.root = t.insert(t.root, "E", 50);
	t.root = t.insert(t.root, "F", 25);
	t.remove(t.root, 25);
	t.searchId(t.root, 50);
	t.searchName(t.root, "C");
	
	
	t.printPreorder(t.root);
}


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/