#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	BSTNode* current;
	int currentFrequency;

	BSTNode* findLeftMost(BSTNode* node);
	BSTNode* findSuccessor(BSTNode* node);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

