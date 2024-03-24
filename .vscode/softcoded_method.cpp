// Sir's Method

// #include<iostream>
// using namespace std;

// bool isLetter(char c) {
//     if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
//      return true;
//     else
//         return false; 
// }

// bool isDigit(char c) {
//     if (c >= '0' && c <= '9')
//         return true;
//     else
//         return false;
// }

// enum COL{
//         L=0,
//         U,
//         D,
//         NLDU,
//         A,
//         R,
//         T

// };

// COL getColType(char ch) {
//     if (isLetter(ch)) {
//         return L;
//     } else if (isDigit(ch)) {
//         return D;
//     } else if (ch=='_') {
//         return U;
//     }
//     else{
//         return NLDU;
//     }
// }


// int main () {

//     enum TOKTYPE{
//         N=0,
//         ID,
//         KEY,
//         PUN,
//         OP,
//         LIT

//     };




//     char buff[4096] = "price=price+com*sales;\0";
//     char lex[100];

//     int bi = 0;
//     int li = 0;
//     int state = 0;
//     char ch;
//     cout<<buff<<endl;

//     int TT[3][7]={
//         {1,1,-1,-1,false,false,N},
//         {1,1,1,2,false,false,N},
//         {0,0,0,0,true,true,ID}

//     };
// while((ch=buff[bi])!='\0'){

//     if(!TT[state][A]){
//         state=TT[state][getColType(ch)];
//         lex[li++]=ch;
//     }
//     else{
//         lex[li]='\0';
//         li=0;
//         if(TT[state][R]){ // only check the state is retracting
//             bi--;
//         }
//         state = 0;
//         cout << "Token: " << lex << endl;
//     }
//     bi++;
// }

//     cout<<endl;

//     return 0;
// }



#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;

enum STATE {
    S0 = 0, // Outside identifier
    S1      // Inside identifier
};

// Define the transition table
STATE transitionTable[2][3] = {
    // Letter or underscore, digit, others
    {S1, S0, S0}, // S0
    {S1, S1, S0}  // S1
};

// Function to get the column index in the transition table for a given character
int getCharType(char ch) {
    if (isalpha(ch) || ch == '_') {
        return 0;
    } else if (isdigit(ch)) {
        return 1;
    } else {
        return 2;
    }
}

// Function to get the next state from the transition table
STATE nextState(STATE currentState, char ch) {
    int charType = getCharType(ch);
    return transitionTable[currentState][charType];
}

int main() {
    ifstream inFile("softcoded_method.cpp"); 
    if (!inFile) {
        cout << "Error: Unable to open input file." << endl;
        return 1;

    }

    STATE currentState = S0;
    char ch;

    char buffer[2][1024]; 
    int currentBuffer = 0;
    int bufferIndex = 0;

    while (inFile.get(ch)) {
        STATE oldState = currentState;
        currentState = nextState(currentState, ch);

        if (oldState == S1 && currentState != S1 && bufferIndex > 0) {
            // End of identifier reached
            buffer[currentBuffer][bufferIndex] = '\0'; // Null-terminate
            cout << buffer[currentBuffer] << endl; // Print the identifier
            bufferIndex = 0; // Reset index
            currentBuffer = (currentBuffer + 1) % 2; // Switch to the other buffer
        } else if (currentState == S1) {
            buffer[currentBuffer][bufferIndex++] = ch;
        }
    }

    // Print any remaining identifier in the last buffer
    if (bufferIndex > 0) {
        buffer[currentBuffer][bufferIndex] = '\0';
        cout << buffer[currentBuffer] << endl;
    }

    inFile.close();

    return 0;
}