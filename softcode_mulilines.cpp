

#include <fstream>
#include <iostream>
using namespace std;

enum STATE {
    S0 = 0, // Inside code or outside comment
    S1,     // Possible start of comment
    S2      // Inside multiline comment
};

// Define the transition table
STATE transitionTable[3][3] = {
    // '/', '*', others
    {S1, S0, S0}, // S0
    {S0, S2, S0}, // S1
    {S0, S2, S2}  // S2
};

// Function to get the column index in the transition table for a given character
int getCharType(char ch) {
    if (ch == '/') {
        return 0;
    } else if (ch == '*') {
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
    ifstream inFile("lab_2.cpp"); // Replace "input.cpp" with your input file name
    if (!inFile) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }

    STATE currentState = S0;
    char ch;

    char buffer[2][1024]; // Two buffers, assuming max comment size of 1024 chars
    int currentBuffer = 0;
    int bufferIndex = 0;

    while (inFile.get(ch)) {
        STATE oldState = currentState;
        currentState = nextState(currentState, ch);

        if (oldState == S2 && currentState != S2 && bufferIndex > 0) {
            // End of comment reached
            buffer[currentBuffer][bufferIndex] = '\0'; // Null-terminate
            cout << buffer[currentBuffer] << endl; // Print the comment
            bufferIndex = 0; // Reset index
            currentBuffer = (currentBuffer + 1) % 2; // Switch to the other buffer
        } else if (currentState == S2) {
            buffer[currentBuffer][bufferIndex++] = ch;
        }
    }

    // Print any remaining comment in the last buffer
    if (bufferIndex > 0) {
        buffer[currentBuffer][bufferIndex] = '\0';
        cout << buffer[currentBuffer] << endl;
    }

    inFile.close();

    return 0;
}







