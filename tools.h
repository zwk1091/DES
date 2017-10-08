#ifndef	_TOOLS
#define _TOOLS
#include<iostream>
#include<string>
using namespace std;
class Tools {
public:
	bitset<64> stringToBitset(string x);
	bitset<64> charToBitset(char *x);
	//string bitsetToString(bitset<64>);
	string keyHexToBin(string x);

};

#endif