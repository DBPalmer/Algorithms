#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath> //added for pow()
#include "SortClass.h"

using namespace std;


SortClass::SortClass(int n, bool genRandom)
{
    swapCount = 0;
    if (genRandom) 
	{
            srand(time(0));
	    for (int i = 0; i < n; i++)
		array.push_back((rand() % 1000) * 1.0);
	}
    else
	{
	    for (int i = 0; i < n; i++)
		array.push_back(0.0);
	}
}

SortClass::SortClass(const SortClass& st)
{
   swapCount = st.swapCount;
   for (int i = 0 ; i < st.array.size(); i++)
	array.push_back(st.array[i]);

}

int SortClass::count()
{
   return array.size();
}

int SortClass::getSwapCount()
{
   return swapCount;
}

void SortClass::clear(bool genRandom)
{
    swapCount = 0;
    if (genRandom)
	{
            srand(time(0));
	    for (int i = 0; i < array.size(); i++)
		array[i] = rand() * 1.0;
	}
    else
	{
	    for (int i = 0; i < array.size(); i++)
		array[i] = 0.0;
	}
}

bool SortClass::lessthan(int i, int j)
{
   return (array[i] < array[j]);
}

void SortClass::swap(int i, int j)
{
    float temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    swapCount++;
}

ostream& operator<<(ostream& os, SortClass& s)
{
    for (int i = 0; i < s.array.size(); i++)
	{
	    if (!(i % 10))
		os << endl;
	    os << s.array[i] << " ";
	}
    return os;
}

istream& operator>>(istream& is, SortClass& s)
{
    for (int i = 0; i < s.array.size(); i++)
	{
	    is >> s.array[i];
	}
    return is;
}

void ShellSort(SortClass& s, int code) {
    int k = 1;
    int h;
    vector<int> hlist;
    if (code == 0) {
        hlist.push_back(1);
    }
    else if (code == 1){
        while (pow(k, 2) < s.count()) {
            hlist.push_back(pow(k++, 2));
        }
    }
    else if (code == 2) {
        while (pow(2, k) - 1 < s.count()) {
            hlist.push_back(pow(2, k++) - 1);
        }
    }
    else if (code == 3){
        while ((pow(3, k)-1)/ 2 < s.count()) {
            hlist.push_back((pow(3, k++)-1) / 2);
        }
    }
    else {
        cout << "ERROR: Incorrect code value entered. Program Exited.\n";
        return;
    }
    k = hlist.size() - 1;
    while (k >= 0) {
        h = hlist[k--];
        for (int j = 1; j < s.count(); j++) {
            int i = j;
            while ((i >= 0) && (s.lessthan(i, i - h))) {
                s.swap(i - h, i);
                i = i - h;
            }
        }
    }
}
