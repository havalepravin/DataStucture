#include <crtdbg.h>
#include <iostream>
#include "list.h"

void TestPushBack() {
	list l;
	list::iterator it;
	int i = 0;
	for(i = 1; i <= 10; i++) {
		l.push_back(i);
	}
	for(it = l.begin(), i = 1; it != l.end(); ++it, i++) {
		assert(*it == i);
	}
}

void TestPushFront() {
	list l;
	list::iterator it;
	int i = 0;
	for(i = 1; i <= 10; i++) {
		l.push_front(i);
	}
	for(it = l.begin(), i = 10; it != l.end(); ++it, i--) {
		assert(*it == i);
	}
}

void TestPopBack() {
	list l;
	l.push_back(1);
	l.pop_back();
	assert(l.empty());

	for(int i = 1; i <= 10; i++) {
		l.push_back(i);
	}

	for(int i = 1; i <= 10; i++) {
		l.pop_back();
	}
	assert(l.empty());
}

void TestPopFront() {
	list l;
	l.push_back(1);
	l.pop_back();
	assert(l.empty());

	for(int i = 1; i <= 10; i++) {
		l.push_front(i);
	}

	for(int i = 1; i <= 10; i++) {
		l.pop_front();
	}
	assert(l.empty());
}

void TestFrontAndBack() {
	list l;
	for(int i = 1; i <= 10; i++) {
		l.push_back(i);
	}
	assert(l.front() == 1 && l.back() == 10);
}

void TestIterator() {
	list l;
	list::iterator it;
	int i = 0;
	for(i = 1; i <= 10; i++) {
		l.push_back(i);
	}

	it = l.begin();
	for(i = 1; i <= 10; i++) {
		assert(*it == i);
		++it;
	}

	it = l.end();
	for(i = 10; i >= 1; i--){
		--it;
		assert(*it == i);
	}
}

int main() {
	TestPushBack();
	TestPushFront();
	TestPopBack();
	TestPopFront();
	TestFrontAndBack();
	TestIterator();
	_CrtDumpMemoryLeaks();
}