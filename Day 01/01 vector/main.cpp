#include <crtdbg.h>
#include <iostream>
#include "vector.h"

void TestPushBack() {
	vector v;
	vector::iterator it;
	int i = 0;
	for(i = 1; i <= 10; i++) {
		v.push_back(i);
	}
	for(it = v.begin(), i = 1; it != v.end(); ++it, i++) {
		assert(*it == i);
	}
}

void TestPopBack() {
	vector v;
	v.push_back(1);
	v.pop_back();
	assert(v.empty());

	for(int i = 1; i <= 10; i++) {
		v.push_back(i);
	}

	for(int i = 1; i <= 10; i++) {
		v.pop_back();
	}
	assert(v.empty());
}

void TestFrontAndBack() {
	vector v;
	for(int i = 1; i <= 10; i++) {
		v.push_back(i);
	}
	assert(v.front() == 1 && v.back() == 10);
}

void TestIterator() {
	vector v;
	vector::iterator it;
	int i = 0;
	for(i = 1; i <= 10; i++) {
		v.push_back(i);
	}

	it = v.begin();
	for(i = 1; i <= 10; i++) {
		assert(*it == i);
		++it;
	}

	it = v.end();
	for(i = 10; i >= 1; i--) {
		--it;
		assert(*it == i);
	}
}

int main() {
	TestPushBack();
	TestPopBack();
	TestFrontAndBack();
	TestIterator();
	_CrtDumpMemoryLeaks();
}