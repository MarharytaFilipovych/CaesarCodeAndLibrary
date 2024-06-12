char* Encrypt(char* rawText, int key)
{
    int length = strlen(rawText);
    char* encodedText = new char[length + 1];

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(rawText[i]))
        {
            encodedText[i] = rawText[i];
        }
        else if (isupper(rawText[i]))
        {
            encodedText[i] = ((rawText[i] - 65 + key) % 26 + 26) % 26 + 65;
        }
        else if (!isupper(rawText[i]))
        {
            encodedText[i] = ((rawText[i] - 97 + key) % 26 + 26) % 26 + 97;
        }

    }
    encodedText[length] = '\0';
    return encodedText;
}

char* Decrypt(char* encryptedText, int key)
{
    char* text = Encrypt(encryptedText, -key);
    delete[] encryptedText;
    return text;
}


#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    char phrase[] = "Ab";
    char* encryptedText = Encrypt(phrase, 1);
    std::cout << encryptedText << std::endl;
    char* text = Decrypt(encryptedText, 1);
    std::cout << text << std::endl;

}


