#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <limits>
#include <Windows.h>
#undef max
#define INITIAL_SIZE 50

using namespace std;

typedef struct {
    char* text;
    size_t capacity;
} arrayForUserInput;

void CreateArrayForUserInput(arrayForUserInput* userInput) {
    char* array = new char[INITIAL_SIZE];
    if (array == nullptr) {
        cout << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    array[0] = '\0';
    userInput->capacity = INITIAL_SIZE;
    userInput->text = array;
}

void MakeUserArrayLonger(arrayForUserInput* userInput) {
    size_t newCapacity = userInput->capacity * 2;
    char* temp = new char[newCapacity];
    if (temp == nullptr) {
        cout << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    strncpy(temp, userInput->text, userInput->capacity);
    delete[] userInput->text;
    userInput->text = temp;
    userInput->capacity = newCapacity;
}

void TakeUserInput(arrayForUserInput* userInput) {
    cout << "Enter text: " << endl;
    size_t currentLength = strlen(userInput->text);
    while (fgets(userInput->text + currentLength, userInput->capacity - currentLength, stdin)) {
        currentLength += strlen(userInput->text + currentLength);
        if (userInput->text[currentLength - 1] == '\n') {
            break;
        }
        MakeUserArrayLonger(userInput);
    }
    userInput->text[currentLength - 1] = '\0';
}

bool AskUserToEnterKey(int* key) {
    cout << "Enter a key (0 to 25): " << endl;
    if (!(cin >> *key)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!" << endl;
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (*key < 0 || *key > 25) {
        cout << "Invalid range!" << endl;
        return false;
    }
    return true;
}

void help() {
    cout << "0 - exit\n"
        << "1 - help\n"
        << "2 - encrypt\n"
        << "3 - decrypt\n";
}

void ProcessCommand(int command, char* (*encrypt_ptr)(char*, int), char* (*decrypt_ptr)(char*, int)) {
    arrayForUserInput userInput;
    CreateArrayForUserInput(&userInput);
    int key;
    char* result = nullptr;

    switch (command) {
    case 0:
        exit(0);
        break;
    case 1:
        help();
        break;
    case 2:
        TakeUserInput(&userInput);
        if (!AskUserToEnterKey(&key)) {
            return;
        }
        result = encrypt_ptr(userInput.text, key);
        if (result == nullptr) {
            return;
        }
        cout << "Encrypted: " << result << endl;
        delete[] result;       
        break;
    case 3:
        TakeUserInput(&userInput);
        if (!AskUserToEnterKey(&key)) {
            return;
        }
         result = decrypt_ptr(userInput.text, key);
         if (result == nullptr) {
             return;
         }
         cout << "Decrypted: " << result << endl;
         delete[] result;
        break;
    default:
        cout << "The command is not implemented! Type 1 for help!\n";
    }

    if (userInput.text != nullptr) {
        delete[] userInput.text;
    }
}

int main() {
    typedef char* (*encrypt_ptr_t)(char*, int);
    typedef char* (*decrypt_ptr_t)(char*, int);

    HINSTANCE handle = LoadLibrary(TEXT("C:\\Margo\\CaesarCodeAndLibrary\\Library\\Caesar.dll"));
    cout << "Hello! Enter '1' to see the available list of commands :)\n";
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        cout << "Library not found." << endl;
        return -1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "Encrypt");
    if (encrypt_ptr == nullptr) {
        cout << "Encrypt function not found." << endl;
        FreeLibrary(handle);
        return 1;
    }

    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "Decrypt");
    if (decrypt_ptr == nullptr) {
        cout << "Decrypt function not found." << endl;
        FreeLibrary(handle);
        return 1;
    }

    int command;
    do {
        cout << "Enter command: ";
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (command == 0) {
            break;
        }

        ProcessCommand(command, encrypt_ptr, decrypt_ptr);
    } while (true);

    FreeLibrary(handle);
    return 0;
}
