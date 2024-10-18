#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/// best case = worst case = total case = theta ( n + n * m)
/// n = capacity of the slla - number of keys
/// m = capacity of the slla of values - number of values


SortedMultiMap::SortedMultiMap(Relation r) {
	this->relation = r;
	this->capacity = 10;

	this->head = -1;
	this->firstEmpty = 0;
	this->nrElements = 0;

	this->slla = new SLLANode[this->capacity];
	for (int i = 0; i < this->capacity - 1; i++) {
		this->slla[i].next = i + 1;
	}
	this->slla[this->capacity - 1].next = -1;

	for (int i = 0; i < this->capacity; i++) {
		this->slla[i].elements = new KeyNode;
		this->slla[i].elements->capacity = 10;
		this->slla[i].elements->values = new TValue[this->slla[i].elements->capacity];
		this->slla[i].elements->head = -1;
		this->slla[i].elements->firstEmpty = 0;
		this->slla[i].elements->nrElem = 0;
		this->slla[i].elements->next = new int[this->slla[i].elements->capacity];
		for (int j = 0; j < this->slla[i].elements->capacity - 1; j++) {
			this->slla[i].elements->next[j] = j + 1;
		}
		this->slla[i].elements->next[this->slla[i].elements->capacity - 1] = -1;
	}

}


/// best case = theta (1)
/// worst case = O ( n + m )
/// total case = O ( n + m )
/// n = number of keys
/// m = number of values


void SortedMultiMap::add(TKey c, TValue v) {

	/// if the slla is empty => add the first key
	if (this->nrElements == 0) {
		this->slla[0].key = c;
		this->slla[0].next = -1;
		this->head = 0;
		this->firstEmpty = 1;
		this->nrElements++;
		this->slla[0].elements->values[0] = v;
		this->slla[0].elements->head = 0;
		this->slla[0].elements->firstEmpty = 1;
		this->slla[0].elements->nrElem = 1;
		this->slla[0].elements->next[0] = -1;
		return;
	}

	/// if the slla is not empty => search for the key
	int current = this->head;
	int keyIndex = -1;
	while (current != -1) {
		if (this->slla[current].key == c && this->relation(this->slla[current].key,c)) {
			keyIndex = current;
			break;
		}
		current = this->slla[current].next;
	}
	if (keyIndex != -1) {
		/// key exists => add value to it's slla of values
		KeyNode& keyNode = *this->slla[keyIndex].elements;

		/// if the slla of values is full => resize it
		if (keyNode.firstEmpty == -1) {
			TValue* newValues = new TValue[keyNode.capacity * 2];
			int* newNext = new int[keyNode.capacity * 2];

			for (int i = 0; i < keyNode.capacity; i++) {
				newValues[i] = keyNode.values[i];
				newNext[i] = keyNode.next[i];
			}
			for (int i = keyNode.capacity; i < keyNode.capacity * 2 - 1; i++) {
				newNext[i] = i + 1;
			}
			newNext[keyNode.capacity * 2 - 1] = -1;

			/// delete the old arrays
			delete[] keyNode.values;
			delete[] keyNode.next;
			keyNode.values = newValues;
			keyNode.next = newNext;
			keyNode.firstEmpty = keyNode.capacity;
			keyNode.capacity *= 2;
		}

		int indexEmpty = keyNode.firstEmpty;
		
		/// add the value to the slla of values
		keyNode.firstEmpty = keyNode.next[indexEmpty];
		keyNode.values[indexEmpty] = v;
		keyNode.next[indexEmpty] = -1;
		if (keyNode.head == -1) {
			keyNode.head = indexEmpty;
		}
		else {
			int currentKeyNode = keyNode.head;
			int prevKeyNode = -1;

			while (currentKeyNode != -1) {
				prevKeyNode = currentKeyNode;
				currentKeyNode = keyNode.next[currentKeyNode];
			}

			if (prevKeyNode == -1) {
				keyNode.next[indexEmpty] = keyNode.head;
				keyNode.head = indexEmpty;
			}

			else {
				keyNode.next[indexEmpty] = keyNode.next[prevKeyNode];
				keyNode.next[prevKeyNode] = indexEmpty;
			}
		}
		keyNode.nrElem++;
		this->nrElements++;
	}
	else {
		/// key does not exist => add a new key
		if (this->firstEmpty == -1) {
			/// resize the slla of keys
			SLLANode* newSlla = new SLLANode[this->capacity * 2];
			for (int i = 0; i < this->capacity; i++) {
				newSlla[i] = this->slla[i];
			}
			for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
				newSlla[i].next = i + 1;
			}
			newSlla[this->capacity * 2 - 1].next = -1;
			delete[] this->slla;
			this->slla = newSlla;
			this->firstEmpty = this->capacity;
			this->capacity *= 2;
		}

		int index = this->firstEmpty;
		this->firstEmpty = this->slla[index].next;

		this->slla[index].key = c;
		this->slla[index].elements = new KeyNode();
		this->slla[index].elements->capacity = 10;
		this->slla[index].elements->values = new TValue[this->slla[index].elements->capacity];
		this->slla[index].elements->head = -1;
		this->slla[index].elements->firstEmpty = 0;
		this->slla[index].elements->nrElem = 0;
		this->slla[index].elements->next = new int[this->slla[index].elements->capacity];
		for (int i = 0; i < this->slla[index].elements->capacity - 1; i++) {
			this->slla[index].elements->next[i] = i + 1;
		}
		this->slla[index].elements->next[this->slla[index].elements->capacity - 1] = -1;

		/// add the value to the slla of values

		int indexEmpty = this->slla[index].elements->firstEmpty;
		this->slla[index].elements->firstEmpty = this->slla[index].elements->next[indexEmpty];
		this->slla[index].elements->values[indexEmpty] = v;

		this->slla[index].elements->next[indexEmpty] = -1;
		this->slla[index].elements->head = indexEmpty;
		this->slla[index].elements->nrElem++;
		this->slla[index].next = -1;


		/// link the key to the slla of keys

		if (this->head == -1) {
			this->head = index;
		}
		else {
			int current = this->head;
			int prev = -1;
			while (current != -1 && this->relation(this->slla[current].key, c)) {
				prev = current;
				current = this->slla[current].next;
			}
			if (prev == -1) {
				this->slla[index].next = this->head;
				this->head = index;
			}
			else {
				this->slla[prev].next = index;
				this->slla[index].next = current;
			}
		}
		this->nrElements++;

	}
}

/// best case = theta (1)
/// worst case = theta ( n + m )
/// total case = O ( n + m )
/// n = number of keys
/// m = number of values

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	int current = this->head;
	int keyIndex = -1;


	/// search for the key
	while (current != -1) {
		if (this->slla[current].key == c) {
			keyIndex = current;
			break;
		}
		current = this->slla[current].next;
	}

	/// if the key exists => get the values
	if (keyIndex != -1) {
		int currentKeyNode = this->slla[keyIndex].elements->head;
		while (currentKeyNode != -1) {
			values.push_back(this->slla[keyIndex].elements->values[currentKeyNode]);
			currentKeyNode = this->slla[keyIndex].elements->next[currentKeyNode];
		}
	}

	return values;
}


/// best case = theta (1)
/// worst case = theta ( n + m )
/// total case = O ( n + m )
/// n = number of keys
///	m = number of values

bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = this->head;
	int keyIndex = -1;

	/// search for the key
	while (current != -1) {
		if (this->slla[current].key == c) {
			keyIndex = current;
			break;
		}
		current = this->slla[current].next;
	}
	if (keyIndex != -1) {
		/// key exists => remove value from it's slla of values
		int currentKey = keyIndex;
		int currentKeyNode = this->slla[currentKey].elements->head;
		int prevKeyNode = -1;
		while (currentKeyNode != -1) {
			if (this->slla[currentKey].elements->values[currentKeyNode] == v) {
				if (prevKeyNode == -1) {
					this->slla[currentKey].elements->head = this->slla[currentKey].elements->next[currentKeyNode];
				}
				else {
					this->slla[currentKey].elements->next[prevKeyNode] = this->slla[currentKey].elements->next[currentKeyNode];
				}
				this->slla[currentKey].elements->next[currentKeyNode] = this->slla[currentKey].elements->firstEmpty;
				this->slla[currentKey].elements->firstEmpty = currentKeyNode;
				this->slla[currentKey].elements->nrElem--;
				this->nrElements--;
				
				if (this->slla[currentKey].elements->nrElem == 0) {
					/// the key has no values => remove the key
					if (currentKey == this->head) {
						this->head = this->slla[currentKey].next;
					}
					else {
						int prev = this->head;
						while (this->slla[prev].next != currentKey) {
							prev = this->slla[prev].next;
						}
						this->slla[prev].next = this->slla[currentKey].next;
					}
					this->slla[currentKey].next = this->firstEmpty;
					this->firstEmpty = currentKey;
					delete[] this->slla[currentKey].elements->values;
					delete[] this->slla[currentKey].elements->next;
					delete this->slla[currentKey].elements;
				}
				return true;

			}
			prevKeyNode = currentKeyNode;
			currentKeyNode = this->slla[currentKey].elements->next[currentKeyNode];
		}
	}
	return false;
}

/// best case = worst case = total case = theta (1)

int SortedMultiMap::size() const {
	return this->nrElements;
}

/// best case = worst case = total case = theta (1)

bool SortedMultiMap::isEmpty() const {
	return this->nrElements == 0;
}


SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/// best case = worst case = total case = theta ( n )
/// n = number of keys

SortedMultiMap::~SortedMultiMap() {
	int current = this->head;
	while (current != -1) {
		if (this->slla[current].next != -1) {
			delete[] this->slla[current].elements->values;
			delete[] this->slla[current].elements->next;
			delete this->slla[current].elements;
		}
		current = this->slla[current].next;
	}
	delete[] this->slla;
}


int SortedMultiMap::trimValues(int maxValues) {

	if (maxValues < 1) 
		throw exception();

	int currentK = this->head;
	int valuesRemoved = 0;

	while (currentK != -1) {
		KeyNode& keyNode = *this->slla[currentK].elements;

		for (int i = 0; i < keyNode.nrElem; i++) {
			cout << "Values: " << keyNode.values[i]<<endl;
			}

		if (this->slla[currentK].elements->nrElem > maxValues) {

			int current = keyNode.head;



			/// remove values from the slla of values until it has same number of values as maxValues
			while ( keyNode.nrElem != maxValues) {
				

				keyNode.head = keyNode.next[current];
				keyNode.next[current] = keyNode.firstEmpty;
				keyNode.firstEmpty = current;
				keyNode.nrElem--;
				this->nrElements--;
				valuesRemoved++;

			}

		}
		currentK = this->slla[currentK].next;
		cout<<"------------------------"<<endl;
	}

	return valuesRemoved;

}