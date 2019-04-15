#pragma once

#include <assert.h>

class vector {
public:
	class iterator {
	public:
		iterator() : m_pvector(nullptr), m_pos(0) {}
		iterator(vector *pvector, size_t pos) : m_pvector(pvector), m_pos(pos) {}
	public:
		iterator& operator++() {
			assert(m_pos != m_pvector->m_size);
			m_pos++;
			return *this;
		}
		iterator& operator--() {
			assert(m_pos != 0);
			m_pos--;
			return *this;
		}
	public:
		int& operator*() {
			assert(m_pos != m_pvector->m_size);
			return m_pvector->m_pdata[m_pos];
		}
	public:
		bool operator==(const iterator &it) { return (m_pvector == it.m_pvector && m_pos == it.m_pos); }
		bool operator!=(const iterator &it) { return !(*this == it); }
	private:
		vector *m_pvector;
		size_t m_pos;
	};
public:
	vector() : m_size(0), m_capacity(0), m_pdata(nullptr) {}
	~vector() { delete[] m_pdata; m_pdata = nullptr; } // delete will not call destructor(in case of non scalar elements) for every element in array instead use delete[]
public:
	int& operator[](int index) {
		assert(m_size > 0);
		return m_pdata[index];
	}
	int& front() {
		assert(m_size > 0);
		return m_pdata[0];
	}
	int& back() {
		assert(m_size > 0);
		return m_pdata[m_size - 1];
	}
public:
	iterator begin() {
		return iterator(this, 0);
	}
	iterator end() {
		return iterator(this, m_size);
	}
public:
	bool empty() {
		return 0 == m_size;
	}
	size_t size() {
		return m_size;
	}
public:
	void push_back(int value) {
		if(m_size == m_capacity) relocate();
		m_pdata[m_size] = value;
		m_size++;
	}
	void pop_back() {
		m_size--;
	}
private:
	void relocate() {
		m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
		int *temp = new int[m_capacity];
		for(size_t index = 0; index < m_size; index++) {
			temp[index] = m_pdata[index];
		}
		delete[] m_pdata;
		m_pdata = temp;
	}
private:
	size_t m_size;
	size_t m_capacity;
private:
	int *m_pdata;
};