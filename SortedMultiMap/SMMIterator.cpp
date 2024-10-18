#include "SMMIterator.h"
#include "SortedMultiMap.h"


/// best case = worst case = total case = theta (1)

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	if (this->map.head == -1) {
		this->currentKey = -1;
		this->currentValue = -1;
		return;
	}
	this->currentKey = this->map.head;
	this->currentValue = this->map.slla[this->map.head].elements->head;
}

/// best case = worst case = total case = theta (1)

void SMMIterator::first(){
	if (this->map.head == -1) {
		this->currentKey = -1;
		this->currentValue = -1;
		return;
	}
	this->currentKey = this->map.head;
	this->currentValue = this->map.slla[this->map.head].elements->head;
}

/// best case = worst case = total case = theta (1)

void SMMIterator::next(){
	if (!this->valid())
		throw exception();
	if (this->map.slla[this->currentKey].elements->next[this->currentValue] != -1)
		this->currentValue = this->map.slla[this->currentKey].elements->next[this->currentValue];
	else {
		this->currentKey = this->map.slla[this->currentKey].next;
		if (this->currentKey != -1)
			this->currentValue = this->map.slla[this->currentKey].elements->head;
		else
			this->currentValue = -1;
	}
}

/// best case = worst case = total case = theta (1)

bool SMMIterator::valid() const{
	if (this->currentKey == -1 && this->currentValue == -1)
		return false;
	return true;
}

/// best case = worst case = total case = theta (1)


TElem SMMIterator::getCurrent() const{
	if (!this->valid())
		throw exception();
	TValue value = this->map.slla[this->currentKey].elements->values[this->currentValue];
	TKey key = this->map.slla[this->currentKey].key;
	return TElem(key, value);

}


