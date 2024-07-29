#include <iostream>
#include "SortClass.h"


void insertionSort(SortClass &s)
{
    for (int j = 1; j < s.count(); j++)
	{
	   int i = j;
	   while ((i > 0) && (s.lessthan(i, i-1)))
		{
		   s.swap(i-1, i);
		   i--;
		}
	} 
}

int main()
{

    SortClass  st(5000);
    for (int i = 0; i < 100; i++)
	{
    st.clear();
    SortClass st2(st);
    cout << "======\n";
    cout << st << endl; 
    insertionSort(st);
    cout << "------\n";
    cout << st << endl; 
    cout << "Swap count : " << st.getSwapCount() << endl;
    insertionSort(st2);
    cout << "------\n";
    cout << st2 << endl; 
    cout << "Swap count : " << st2.getSwapCount() << endl;

	}
   
    return 0;
}
