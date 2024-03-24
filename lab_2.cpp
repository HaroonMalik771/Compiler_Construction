
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

   /*
This is a multiline comment in C++.
It can span multiple lines and is used to provide
detailed explanations or notes within the code.
*/



using namespace std;
   /*
This is a multiline comment in C++.
It can span multiple lines and is used to provide
detailed explanations or notes within the code.
*/


const int BUFFER_SIZE = 4096;

struct Token {
    string identifier;
    int value;
};

void identifier(char* currentBuffer, ofstream& outFile) {
    int bufferIndex = 0;
    int lexemeIndex = 0;
    int tokenValue = 0;

    char ch = currentBuffer[bufferIndex];
    char lexeme[50];
    int state = 0;

    while (bufferIndex < BUFFER_SIZE) {
        switch (state) {
            case 0:
                if (ch == '_' || isalpha(ch)) {
                    state = 1;
                    lexeme[lexemeIndex] = ch;
                    lexemeIndex++;
                }
                break;

            case 1:
                if (ch == '_' || isalnum(ch)) {
                    state = 1;
                    lexeme[lexemeIndex] = ch;
                    lexemeIndex++;
                } else {
                    state = 2;
                }
                break;

            case 2:
                lexeme[lexemeIndex] = '\0';
                string lexemeString = lexeme;
                state = 0;
                bufferIndex--;
                tokenValue++;
                Token token;
                token.identifier = lexemeString;
                token.value = tokenValue;
                outFile << "Token: " << token.identifier << " (Value: " << token.value << ")\n";
                lexemeIndex = 0; 
        }
        bufferIndex++;
        ch = currentBuffer[bufferIndex];
    }
}



int main() {
    ifstream inFile("lab_2.cpp");
    ofstream outFile("output.txt");
    if (inFile.is_open() && outFile.is_open()) {
        char buffer1[BUFFER_SIZE];
        char buffer2[BUFFER_SIZE];
        char* currentBuffer = buffer1;
        char* nextBuffer = buffer2;
        inFile.read(currentBuffer, BUFFER_SIZE);
        while (!inFile.eof()) {
            inFile.read(nextBuffer, BUFFER_SIZE);
            identifier(currentBuffer, outFile);
            swap(currentBuffer, nextBuffer);
        }
        identifier(currentBuffer, outFile);
        inFile.close();
        outFile.close();
    } else {
        cout << "Unable to open file for reading or writing";
    }
 

    return 0;
}



