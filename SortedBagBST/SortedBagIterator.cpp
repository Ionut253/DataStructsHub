#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/// BC = WC = TC = theta(1)

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	first();
}

/// BC = WC = TC = O(n)

BSTNode* SortedBagIterator::findLeftMost(BSTNode* node) {
	while (node != nullptr && node->left != nullptr) {
		node = node->left;
	}
	return node;
}

/// BC = WC = TC = O(n)

BSTNode* SortedBagIterator::findSuccessor(BSTNode* node) {
    if (node->right != nullptr) {
        return findLeftMost(node->right);
    }
    BSTNode* successor = nullptr;
    BSTNode* ancestor = bag.root;
    while (ancestor != node) {
        if (bag.relation(node->info, ancestor->info)) {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

/// BC = WC = TC = theta(1)

TComp SortedBagIterator::getCurrent() {
	if (!this->valid()) {
		throw exception();
	}
	return this->current->info;

}

/// BC = WC = TC = theta(1)

bool SortedBagIterator::valid() {
	return this->current != nullptr;
}

/// BC = WC = TC = O(n)


void SortedBagIterator::next() {
    if (!valid()) {
        throw exception();
    }

    if (currentFrequency < current->frequency - 1) {
        currentFrequency++;
    }
    else {
        current = findSuccessor(current);
        currentFrequency = 0;
    }
}

/// BC = WC = TC = O(n)

void SortedBagIterator::first() {
	this->current = findLeftMost(this->bag.root);
	this->currentFrequency = 0;
}

