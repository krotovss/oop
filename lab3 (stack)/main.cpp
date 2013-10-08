#include "linked_stack.h"
#include "array_stack.h"
#include <iostream>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ArrayStack<int> s;
	//LinkedStack<int> s;

	const int N = 2;
	for (int i = 0; i < N; ++i)
		s.push(i + 1);

	for (int i = 0; i < N; ++i)
	{
		std::cout << s.peek() << std::endl;
		//s.pop();
	}

	ArrayStack<int> other = s;
	//LinkedStack<int> other = s;
	//other = s;

	s.makeEmpty();

	std::cout << (other.isEmpty() ? 0 : other.peek()) << std::endl;

	std::cout << (s.isEmpty() ? "YES" : "NO") << std::endl;

	return 0;
}