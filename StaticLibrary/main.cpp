
#include <iostream>
#include "mylibrary.h"
using namespace std;
int main()
{
	int key = 22;
	char phrase[] = "Today is a good day, but not tomorrow!";
	cout << phrase << endl;
	cout << "Encryption by key: " << key << " " << Encrypt(phrase, key) << endl;
	char* encryptedText = Encrypt(phrase, key);
	cout << "Decryption by key: " << key << " " << Decrypt(encryptedText, key) << endl;


}