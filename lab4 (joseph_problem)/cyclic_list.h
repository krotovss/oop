#pragma once

#ifndef CYCLIC_LIST_H
#define CYCLIC_LIST_H

#include <assert.h>

template<class T>
class CyclicList
{
public:
	CyclicList() : _current(0), _prev(0), _size(0) {}

	void insert(T value)
	{
		if (_current == 0)
		{
			_current = new Node(value);
			_current->next = _current;
			_prev = _current;
			_size = 1;
		} else
		{
			Node* node = new Node(value, _current);
			_prev->next = node;
			_prev = node;
			_size++;
		}
	}

	void remove()
	{
		if (_size <= 1)
		{
			clear();
		} else
		{
			_prev->next = _current->next;
			delete _current;
			_current = _prev->next;
			_size--;
		}
	}

	T next()
	{
		assert (_current != 0);

		_prev = _current;
		_current = _current->next;

		return _current->value;
	}

	T get() const
	{
		assert (_current != 0);

		return _current->value;
	}

	size_t size() const
	{
		return _size;
	}

	void clear()
	{
		if (_current != 0)
			_prev->next = 0;

		_size = 0;
		delete_list(_current);
		_current = 0;
		_prev = 0;
	}

	~CyclicList()
	{
		clear();
	}

private:
	struct Node
	{
		T value;
		Node* next;
	
		Node() {}
		Node(T value) : value(value), next(0) {}
		Node(T value, Node* node) : value(value), next(node) {}
	};

	Node* _current;
	Node* _prev;
	size_t _size;

	void delete_list(Node*& current)
	{
		if (current == 0)
			return;

		delete_list(current->next);
		delete current;
		current = 0;
	}

};

#endif // CYCLIC_LIST_H