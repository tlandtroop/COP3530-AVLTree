#include <iostream>
using namespace std;

class BST {
	
	public:
		struct TreeNode {
			string name;
			string id;
			TreeNode* left;
			TreeNode* right;
			TreeNode* root;
			TreeNode() : name(""), id(""), left(nullptr), right(nullptr) {}
		};

		TreeNode* root = nullptr;
		
		// Rotations
		TreeNode* right(TreeNode* node);
		TreeNode* left(TreeNode* node);
		TreeNode* rightLeft(TreeNode* node);
		TreeNode* leftRight(TreeNode* node);

		// Manipulating functions
		void insert(string name, string id);
		void remove(string id);
		void searchId(string id);
		void searchName(string name);

		// Printing functions
		void printInorder();
		void printPreorder();
		void printPostorder();
		void printLevelCount(TreeNode* root);

		void removeInorder(int n);
	private:
		// Helper functions
		TreeNode* helperInsert(TreeNode* node, string name, string id);
		void helperInorder(TreeNode* helpRoot);
		void helperPreorder(TreeNode* helpRoot);
		void helperPostorder(TreeNode* helpRoot);
		int height(TreeNode* root);
		int getBalanceFactor(TreeNode* node);
};

// Helpers
BST::TreeNode* BST::helperInsert(TreeNode* node, string name, string id) { // TODO
	
}

void BST::helperInorder(BST::TreeNode* helpRoot) {
	if (helpRoot == nullptr)
		cout << "";
	else {
		helperInorder(helpRoot->left);
		cout << helpRoot->name << ", ";
		helperInorder(helpRoot->right);
	}
}

void BST::helperPreorder(BST::TreeNode* helpRoot) {
	if (helpRoot == nullptr)
		cout << "";
	else {
		cout << helpRoot->name << ", ";
		helperPreorder(helpRoot->left);
		helperPreorder(helpRoot->right);
	}
}

void BST::helperPostorder(BST::TreeNode* helpRoot) {
	if (helpRoot == nullptr)
		cout << "";
	else {
		cout << helpRoot->name << ", ";
		helperPreorder(helpRoot->left);
		helperPreorder(helpRoot->right);
	}
}

int BST::height(TreeNode* root) {
	if (root == nullptr)
		return 0;
	else {
		int left = height(root->left);
		int right = height(root->right);

		return max(left, right) + 1;
	}
}

int BST::getBalanceFactor(TreeNode* node) {
	if (node == nullptr)
		return -1;
	return height(node->left) - height(node->right);
}

// Rotations
BST::TreeNode* BST::right(TreeNode* node) {
	TreeNode* grandchild = node->left->right;
	TreeNode* newParent =  node->left;
	node->left = grandchild;
	return newParent;
}

BST::TreeNode* BST::left(TreeNode* node) {
	TreeNode* grandchild = node->right->left;
	TreeNode* newParent =  node->right;
	node->right = grandchild;
	return newParent;
}

BST::TreeNode* BST::rightLeft(TreeNode* node) { // TODO: First rotation on child
	node = right(node);
	return left(node);
}

BST::TreeNode* BST::leftRight(TreeNode* node) { // TODO: First rotation on child
	node = left(node);
	return right(node);
}

// Manipulative Functions
void BST::insert(string name, string id) { // TODO
	
}

void BST::remove(string id) { // TODO
	
}

void BST::searchId(string id) { // TODO
	
}

void searchName(string name) { // TODO
	
}

// Printing Functions
void BST::printInorder() {
	helperInorder(this->root);
}

void BST::printPreorder() {
	helperPreorder(this->root);
}

void BST::printPostorder() {
	helperPostorder(this->root);
}

void BST::printLevelCount(TreeNode* root) {
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
	t.insert("Andrew", "12345678");
	t.printInorder();
}


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/