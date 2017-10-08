#include<iostream>
#include<bitset>
#include<algorithm>
#include<string>
#include"tools.h"
using namespace std;

bitset<64> Tools::stringToBitset(string x) {
	bitset<64> res;
	const char* t = x.c_str();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			res[i * 8 + j] = ((t[i] >> j) & 1);
		}
	}
	return res;
}

bitset<64> Tools::charToBitset(char* x) {
	bitset<64> res;
	const char* t = x;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			res[i * 8 + j] = ((t[i] >> j) & 1);
		}
	}
	return res;
}

string Tools::keyHexToBin(string x) {
	string res = "";
	if (x.length() != 16) {
		cout << "您输入的密钥长度" << x.length() << endl;
		return "0";
	}
	//cout << "x: " << x << endl;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == '0') {
			res += "0000";
		}
		else if (x[i] == '1') {
			res += "0001";
		}
		else if (x[i] == '2') {
			res += "0010";
		}
		else if (x[i] == '3') {
			res += "0011";
		}
		else if (x[i] == '4') {
			res += "0100";
		}
		else if (x[i] == '5') {
			res += "0101";
		}
		else if (x[i] == '6') {
			res += "0110";
		}
		else if (x[i] == '7') {
			res += "0111";
		}
		else if (x[i] == '8') {
			res += "1000";
		}
		else if (x[i] == '9') {
			res += "1001";
		}
		else if (x[i] == 'a' || x[i] == 'A') {
			res += "1010";
		}
		else if (x[i] == 'b' || x[i] == 'B') {
			res += "1011";
		}
		else if (x[i] == 'c' || x[i] == 'C') {
			res += "1100";
		}
		else if (x[i] == 'd' || x[i] == 'D') {
			res += "1101";
		}
		else if (x[i] == 'e' || x[i] == 'E') {
			res += "1110";
		}
		else if (x[i] == 'f' || x[i] == 'F') {
			res += "1111";
		}
		else {
			cout << "含有非法字符: " << x[i]<<endl;
			return "0";
		}
	}
	return res;
}