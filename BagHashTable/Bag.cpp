#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <math.h>
using namespace std;

//BC = WC = TC = theta(m) ; m = capacity
Bag::Bag() {
	this->capacity = 10;
	this->sizeOfBag = 0;
	this->bag = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->bag[i] = NULL;
	}
}

//BC = WC = TC = theta(1)
int Bag::hashFunction(TElem elem) const {
	return abs(elem) % this->capacity;
}


//BC = WC = TC = theta(m + k*n) ; m = new capacity ; k = initial capacity ; n = sizeOfBag


void Bag::resize() {
	this->capacity *= 2;
	Node** newB = new Node * [this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		newB[i] = nullptr;
	}
	for (int i = 0; i < this->capacity / 2; i++) {
		Node* currentNode = this->bag[i];
		while (currentNode != nullptr) {
			/// rehashing the elements
			int position = this->hashFunction(currentNode->data);
			Node* newNode = new Node;
			newNode->data = currentNode->data;
			newNode->next = newB[position];
			newB[position] = newNode;
			currentNode = currentNode->next;
		}
	}
	delete[] this->bag;
	this->bag = newB;

	
}


//  BC = theta(1) 
//  WC = theta(n + k*n) resize() is called , n = sizeOfBag
//  TC = O(n + k*n) resize() is called, n = sizeOfBag

void Bag::add(TElem elem) {
	if ((double)this->sizeOfBag / this->capacity > 0.7) {
		this->resize();
	}
	int position = this->hashFunction(elem);
	Node* currentNode = this->bag[position];
	Node* previousNode = nullptr;
	while (currentNode != nullptr) {
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	Node* newNode = new Node;
	newNode->data = elem;
	newNode->next = nullptr;
	if (previousNode == nullptr) {
		this->bag[position] = newNode;
	}
	else {
		previousNode->next = newNode;
	}
	this->sizeOfBag++;

}

// BC = theta(1)
// WC = theta(sizeOfBag)
// TC = O(sizeOfBag)

bool Bag::remove(TElem elem) {
	int position = this->hashFunction(elem);
	Node* currentNode = this->bag[position];
	Node* previousNode = nullptr;
	while (currentNode != nullptr) {
		if (currentNode->data == elem) {
			Node* node = currentNode;
			if (previousNode == nullptr) {
				this->bag[position] = currentNode->next;
			}
			else {
				previousNode->next = currentNode->next;
			}
			delete node;
			this->sizeOfBag--;
			return true;
		
		}
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	return false; 
}

// BC = theta(1)
// WC = theta(sizeOfBag)
// TC = O(sizeOfBag)


bool Bag::search(TElem elem) const {
	int position = this->hashFunction(elem);
	Node* currentNode = this->bag[position];
	while (currentNode != nullptr) {
		if (currentNode->data == elem) {
			return true;
		}
		currentNode = currentNode->next;
	}
	return false;
}

// BC = WC = TC = theta(sizeOfBag)

int Bag::nrOccurrences(TElem elem) const {
	int position = this->hashFunction(elem);
	int count = 0;
	Node* currentNode = this->bag[position];
	
	while (currentNode != nullptr) {
		if (currentNode->data == elem) {
			count++;
		}
		currentNode = currentNode->next;
	}

	return count;
}

// BC = WC = TC = theta(1)
int Bag::size() const {
	return this->sizeOfBag;
}

// BC = WC = TC = theta(1)
bool Bag::isEmpty() const {
	return this->sizeOfBag == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

int Bag::getRange() const {
	if (this->sizeOfBag == 0)
		return -1;
	int min = 0, max = 0;
	for (int i = 0; i < this->capacity; i++){
		Node* currentNode = this->bag[i];
		while (currentNode != nullptr) {
			if (currentNode->data < min)
				min = currentNode->data;
			if (currentNode->data > max)
				max = currentNode->data;
			currentNode = currentNode->next;			
		}
	}
	return max - min;
}


//BC = WC = TC = theta(k*n) ; k = capacity ; n = sizeOfBag
Bag::~Bag() {
	for (int i = 0; i < this->capacity; i++) {
		Node* currentNode = this->bag[i];
		Node* previousNode = nullptr;
		while (currentNode != nullptr) {
			previousNode = currentNode;
			currentNode = currentNode->next;
			delete previousNode;
		}
	}
	delete[] this->bag;

}

