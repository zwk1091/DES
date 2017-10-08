#ifndef	_DES
#define _DES

#include<iostream>
#include<bitset>
#include<algorithm>
#include<string>
#include"tools.h"
using namespace std;
class Des {
public:
	bool setKey(string x);
	void generateSubKey();
	bitset<64> encrypt(bitset<64> plaintext);
	bitset<64> decrypt(bitset<64> ciphertext);
	bitset<32> feistel(bitset<32>, bitset<48>);
private:
	bitset<64> key;
	bitset<48> subKey[16];
};

#endif