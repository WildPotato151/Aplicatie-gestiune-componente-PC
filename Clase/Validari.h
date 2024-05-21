//
// Created by EON on 5/21/2024.
//

#ifndef VALIDARI_H
#define VALIDARI_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <regex>


using namespace std;


class Validari {
public:

    static vector<string> split(string str, char delimiter) {
        vector<string> tokens;
        char delimiterStr[] = {delimiter, '\0'};  // Convert delimiter to C-style string

        char* token = strtok(&str[0], delimiterStr);

        while (token != nullptr) {
            tokens.emplace_back(token);
            token = strtok(nullptr, delimiterStr);
        }

        return tokens;
    }

    static string toLowercase(string str)
    {
        string result = str;
        for (char& c : result)
        {
            c = tolower(c);
        }
        return result;
    }

    static bool validareDoarCifre(string str) {
        for (char ch : str) {
            if (!isdigit(ch)) {
                return false;
            }
        }
        return true;
    }

    static bool validareEmail(string email) {
        regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");

        return regex_match(email, pattern);
    }

};


#endif //VALIDARI_H
