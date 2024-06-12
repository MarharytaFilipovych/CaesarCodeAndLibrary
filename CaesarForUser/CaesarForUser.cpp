#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#define INITIAL_SIZE 50

using namespace std;

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

void help() {
    cout << "0 - exit\n"
        << "1 - help\n"
        << "2 - encrypt\n"
        << "3 - decrypt\n";
}

void ProcessCommand(int command) {
    switch (command) {
    case 0:
        exit(0);
        break;
    case 1:
        help();
        break;
    case 2:
        // You can add the encrypt logic here
        break;
    case 3:
        // You can add the decrypt logic here
        break;
    default:
        cout << "The command is not implemented! Type 1 for help!\n";
    }
}
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
    size_t newCapacity = INITIAL_SIZE * 2;
    char* temp = new char[newCapacity];
    if (temp == nullptr) {
        cout << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    copy_n(userInput->text, INITIAL_SIZE, temp);
    delete[] userInput->text;
    userInput->text = temp;
    userInput->capacity = newCapacity;
}
void AdjustSizeOfUserArray(arrayForUserInput* userInput)
{
    size_t newCapacity = strlen(userInput->text) + 1;
    char* temp = new char[newCapacity];
    if (temp == nullptr)
    {
        cout << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    copy_n(userInput->text, newCapacity, temp);
    delete[] userInput->text;
    userInput->text = temp;
    userInput->capacity = newCapacity;
}
void TakeUserInput(arrayForUserInput* userInput) {
    size_t currentLength = strlen(userInput->text);
    while (fgets(userInput->text + currentLength, INITIAL_SIZE - currentLength, stdin)) {
        currentLength += strlen(userInput->text + currentLength);
        if (userInput->text[currentLength - 1] == '\n') {
            break;
        }
        MakeUserArrayLonger(userInput);
    }
    userInput->text[currentLength - 1] = '\0';
}
int main() {
    cout << "Hello! Welcome to the Text Editor! Enter '9' to see the available list of commands :)\n";
    arrayForUserInput userInput;
    CreateArrayForUserInput(&userInput);
    int command;
    do {
        std::cout << "Enter command: ";
        if (!(std::cin >> command)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (command == 0) {
            break;
        }
        
        ProcessCommand(command);
    } while (true);
    return 0;
}

