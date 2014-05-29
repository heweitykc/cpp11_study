#include "stdafx.h"
#include "generator.h"


void generator::doit()
{
	int iArray[5] = { 1, 2, 3, 4, 5 };
	list<int> iList;

	// Seed the random number generator
	srand(unsigned int(NULL));

	// Construct vector and fill with random integer values
	vector<int> collection(10);
	for (int i = 0; i < 10; i++)
		collection[i] = rand() % 10000;

	// Display, sort, and redisplay
	Display(collection, "Before sorting:collection");
	sort(collection.begin(), collection.end());
	Display(collection, "After sorting:collection");

	copy(iArray, iArray + 5, front_inserter(iList));
	Display(iList, "After sorting:iList");

	list<int>::iterator p = find(iList.begin(), iList.end(), 3);
	copy(iArray, iArray + 2, inserter(iList, p));
	Display(iList, "After find and copy:iList");

	int k = 0;
	advance(p, 0);
	k = distance(p, iList.end());
	cout << "k=" << k << endl;

	int sum = accumulate(iList.begin(), iList.end(), 1, multiplies<int>());
	cout << "sum=" << sum << endl;

	static const char* foo[] = { "1", "1", "1", "1", "10" };
	int bar[5];
	transform(foo, foo + 5, bar, ptr_fun(atoi));
	sum = accumulate(bar, bar + 5, 0);
	cout << "sum=" << sum << endl;
}


// Display label s and contents of integer vector v
void Display(vector<int>& v, const char* s)
{
	cout << endl << s << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
	cout << endl;
}

void Display(list<int>& v, const char* s)
{
	cout << endl << s << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
	cout << endl;
}