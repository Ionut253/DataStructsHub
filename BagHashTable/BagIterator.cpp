#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <iostream>

using namespace std;

///  BC = WC = TC = theta(N) ; n = capacity 
BagIterator::BagIterator(const Bag& c) : bag(c)
{
	this->currentPosition = 0;
	this->b = new Node[bag.sizeOfBag];
	int position = 0;
	for (int i = 0; i < bag.capacity; i++) {
		Node* currentNode = bag.bag[i];
		while (currentNode != nullptr) {
			this->b[position].data = currentNode->data;
			position++;
			currentNode = currentNode->next;
		}
	}
}

/// BC = WC = TC = theta(1) 

void BagIterator::first() {
	this->currentPosition = 0;
}


/// BC = WC = TC = theta(N)
void BagIterator::next() {
	if (!this->valid())
		throw exception();
	this->currentPosition++;
}

/// BC = WC = TC = theta(1)
bool BagIterator::valid() const {
	return currentPosition < bag.size();
}


/// BC = WC = TC = theta(1)
TElem BagIterator::getCurrent() const
{
	if (!this->valid())
		throw exception();
	return this->b[currentPosition].data;
}
