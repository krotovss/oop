#include "cyclic_list.h"

#include <iostream>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CyclicList<int> list;
	int n;
	int k;
	std::cin >> n >> k;

	for (int i = 1; i <= n; ++i)
		list.insert(i);

	while(list.size() != 1)
	{
		for (int i = 1; i < k; ++i)
			list.next();
		
		list.remove();
	}


	std::cout << list.get();

	// system("pause");
	return 0;
}