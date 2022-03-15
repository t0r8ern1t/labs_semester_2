#include <iostream>
#include "timer.hpp"
#include "functions.hpp"

using namespace std;
using namespace ssh;



int main()
{
	srand(time(0));
	List* head = new List;
	head->next = nullptr;
	int n = 100000; //элементы
	int m = 1000; //запросы
	int filling = 0;
	int position = 0;

	for (int i = 0; i < n; ++i) 
	{
		filling = rand();
		ADD(head, filling);
	}
	//PRINT(head);

	ssh::Timer timer;
	for (int i = 0; i < m; ++i) 
	{
		filling = rand();
		position = rand() % n;
		ADDPOS(head, filling, position);
		++n;
	}
	cout << timer.elapsed() << endl;
	//PRINT(head);
	cout << endl;

	CLEAR(head);
	delete head;

	int* array = new int[n + m];
	for (int i = 0; i < n; ++i) 
	{
		filling = rand();
		array[i] = filling;
	}
	//PrintArr(array, n);

	timer.reset();
	for (int i = 0; i < m; ++i) 
	{
		filling = rand();
		position = rand() % n;
		AddToArr(array, n, position, filling);
		n++;
	}
	cout << timer.elapsed() << endl;
	//PrintArr(array, n);

	return 0;
}
