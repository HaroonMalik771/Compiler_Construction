// #include <fstream>
// #include <iostream>
// #include <string>

// enum State {
//     OutsideComment,
//     InsideComment,
//     AsteriskFound
// };

// int main() {
//     std::ifstream inFile("lab_3.cpp");
//     if (!inFile.is_open()) {
//         std::cout << "Unable to open file";
//         return 1;
//     }

//     std::string line;
//     State state = OutsideComment;
//     while (std::getline(inFile, line)) {
//         for (char ch : line) {
//             switch (state) {
//                 case OutsideComment:
//                     if (ch == '/') {
//                         state = InsideComment;
//                     }
//                     break;
//                 case InsideComment:
//                     if (ch == '*') {
//                         state = AsteriskFound;
//                         std::cout << "/*";
//                     } else {
//                         state = OutsideComment;
//                     }
//                     break;
//                 case AsteriskFound:
//                     std::cout << ch;
//                     if (ch == '/') {
//                         state = OutsideComment;
//                         std::cout << '\n';
//                     }
//                     break;
//             }
//         }
//     }

//     inFile.close();
//     return 0;
// }


#include<bits/stdc++.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

int isKeyword(char buffer[]){
    char keywords[32][10] =
    {"auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto",
    "if","int","long","register","return","short","signed",
    "sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while"};
    int i, flag = 0;

    for(i = 0; i < 32; ++i){
        if(strcmp(keywords[i], buffer) == 0){
            flag = 1;
            break;
        }
    }

    return flag;
}

int main(){
    char ch, buffer[15], b[30], logical_op[] = "><", math_op[]="+-*/=", numer[]=".0123456789", other[]=",;\(){}[]'':";
    ifstream fin("lab_3.cpp");
    int mark[256] = {0}; // Assuming ASCII characters
    int i, j=0, kc=0, ic=0, lc=0, mc=0, nc=0, oc=0, aaa=0;
    char keywords[32][10], identifiers[100][15], math_ops[5], logical_ops[2], numericals[100][30], others[100];
    int kw_idx = 0, id_idx = 0, mo_idx = 0, lo_idx = 0, nu_idx = 0, ot_idx = 0;
    bool in_comment = false;
    bool is_multiline_comment = false;

    if(!fin.is_open()){
        cout<<"error while opening the file\n";
        exit(0);
    }

    while(!fin.eof()){
        ch = fin.get();

        // Skip comments
        if(!in_comment && ch == '/'){
            if(fin.peek() == '/'){
                while(ch != '\n'){
                    ch = fin.get();
                }
            }
            else if(fin.peek() == '*'){
                fin.ignore(); // Ignore the '*'
                in_comment = true;
                is_multiline_comment = true;
            }
        }
        else if(in_comment && is_multiline_comment && ch == '*'){
            if(fin.peek() == '/'){
                fin.ignore(); // Ignore the '/'
                in_comment = false;
                is_multiline_comment = false;
            }
        }
        else if(in_comment && !is_multiline_comment){
            // Continue ignoring characters until end of line for single-line comments
            if(ch == '\n'){
                in_comment = false;
            }
        }
        else if(!in_comment){
            // Process other characters
            for(i = 0; i < 12; ++i){
                if(ch == other[i]){
                    if(mark[ch] != 1){
                        others[ot_idx++] = ch;
                        mark[ch] = 1;
                        ++oc;
                    }
                }
            }

            // Process math operators
            for(i = 0; i < 5; ++i){
                if(ch == math_op[i]){
                    if(mark[ch] != 1){
                        math_ops[mo_idx++] = ch;
                        mark[ch] = 1;
                        ++mc;
                    }
                }
            }

            // Process logical operators
            for(i = 0; i < 2; ++i){
                if(ch == logical_op[i]){
                    if(mark[ch] != 1){
                        logical_ops[lo_idx++] = ch;
                        mark[ch] = 1;
                        ++lc;
                    }
                }
            }

            // Process numerical values and identifiers
            if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.' || ch == ' ' || ch == '\n' || ch == ';'){
                if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.'){
                    b[aaa++] = ch;
                }
                if((ch == ' ' || ch == '\n' || ch == ';') && (aaa != 0)){
                    b[aaa] = '\0';
                    aaa = 0;
                    strcpy(numericals[nu_idx++], b);
                    ++nc;
                }
            }

            // Process keywords and identifiers
            if(isalnum(ch)){
                buffer[j++] = ch;
            }
            else if((ch == ' ' || ch == '\n') && (j != 0)){
                buffer[j] = '\0';
                j = 0;

                if(isKeyword(buffer) == 1){
                    strcpy(keywords[kw_idx++], buffer);
                    ++kc;
                }
                else{
                    if(buffer[0] >= 97 && buffer[0] <= 122) {
                        if(mark[buffer[0] - 'a'] != 1){
                            identifiers[id_idx++][0] = buffer[0];
                            ++ic;
                            mark[buffer[0] - 'a'] = 1;
                        }
                    }
                }
            }
        }
    }

    fin.close();
    printf("Keywords: ");
    for(int f=0; f<kc; ++f){
        if(f == kc - 1){
            cout << keywords[f] << "\n";
        }
        else {
            cout << keywords[f] << ", ";
        }
    }
    printf("Identifiers: ");
    for(int f=0; f<ic; ++f){
        if(f == ic - 1){
            cout << identifiers[f][0] << "\n";
        }
        else {
            cout << identifiers[f][0] << ", ";
        }
    }
    printf("Math Operators: ");
    for(int f=0; f<mc; ++f){
        if(f == mc - 1){
            cout << math_ops[f] << "\n";
        }
        else {
            cout << math_ops[f] << ", ";
        }
    }
    printf("Logical Operators: ");
    for(int f=0; f<lc; ++f){
        if(f == lc - 1){
            cout << logical_ops[f] << "\n";
        }
        else {
            cout << logical_ops[f] << ", ";
        }
    }
    printf("Numerical Values: ");
    for(int f=0; f<nc; ++f){
        if(f == nc - 1){
            cout << numericals[f] << "\n";
        }
        else {
            cout << numericals[f] << ", ";
        }
    }
    printf("Others: ");
    for(int f=0; f<oc; ++f){
        if(f == oc - 1){
            cout << others[f] << "\n";
        }
        else {
            cout << others[f] << " ";
        }
    }

    return 0;
}


