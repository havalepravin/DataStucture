#pragma once

#include<assert.h>

class list {
private:
	struct Node {
		int m_value;
		Node *m_pprevNode;
		Node *m_pnextNode;
	public:
		Node() : m_pprevNode(nullptr), m_pnextNode(nullptr) {}
		Node(int value) : m_value(value), m_pprevNode(nullptr), m_pnextNode(nullptr) {}
	};
public:
	class iterator {
	public:
		iterator() : m_plist(nullptr), m_pnode(nullptr) {}
		iterator(list *plist, Node *pnode) : m_plist(plist), m_pnode(pnode) {}
	public:
		iterator& operator++() {
			assert(m_pnode != m_plist->m_ptail);
			m_pnode = m_pnode->m_pnextNode;
			return *this;
		}
		iterator& operator--() {
			assert(m_pnode != m_plist->m_phead);
			m_pnode = m_pnode->m_pprevNode;
			return *this;
		}
	public:
		int& operator*() {
			assert(m_pnode != m_plist->m_ptail);
			return m_pnode->m_value;
		}
	public:
		bool operator==(const iterator &it) { return (m_plist == it.m_plist && m_pnode == it.m_pnode); }
		bool operator!=(const iterator &it) { return !(*this == it); }
	private:
		list *m_plist;
		Node *m_pnode;
	};
public:
	list() : m_size(0) {
		m_phead = m_ptail = new Node();
	}
	~list() {
		while(m_size > 0)
			pop_front();
		delete m_ptail; m_ptail = nullptr;
	}
public:
	int& front() {
		assert(m_size > 0);
		return m_phead->m_value;
	}
	int& back() {
		assert(m_size > 0);
		return m_ptail->m_pprevNode->m_value;
	}
public:
	iterator begin() {
		return iterator(this, m_phead);
	}
	iterator end() {
		return iterator(this, m_ptail);
	}
public:
	bool empty() {
		return 0 == m_size;
	}
	bool size() {
		return m_size;
	}
public:
	void push_back(int value) {
		if(m_size == 0) return push_front(value);
		Node *pnewNode = new Node(value);
		Node *plastNode = m_ptail->m_pprevNode;
		plastNode->m_pnextNode = pnewNode;
		pnewNode->m_pprevNode = plastNode;
		pnewNode->m_pnextNode = m_ptail;
		m_ptail->m_pprevNode = pnewNode;
		m_size++;
	}
	void pop_back() {
		assert(m_size > 0);
		if(m_size == 1) return pop_front();
		Node *pdelNode = m_ptail->m_pprevNode;
		Node *ptobelastNode = pdelNode->m_pprevNode;
		ptobelastNode->m_pnextNode = m_ptail;
		m_ptail->m_pprevNode = ptobelastNode;
		pdelNode->m_pprevNode = pdelNode->m_pnextNode = nullptr;
		delete pdelNode;  pdelNode = nullptr;
		m_size--;
	}
	void push_front(int value) {
		Node *pnewNode = new Node(value);
		pnewNode->m_pnextNode = m_phead;
		m_phead->m_pprevNode = pnewNode;
		m_phead = pnewNode;
		m_size++;
	}
	void pop_front() {
		assert(m_size > 0);
		Node *pdelNode = m_phead;
		m_phead = m_phead->m_pnextNode;
		m_phead->m_pprevNode = nullptr;
		pdelNode->m_pprevNode = pdelNode->m_pnextNode = nullptr;
		delete pdelNode; pdelNode = nullptr;
		m_size--;
	}
private:
	size_t m_size;
private:
	Node *m_phead;
	Node *m_ptail;
};