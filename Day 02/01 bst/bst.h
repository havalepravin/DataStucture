#pragma once

#include <assert.h>

class bst {
private:
	struct Node {
		int m_value;
		Node *m_pparent;
		Node *m_pleft;
		Node *m_pright;
	public:
		Node() : m_pparent(nullptr), m_pleft(nullptr), m_pright(nullptr) {}
		Node(int value, Node *pparent) : m_value(value), m_pparent(pparent), m_pleft(nullptr), m_pright(nullptr) {}
		Node(int value, Node *pparent, Node *pleft, Node *pright) : m_value(value), m_pparent(pparent), m_pleft(pleft), m_pright(pright) {}
	};
public:
	class iterator {
	public:
		iterator() : m_pbst(nullptr), m_pnode(nullptr) {}
		iterator(bst *pbst, Node *pnode) : m_pbst(pbst), m_pnode(pnode) {}
	public:
		iterator& operator++() {
			assert(m_pnode != m_pbst->m_pend);
			Node *pparent = nullptr;
			if(m_pnode->m_pright == nullptr) {
				pparent = m_pnode->m_pparent;
				while(m_pnode == pparent->m_pright) {
					m_pnode = pparent;
					pparent = m_pnode->m_pparent;
				}
				m_pnode = pparent;
				return *this;
			}
			m_pnode = m_pnode->m_pright;
			while(m_pnode->m_pleft != nullptr)
				m_pnode = m_pnode->m_pleft;
			return *this;
		}
		iterator& operator--() {
			assert(m_pnode != m_pbst->m_pbegin);
			Node *pparent = nullptr;
			if(m_pnode->m_pleft == nullptr) {
				pparent = m_pnode->m_pparent;
				while(m_pnode == pparent->m_pleft) {
					m_pnode = pparent;
					pparent = m_pnode->m_pparent;
				}
				m_pnode = pparent;
				return *this;
			}
			m_pnode = m_pnode->m_pleft;
			while(m_pnode->m_pright != nullptr)
				m_pnode = m_pnode->m_pright;
			return *this;
		}
	public:
		// iterator is immutable
		const int& operator*() {
			assert(m_pnode != m_pbst->m_pend);
			return m_pnode->m_value;
		}
	public:
		bool operator==(const iterator &it) { return (m_pbst == it.m_pbst && m_pnode == it.m_pnode); }
		bool operator!=(const iterator &it) { return !(*this == it); }
	private:
		bst *m_pbst;
		Node *m_pnode;
		friend class bst;
	};
public:
	bst() : m_size(0) {
		m_pbegin = m_pend = m_proot = new Node();
	}
	~bst() {
		while(m_size > 0)
			erase(iterator(this, m_proot));
		delete m_proot;
		m_proot = nullptr;
	}
public:
	iterator begin() {
		return iterator(this, m_pbegin);
	}
	iterator end() {
		return iterator(this, m_pend);
	}
public:
	bool empty() {
		return 0 == m_size;
	}
	size_t size() {
		return m_size;
	}
public:
	void insert(int value) {
		Node *pwalker = m_proot, *pparent = nullptr;
		while(pwalker != nullptr && pwalker != m_pend) {
			pparent = pwalker;
			if(value < pwalker->m_value) {
				pwalker = pwalker->m_pleft;
			}
			else {
				pwalker = pwalker->m_pright;
			}
		}
		if(pparent == nullptr) {
			m_proot = new Node(value, nullptr, nullptr, m_pend);
			m_pbegin = m_proot;
			m_pend->m_pparent = m_proot;
		}
		else if(value < pparent->m_value) {
			pparent->m_pleft = new Node(value, pparent);
			if(pparent == m_pbegin)
				m_pbegin = pparent->m_pleft;
		}
		else {
			pparent->m_pright = new Node(value, pparent, nullptr, pparent->m_pright);
			Node *platestNode = pparent->m_pright;
			if(platestNode->m_pright == m_pend)
				m_pend->m_pparent = platestNode;
		}
		m_size++;
	}
	void erase(iterator it) {
		assert(it.m_pbst == this);
		assert(it.m_pnode != m_pend);
		m_pend->m_pparent->m_pright = nullptr;
		if(it.m_pnode->m_pleft != nullptr && it.m_pnode->m_pright != nullptr) {
			Node *pwalker = it.m_pnode->m_pright;
			while(pwalker->m_pleft != nullptr) {
				pwalker = pwalker->m_pleft;
			}
			it.m_pnode->m_value = pwalker->m_value;
			it.m_pnode = pwalker;
		}
		if(it.m_pnode->m_pleft == nullptr && it.m_pnode->m_pright == nullptr) {
			Node *pparent = it.m_pnode->m_pparent;
			if(pparent == nullptr) {
				m_proot = m_pend;
				m_proot->m_pparent = nullptr;
			}
			else if(pparent->m_pleft == it.m_pnode)
				pparent->m_pleft = nullptr;
			else
				pparent->m_pright = nullptr;
			delete it.m_pnode;
		}
		else if(it.m_pnode->m_pleft != nullptr && it.m_pnode->m_pright == nullptr) {
			Node *pparent = it.m_pnode->m_pparent;
			if(pparent == nullptr) {
				m_proot = it.m_pnode->m_pleft;
				m_proot->m_pparent = nullptr;
			}
			else if(pparent->m_pleft == it.m_pnode) {
				pparent->m_pleft = it.m_pnode->m_pleft;
				it.m_pnode->m_pleft->m_pparent = pparent;
			}
			else {
				pparent->m_pright = it.m_pnode->m_pleft;
				it.m_pnode->m_pleft->m_pparent = pparent;
			}
			delete it.m_pnode;
		}
		else if(it.m_pnode->m_pleft == nullptr && it.m_pnode->m_pright != nullptr) {
			Node *pparent = it.m_pnode->m_pparent;
			if(pparent == nullptr) {
				m_proot = it.m_pnode->m_pright;
				m_proot->m_pparent = nullptr;
			}
			else if(pparent->m_pleft == it.m_pnode) {
				pparent->m_pleft = it.m_pnode->m_pright;
				it.m_pnode->m_pright->m_pparent = pparent;
			}
			else {
				pparent->m_pright = it.m_pnode->m_pright;
				it.m_pnode->m_pright->m_pparent = pparent;
			}
			delete it.m_pnode;
		}
		if(m_proot != m_pend) {
			Node *pwalker = m_proot;
			while(pwalker->m_pright != nullptr)
				pwalker = pwalker->m_pright;
			pwalker->m_pright = m_pend;
			m_pend->m_pparent = pwalker;

			pwalker = m_proot;
			while(pwalker->m_pleft != nullptr)
				pwalker = pwalker->m_pleft;
			m_pbegin = pwalker;
		}
		else {
			m_pbegin = m_pend;
		}
		m_size--;
	}
public:
	iterator find(int value) {
		assert(m_size > 0);
		Node *pwalker = m_proot;
		while(pwalker != nullptr && pwalker != m_pend) {
			if(pwalker->m_value == value) {
				return iterator(this, pwalker);
			}
			else if(value < pwalker->m_value) {
				pwalker = pwalker->m_pleft;
			}
			else {
				pwalker = pwalker->m_pright;
			}
		}
		return iterator(this, m_pend);
	}
private:
	size_t m_size;
private:
	Node *m_proot;
	Node *m_pbegin;
	Node *m_pend;
};