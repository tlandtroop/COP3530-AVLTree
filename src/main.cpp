#include <iostream>
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
		void remove(int id);
		void searchId(int id);
		void searchName(string name);

		// Printing functions
		void printInorder();
		void printPreorder();
		void printPostorder();
		void printLevelCount(TreeNode* root);
		void removeInorder(int n);

	private:
		// Helper functions
		void helperInorder(TreeNode* helpRoot);
		void helperPreorder(TreeNode* helpRoot);
		void helperPostorder(TreeNode* helpRoot);
		int height(TreeNode* root);
		int getBalanceFactor(TreeNode* node);
		TreeNode* createNode(string name, int id);
};

// Helpers
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
		cout << helpRoot->id << ", ";
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
		return 0;
	return height(node->left) - height(node->right);
}

BST::TreeNode* BST::createNode(string name, int id) {
	TreeNode* node = new TreeNode();
	node->id = id;
	node->name = name;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;

	return node;
}

// Rotations
BST::TreeNode* BST::right(TreeNode* root) {
	TreeNode* grandchild = root->left->right;
	TreeNode* newParent =  root->left;
	newParent->right = root;
	root->left = grandchild;
	return newParent;
}

BST::TreeNode* BST::left(TreeNode* root) {
	TreeNode* grandchild = root->right->left;
	TreeNode* newParent =  root->right;
	root->right = grandchild;
	root = newParent;
	return newParent;
}

BST::TreeNode* BST::rightLeft(TreeNode* root) { // TODO: First rotation on child
	root = right(root->right);
	root = left(root);
	return root;
}

BST::TreeNode* BST::leftRight(TreeNode* root) { // TODO: First rotation on child
	root = left(root->left);
	root = right(root);
	return root;
}

// Manipulative Functions
BST::TreeNode* BST::insert(TreeNode* root, string name, int id) { // TODO
	if (root == nullptr) {
		return createNode(name, id);
	}

	if (id < root->id) {
		root->left = insert(root->left, name, id);
	}
	else if (id > root->id) {
		root->right = insert(root->right, name, id);
	}

	int balanceFactor = getBalanceFactor(root);

	// Left Left
	if (balanceFactor == 2 && getBalanceFactor(root->left) == 1) {
		return right(root);
	}
	// Right Right
	if (balanceFactor == -2 && getBalanceFactor(root->right) == -1) {
		return left(root);
	}

	// Left Right
	if (balanceFactor == 2 && getBalanceFactor(root->left) == -1) {
		return leftRight(root);
	}

	// Right Left
	if (balanceFactor == -2 && getBalanceFactor(root->right) == 1) {
		return rightLeft(root);
	}

	return root;
}

void BST::remove(int id) { // TODO
	
}

void BST::searchId(int id) { // TODO
	
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
	t.root = nullptr;
	t.root = t.insert(t.root, "A", 10);
	t.root = t.insert(t.root, "B", 20);
	t.root = t.insert(t.root, "C", 30);
	t.root = t.insert(t.root, "D", 40);
	t.root = t.insert(t.root, "E", 50);
	t.root = t.insert(t.root, "F", 25);
	t.printPreorder();
}


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/