#pragma once

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "stack.h"
#include <vector>

template<class T>
class ArrayStack : public Stack<T>
{
private:
	std::vector<T> stack;
public:
	ArrayStack() {}

	ArrayStack(const ArrayStack<T>& other)
	{
		stack = other.stack;
	}

	void push(T val)
	{
		stack.push_back(val);
	}

	void pop()
	{
		if (stack.size() != 0)
			stack.pop_back();
	}

	T peek() const
	{
		assert (stack.size() != 0);

		return stack.back();
	}

	void makeEmpty()
	{
		stack.clear();
	}

	bool isEmpty() const
	{
		return stack.size() == 0;
	}

	size_t size() const
	{
		return stack.size();
	}

	ArrayStack<T>& operator=(const ArrayStack<T>& rhs)
	{
		if (&rhs == this)
			return *this;

		stack.clear();
		stack = rhs.stack;

		return *this;
	}

};

#endif // ARRAY_STACK_H