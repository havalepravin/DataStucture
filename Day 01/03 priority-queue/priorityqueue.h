#pragma once

#include "vector.h"

class priorityqueue {
public:
	typedef unsigned int uint;
public:
	priorityqueue() {}
public:
	const int& top() {
		assert(m_vector.size() > 0);
		return m_vector[0];
	}
public:
	bool empty() {
		return m_vector.size() == 0;
	}
	size_t size() {
		return m_vector.size();
	}
public:
	void push(int value) {
		m_vector.push_back(value);
		push_heap();
	}
	void pop() {
		assert(size() > 0);
		pop_heap();
		m_vector.pop_back();
	}
private:
	void swap(int &first, int &second) {
		int temp = first;
		first = second;
		second = temp;
	}
	void push_heap() {
		uint last = m_vector.size() - 1;
		while(last > 0) {
			uint parent = (last - 1) / 2;
			if(m_vector[parent] < m_vector[last]) {
				swap(m_vector[parent], m_vector[last]);
			}
			last = parent;
		}
	}
	void pop_heap() {
		assert(size() > 0);
		uint last = m_vector.size() - 1;
		swap(m_vector[0], m_vector[last]);
		if(last > 0)
			last = last - 1;
		uint parent = 0;
		while(parent < last) {
			uint leftIndex = 2 * parent + 1;
			uint rightIndex = 2 * parent + 2;
			if(leftIndex > last)
				break;
			if(rightIndex > last) {
				if(m_vector[parent] < m_vector[leftIndex]) {
					swap(m_vector[parent], m_vector[leftIndex]);
				}
				parent = leftIndex;
			}
			else {
				if(m_vector[leftIndex] > m_vector[rightIndex]) {
					if(m_vector[parent] < m_vector[leftIndex]) {
						swap(m_vector[parent], m_vector[leftIndex]);
					}
					parent = leftIndex;
				}
				else {
					if(m_vector[parent] < m_vector[rightIndex]) {
						swap(m_vector[parent], m_vector[rightIndex]);
					}
					parent = rightIndex;
				}
			}
		}
	}
private:
	vector m_vector;
};