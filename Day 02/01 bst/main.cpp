#include <crtdbg.h>
#include <iostream>
#include "bst.h"
#include <set>

void TestIterator() {
	bst bst;
	int values[31] = { 16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 };
	for(int i = 0; i < 31; i++) {
		bst.insert(values[i]);
	}
	// test it.operator++()
	int i = 1;
	bst::iterator it = bst.begin();
	while(it != bst.end()) {
		assert(*it == i);
		++it;
		++i;
	}
	// test it.operator--()
	i = 31;
	it = bst.end();
	while(it != bst.begin()) {
		--it;
		assert(*it == i);
		--i;
	}
}

void TestDelete() {
	bst bst;
	int values[31] = { 16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 };
	for(int i = 0; i < 31; i++) {
		bst.insert(values[i]);
	}
	// delete leaf node
	bst.erase(bst.find(9));
	assert(bst.find(9) == bst.end());
	// delete node with right subtree
	bst.erase(bst.find(10));
	assert(bst.find(10) == bst.end());
	// delete node with both subtrees
	bst.erase(bst.find(8));
	assert(bst.find(8) == bst.end());
	// delete root
	bst.erase(bst.find(16));
	assert(bst.find(16) == bst.end());
	// delete node with left subtree
	bst.erase(bst.find(23));
	assert(bst.find(23) == bst.end());
	bst.erase(bst.find(22));
	assert(bst.find(22) == bst.end());
}

int main() {
	TestIterator();
	TestDelete();
	_CrtDumpMemoryLeaks();
}