#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

bool isDigit(char ch) {
    return ('9' >= ch) && ('0' <= ch);
}

bool isSymbol(char ch) {
    return (ch != '.') && (!isDigit(ch));
}

int main() {
    std::ifstream in("input");

    int result = 0;

    std::vector<std::string> engine;
    std::string line;
    while (in >> line) engine.push_back(line);

    for (size_t i = 0; i < engine.size(); ++i) {
        auto numberStart = engine[i].begin();

        numberStart = std::find_if(numberStart, engine[i].end(), isDigit);
        while (numberStart != engine[i].end()) {
            auto numberEnd = std::find_if_not(numberStart, engine[i].end(), isDigit);
            size_t startIndex = numberStart - engine[i].begin();
            size_t endIndex = numberEnd - engine[i].begin() - 1;

            bool partNumber = false;
            if (numberStart != engine[i].begin()) {
                partNumber |= isSymbol(engine[i][startIndex - 1]);
                if (i != 0) partNumber |= isSymbol(engine[i - 1][startIndex - 1]);
                if (i != engine.size() - 1) partNumber |= isSymbol(engine[i + 1][startIndex - 1]);
            }
            if (numberEnd != engine[i].end()) {
                partNumber |= isSymbol(engine[i][endIndex + 1]);
                if (i != 0) partNumber |= isSymbol(engine[i - 1][endIndex + 1]);
                if (i != engine.size() - 1) partNumber |= isSymbol(engine[i + 1][endIndex + 1]);
            }

            if (i != 0) {
                for (size_t j = startIndex; j <= endIndex; ++j) {
                    partNumber |= isSymbol(engine[i - 1][j]);
                }
            }
            if (i != engine.size() - 1) {
                for (size_t j = startIndex; j <= endIndex; ++j) {
                    partNumber |= isSymbol(engine[i + 1][j]);
                }
            }

            int number = std::stoi(engine[i].substr(startIndex, endIndex - startIndex + 1));
            if (partNumber) result += number;

            numberStart = std::find_if(numberEnd, engine[i].end(), isDigit);
        }
    }

    std::cout << result << '\n';

    return 0;
}