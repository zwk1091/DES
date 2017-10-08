#include"des.h"
#include"constant.h"
#include<iostream>

using namespace std;

bool Des::setKey(string x) {
	Tools T;
	string bin = T.keyHexToBin(x);
	if (bin == "0") {
		return false;
	}
	reverse(bin.begin(), bin.end());
	bitset<64> y(bin);
	key = y;
	generateSubKey();
	return true;
}

void Des::generateSubKey() {
	bitset<28> c0;
	bitset<28> d0;
	//pc_1ÖÃ»»
	for (int i = 0; i < 28; i++) {
		c0[i] = key[PC_1[i]];
		d0[i] = key[PC_1[28 + i]];
	}

	for (int i = 1; i <= 16; i++) {
		//c,d×óÒÆÒ»Î»
		if (i == 1 || i == 2 || i == 9 || i == 16) {
			int t0 = c0[0];
			for (int j = 0; j < 27; j++) {
				c0[j] = c0[j + 1];
			}
			c0[27] = t0;
			t0 = d0[0];
			for (int j = 0; j < 27; j++) {
				d0[j] = d0[j + 1];
			}
			d0[27] = t0;
		}
		//c,d×óÒÆÁ½Î»
		else {
			int t0 = c0[0];
			int t1 = c0[1];
			for (int j = 0; j < 26; j++) {
				c0[j] = c0[j + 2];
			}
			c0[26] = t0;
			c0[27] = t1;

			 t0 = d0[0];
			 t1 = d0[1];
			for (int j = 0; j < 26; j++) {
				d0[j] = d0[j + 2];
			}
			d0[26] = t0;
			d0[27] = t1;
		}
		//pc-2 Ñ¹ËõÖÃ»»
		for (int k = 0; k < 48; k++) {
			if (PC_2[k] < 29) {
				subKey[i - 1][k] = c0[PC_2[k]-1];
			}
			else {
				subKey[i - 1][k] = d0[PC_2[k]-29];
			}
		}
	}
}

//¼ÓÃÜËã·¨
bitset<64> Des::encrypt(bitset<64> plaintext) {
	bitset<32> L, R;
	//³õÊ¼ÖÃ»»IP
	for (int i = 0; i < 32; i++) {
		L[i] = plaintext[IP[i]-1];
		R[i] = plaintext[IP[i+32]-1];
	}
	//µü´úÖÃ»»
	for (int i = 0; i < 16; i++) {
		bitset<32> tL = L;
		bitset<32> tR = R;
		L = tR;
		R = tL^feistel(tR, subKey[i]);
	}
	//ÄæÖÃ»»
	bitset<64> res;
	for (int i = 0; i < 64; i++) {
		if (IP_1[i] < 33) {
			res[i] = R[IP_1[i]-1];
		}
		else {
			res[i] = L[IP_1[i] - 33];
		}
	}
	return res;
}
//½âÃÜËã·¨
bitset<64> Des::decrypt(bitset<64> ciphertext) {
	bitset<32> L, R;
	//³õÊ¼ÖÃ»»IP
	for (int i = 0; i < 32; i++) {
		L[i] = ciphertext[IP[i]-1];
		R[i] = ciphertext[IP[i + 32]-1];
	}
	//µü´úÖÃ»»
	for (int i = 0; i < 16; i++) {
		bitset<32> tL = L;
		bitset<32> tR = R;
		L = tR;
		R = tL^feistel(tR, subKey[15-i]);
	}
	//ÄæÖÃ»»
	bitset<64> res;
	for (int i = 0; i < 64; i++) {
		if (IP_1[i] < 33) {
			res[i] = R[IP_1[i]-1];
		}
		else {
			res[i] = L[IP_1[i] - 33];
		}
	}
	return res;
}

bitset<32> Des::feistel(bitset<32> R, bitset<48> K) {
	//E À©Õ¹ ²¢ÇÒºÍ×ÓÃÜÔ¿×öÒì»ò
	bitset<48> eR;
	bitset<32> res;
	for (int j = 0; j < 48; j++) {
		eR[j] = R[E[j]-1];
		eR = eR^K;
	}
	int restemp = 0;
	//s-box ×ö6-4×ª»»
	for (int i = 0; i < 48; i=i+6) {
		int row = eR[i] * 2 + eR[i+5];
		int col = eR[i + 1] * 8 + eR[i + 2] * 4 + eR[i + 3] * 2 + eR[i + 4];
		int num = S_BOX[i / 6][row-1][col-1];
		bitset<4> temp(num);
		for (int j = 0; j< 4; j++) {
			res[j+restemp] = temp[j];
			
		}
		restemp += 4;
	}
	//½øĞĞpÖÃ»»
	for (int i = 0; i < 32; i++) {
		bitset<32> t = res;
		res[i] = t[P[i]-1];
	}
	return res;
}
