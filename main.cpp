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
		cout << "*************DES�����㷨***************" << endl;
		cout << "1 ����(����plaintext.txt�ļ�����������) " << endl;
		cout << "2 ����(����ciphertext.txt�ļ�����������)" << endl;
		cout << "3 ������Կ" << endl;
		cin >> select;
		if (select == "1") {
			int size = 0;
			//����
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
				
				//cout << "���ģ�" << plain << endl;
				bitset<64> cipher = d.encrypt(plain);
				//cout << "���ģ�" << cipher << endl;

				fout.write((char*)&cipher, sizeof(cipher));
				plain.reset();  // ��0  
				
			}
			fin.close();
			fout.close();
			cout << "���ܳɹ�������ciphertext.txt�в鿴��������" << endl;

		}
		else if (select == "2") {
			//����
			fin.open("ciphertext.txt", ios::binary);
			fout.open("plaintext.txt", ios::binary);
			bitset<64> ci;
			while (fin.read((char*)&ci, sizeof(ci)))

			{
				//cout << "���ģ�" << ci << endl;
				
				bitset<64> pl = d.decrypt(ci);
				//cout <<"���ģ�"<< pl << endl;
				fout.write((char*)&pl, sizeof(pl));
				ci.reset();  // ��0  
			}
			fin.close();
			fout.close();
			cout << "���ܳɹ�������plaintext.txt�в鿴��������" << endl;
		}
		else if (select == "3") {
			while (1) {
				cout << "������������Կ(16λ16������)" << endl;
				cin >> keyHex;
				if (!d.setKey(keyHex)) {
					cout << "��Կ���Ϸ�������������" << endl;
				}
				else {
					cout << "������Կ�ɹ�" << endl;
					break;
				}
			}
		}
		system("pause");
	}
	return 0;
}