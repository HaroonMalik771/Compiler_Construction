#include <fstream>
#include <iostream>
#include <string>

enum State {
    OutsideComment,
    InsideComment,
    AsteriskFound
};

int main() {
    std::ifstream inFile("lab_3.cpp");
    if (!inFile.is_open()) {
        std::cout << "Unable to open file";
        return 1;
    }

    std::string line;
    State state = OutsideComment;
    while (std::getline(inFile, line)) {
        for (char ch : line) {
            switch (state) {
                case OutsideComment:
                    if (ch == '/') {
                        state = InsideComment;
                    }
                    break;
                case InsideComment:
                    if (ch == '*') {
                        state = AsteriskFound;
                        std::cout << "/*";
                    } else {
                        state = OutsideComment;
                    }
                    break;
                case AsteriskFound:
                    std::cout << ch;
                    if (ch == '/') {
                        state = OutsideComment;
                        std::cout << '\n';
                    }
                    break;
            }
        }
    }

    inFile.close();
    return 0;
}



