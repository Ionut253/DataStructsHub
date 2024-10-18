#include "SortedBag.h"
#include "SortedBagIterator.h"

#include <iostream>
using namespace std;


/// BC = WC = TC = theta(1)

SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->sizeOfBag = 0;
	this->root = nullptr;
}

void SortedBag::add_rec(BSTNode*& node, TComp e) {
	if (node == nullptr) {
		node = new BSTNode;
		node->info = e;
		node->left = nullptr;
		node->right = nullptr;
		node->frequency = 1;
	}
	else if (node->info == e) {
		node->frequency++;
	}
	else if (this->relation(e, node->info)) {
		add_rec(node->left, e);
	}
	else {
		add_rec(node->right, e);
	}
}


//BC = theta(1), WC = theta(n), TC = O(n)

void SortedBag::add(TComp e) {
	add_rec(root, e);
	this->sizeOfBag++;
}


//BC = theta(1), WC = theta(n), TC = O(n)

bool SortedBag::remove(TComp e) {
	if (this->root == nullptr) {
		return false;
	}
	BSTNode* currentNode = this->root;
	BSTNode* parentNode = nullptr;
	while (currentNode != nullptr && currentNode->info != e) {
		parentNode = currentNode;
		if (this->relation(e, currentNode->info)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	if (currentNode == nullptr) {
		return false;
	}
	if (currentNode->frequency > 1) {
		currentNode->frequency--;
		this->sizeOfBag--;
		return true;
	}
	if (currentNode->left == nullptr || currentNode->right == nullptr) {
		BSTNode* childNode = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
		if (parentNode == nullptr) {
			this->root = childNode;
		}
		else if (parentNode->left == currentNode) {
			parentNode->left = childNode;
		}
		else {
			parentNode->right = childNode;
		}
		delete currentNode;
	}
	else {
		BSTNode* successorParent = currentNode;
		BSTNode* successor = currentNode->right;
		while (successor->left != nullptr) {
			successorParent = successor;
			successor = successor->left;
		}
		currentNode->info = successor->info;
		currentNode->frequency = successor->frequency;
		if (successorParent->left == successor) {
			successorParent->left = successor->right;
		}
		else {
			successorParent->right = successor->right;
		}
		delete successor;
	}
	this->sizeOfBag--;
	return true;
}

/// BC = O(n), WC = theta(n), TC = O(n)

bool SortedBag::search(TComp elem) const {
	BSTNode* currentNode = this->root;
	while (currentNode != nullptr) {
		if (currentNode->info == elem) {
			return true;
		}
		if (this->relation(elem, currentNode->info)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	return false;
}

/// BC = O(n), WC = theta(n), TC = O(n)


int SortedBag::nrOccurrences(TComp elem) const {
	BSTNode* currentNode = this->root;
	while (currentNode != nullptr) {
		if (currentNode->info == elem) {
			return currentNode->frequency;
		}
		if (this->relation(elem, currentNode->info)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	return 0;
}

/// BC = WC = TC = theta(1)

int SortedBag::size() const {
	return this->sizeOfBag;
}

/// BC = WC = TC = theta(1)

bool SortedBag::isEmpty() const {
	return this->sizeOfBag == 0;
}

int SortedBag::distinctCount(BSTNode* node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + distinctCount(node->left) + distinctCount(node->right);
}

int SortedBag::distinctCount() {
	return distinctCount(this->root);
}

/// BC = WC = TC = theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


void SortedBag::destroyTree(BSTNode* node) {
	if (node == nullptr) {
		return;
	}
	destroyTree(node->left);
	destroyTree(node->right);
	delete node;
}

SortedBag::~SortedBag() {
	destroyTree(this->root);
}
