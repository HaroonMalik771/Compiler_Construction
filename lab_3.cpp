#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

enum col {
    Letter = 0,
    Digit,
    Underscore,
    Punctuation,
    Operator,
    Quote,
    Other
};



int TT[4][7] = {
    {1, -1, -1, 2, 2, 3, -1},  // State 0: Start state
    {1, 1, 1, -1, -1, -1, -1},  // State 1: In identifier
    {-1, -1, -1, 2, 2, -1, -1},  // State 2: In punctuation or operator
    {3, 3, 3, 3, 3, 0, 3}  // State 3: In string literal
};

char ch;
char lex[20];
int li = 0, bi = 0, state = 0;

char buff[4096];

int main() {
    ifstream inFile("lab_2.cpp");
    if (!inFile.is_open()) {
        cout << "Unable to open file";
        return 1;
    }

    inFile.read(buff, 4096);
    buff[inFile.gcount()] = '\0';
    inFile.close();

while ((ch = buff[bi]) != '\0') {
    int col;
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) { // A-Z or a-z
        col = Letter;
    } else if (ch >= '0' && ch <= '9') { // 0-9
        col = Digit;
    } else if (ch == '_') { // Underscore
        col = Underscore;
    } else if (ch == '.' || ch == ',' || ch == ';' || ch == ':') { // Punctuation
        col = Punctuation;
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=') { // Operators
        col = Operator;
    } else if (ch == '\"') { // Quote
        col = Quote;
    } else { // Other characters
        col = Other;
    }

    int nextState = TT[state][col];
    if (nextState != -1) {
        lex[li] = ch;
        li++;
        state = nextState;
    } else {
        lex[li] = '\0';
        if (state == 1) {
            cout << "Token: " << state << ", Identifier: " << lex << ", Token Value: " << col << '\n';
        } else if (state == 2) {
            cout << "Token: " << state << ", Punctuation/Operator: " << lex << ", Token Value: " << col << '\n';
        } else if (state == 3) {
            cout << "Token: " << state << ", String Literal: " << lex << ", Token Value: " << col << '\n';
        }
        li = 0;
        state = 0; // Reset state after processing a token
    }
    bi++;

    /*
This is a multiline comment in C++.
It can span multiple lines and is used to provide
detailed explanations or notes within the code.
*/
}
    
        return 0;
}


