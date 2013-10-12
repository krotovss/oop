#pragma once

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.h"
#include <assert.h>

template<class T>
class LinkedStack : public Stack<T>
{
private:
	struct Node
	{
		T value;
		Node* next;
	
		Node() {}
		Node(T value, Node* node) : value(value), next(node) {}
	};

	Node* head;
	size_t _size;

	void delete_stack(Node*& current)
	{
		if (current == 0)
			return;

		delete_stack(current->next);
		delete current;
		current = 0;
	}

	Node* deep_copy(Node* node)
	{
		if (node == 0)
			return 0;

		return new Node(node->value, deep_copy(node->next));
	}

public:
	LinkedStack() : head(0), _size(0) {}

	LinkedStack(const LinkedStack<T>& other)
	{
		_size = other.size();
		head = deep_copy(other.head);
	}

	void push(T value)
	{
		head = new Node(value, head);
		_size++;
	}

	size_t size() const
	{
		return _size;
	}

	void pop()
	{
		if (head)
		{
			Node* current = head;
			head = head->next;
			delete current;
			_size--;
		}
	}

	T peek() const
	{
		assert (head != 0);
		
		return head->value;
	}

	bool isEmpty() const
	{
		return head == 0;
	}

	void makeEmpty()
	{
		delete_stack(head);
		_size = 0;
	}

	~LinkedStack()
	{
		delete_stack(head);
	}

	LinkedStack<T>& operator=(const LinkedStack<T>& rhs)
	{
		if (&rhs == this)
			return *this;

		delete_stack(head);

		_size = rhs.size();
		head = deep_copy(rhs.head);

		return *this;
	}
};

#endif // LINKED_STACK_H