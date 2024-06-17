using namespace std;
#include <iostream>
#include <windows.h>
int main() {
	typedef char* (*encrypt_ptr_t)(char*, int);
	typedef char* (*decrypt_ptr_t)(char*, int);

	HINSTANCE handle = LoadLibrary(TEXT("C:\\Margo\\CaesarCodeAndLibrary\\Library\\Caesar.dll"));
	
	if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
	{
		cout << "Lib not found" << endl;
		return -1;
	}
	encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "Encrypt");
	if (encrypt_ptr == nullptr)
	{
		cout << "Function not found" << endl;
		return 1;
	}

	decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "Decrypt");
	if (decrypt_ptr == nullptr)
	{
		cout << "Function not found" << endl;
		return 1;
	}
	int key = 22;
	char phrase[] = "Today is a good day, but not tomorrow!";
	cout << phrase << endl;
	cout << "Encryption by key: " << key << " " << encrypt_ptr(phrase, key) << endl;
	char* encryptedText = encrypt_ptr(phrase, key);
	cout << "Decryption by key: " << key << " " << decrypt_ptr(encryptedText, key) << endl;

	FreeLibrary(handle);
}

