#include<iostream>
#include<bitset>
#include<algorithm>
#include<fstream>
#include<ostream>
#include<string>
#include"des.h"
#include"tools.h"
#include<io.h>
#include<stdio.h>
using namespace std;
using std::bitset;

int main() {
	ifstream fin;
	ofstream fout;
	Des d;
	Tools T;
	string select;
	string keyHex;
	//="00123456789abcde";
	//d.setKey(keyHex);
	while (1) {
		system("cls");
		cout << "*************DES加密算法***************" << endl;
		cout << "1 加密(请在plaintext.txt文件中输入明文) " << endl;
		cout << "2 解密(请在ciphertext.txt文件中输入密文)" << endl;
		cout << "3 更改密钥" << endl;
		cin >> select;
		if (select == "1") {
			int size = 0;
			//加密
			char blank = '0';
				struct _stat info;
				_stat("plaintext.txt", &info);
				size = info.st_size;
				//cout << size << endl;
				while (size % 8 != 0) {
					fout.open("plaintext.txt", ios::app);
					fout << blank;
				
					fout.close();
					struct _stat info;
					_stat("plaintext.txt", &info);
					size = info.st_size;
					//cout << size << endl;
			}

			fin.open("plaintext.txt", ios::binary);
			fout.open("ciphertext.txt", ios::binary);
			bitset<64> plain;
			
			while (fin.read((char*)&plain,sizeof(plain)))
			{
				
				//cout << "明文：" << plain << endl;
				bitset<64> cipher = d.encrypt(plain);
				//cout << "密文：" << cipher << endl;

				fout.write((char*)&cipher, sizeof(cipher));
				plain.reset();  // 置0  
				
			}
			fin.close();
			fout.close();
			cout << "加密成功，请在ciphertext.txt中查看您的明文" << endl;

		}
		else if (select == "2") {
			//解密
			fin.open("ciphertext.txt", ios::binary);
			fout.open("plaintext.txt", ios::binary);
			bitset<64> ci;
			while (fin.read((char*)&ci, sizeof(ci)))

			{
				//cout << "密文：" << ci << endl;
				
				bitset<64> pl = d.decrypt(ci);
				//cout <<"明文："<< pl << endl;
				fout.write((char*)&pl, sizeof(pl));
				ci.reset();  // 置0  
			}
			fin.close();
			fout.close();
			cout << "解密成功，请在plaintext.txt中查看您的明文" << endl;
		}
		else if (select == "3") {
			while (1) {
				cout << "请输入您的密钥(16位16进制数)" << endl;
				cin >> keyHex;
				if (!d.setKey(keyHex)) {
					cout << "密钥不合法，请重新输入" << endl;
				}
				else {
					cout << "更改密钥成功" << endl;
					break;
				}
			}
		}
		system("pause");
	}
	return 0;
}