#pragma once

#ifndef STACK_H
#define STACK_H

template<class T>
class Stack
{
public:
	virtual void push(T) = 0;

	virtual void pop() = 0;

	virtual T peek() const = 0;

	virtual void makeEmpty() = 0;

	virtual bool isEmpty() const = 0;

	virtual size_t size() const = 0;

	virtual ~Stack() {}
};

#endif // STACK_H