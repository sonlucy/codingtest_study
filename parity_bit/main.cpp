
#include <iostream>

using namespace std;
//패리티 비트..

int bitcount(unsigned int n)
{
	register unsigned int tmp;

	tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
	return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}

void main()
{
	unsigned int u = 5;
	int b = bitcount(u);

	cout << b;
}