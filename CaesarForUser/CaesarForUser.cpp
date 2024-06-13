#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <limits>

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
    copy_n(userInput->text, userInput->capacity, temp);
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

char* Encrypt(char* rawText, int key) {
    int length = strlen(rawText);
    char* encodedText = new char[length + 1];

    for (int i = 0; i < length; i++) {
        if (!isalpha(rawText[i])) {
            encodedText[i] = rawText[i];
        }
        else if (isupper(rawText[i])) {
            encodedText[i] = ((rawText[i] - 65 + key) % 26 + 26) % 26 + 65;
        }
        else {
            encodedText[i] = ((rawText[i] - 97 + key) % 26 + 26) % 26 + 97;
        }
    }
    encodedText[length] = '\0';
    return encodedText;
}

char* Decrypt(char* encryptedText, int key) {
    return Encrypt(encryptedText, -key);
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

void ProcessCommand(int command) {
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
        if (AskUserToEnterKey(&key)) {
            result = Encrypt(userInput.text, key);
            cout << "Encrypted: " << result << endl;
        }
        break;
    case 3:
        TakeUserInput(&userInput);
        if (AskUserToEnterKey(&key)) {
            result = Decrypt(userInput.text, key);
            cout << "Decrypted: " << result << endl;
        }
        break;
    default:
        cout << "The command is not implemented! Type 1 for help!\n";
    }

    if (userInput.text != nullptr) {
        delete[] userInput.text;
    }
}

int main() {
    cout << "Hello! Welcome to the Text Editor! Enter '9' to see the available list of commands :)\n";
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

        ProcessCommand(command);
    } while (true);
    return 0;
}
