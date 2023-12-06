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

bool isGear(char ch) {
    return ch == '*';
}

int main() {
    std::ifstream in("input");

    int result = 0;

    std::vector<std::string> engine;
    std::string line;
    while (in >> line) engine.push_back(line);

    for (size_t i = 0; i < engine.size(); ++i) {
        auto gear = engine[i].begin();

        gear = std::find_if(gear, engine[i].end(), isGear);
        while (gear != engine[i].end()) {
            size_t gearIndex = gear - engine[i].begin();

            std::vector<std::pair<size_t, size_t>> numbersAround;
            if (i != 0) {
                bool isMiddleDigit = isDigit(engine[i - 1][gearIndex]);
                if (isMiddleDigit) numbersAround.push_back({ i - 1, gearIndex });
                if (gearIndex != 0 && !isMiddleDigit)
                    if (isDigit(engine[i - 1][gearIndex - 1])) numbersAround.push_back({ i - 1, gearIndex - 1 });
                if (gearIndex != engine[i].size() - 1 && !isMiddleDigit)
                    if (isDigit(engine[i - 1][gearIndex + 1])) numbersAround.push_back({ i - 1, gearIndex + 1 });
            }

            if (gearIndex != 0)
                if (isDigit(engine[i][gearIndex - 1])) numbersAround.push_back({ i, gearIndex - 1 });
            if (gearIndex != engine[i].size() - 1)
                if (isDigit(engine[i][gearIndex + 1])) numbersAround.push_back({ i, gearIndex + 1 });

            if (i != engine.size() - 1) {
                bool isMiddleDigit = isDigit(engine[i + 1][gearIndex]);
                if (isMiddleDigit) numbersAround.push_back({ i + 1, gearIndex });
                if (gearIndex != 0 && !isMiddleDigit)
                    if (isDigit(engine[i + 1][gearIndex - 1])) numbersAround.push_back({ i + 1, gearIndex - 1 });
                if (gearIndex != engine[i].size() - 1 && !isMiddleDigit)
                    if (isDigit(engine[i + 1][gearIndex + 1])) numbersAround.push_back({ i + 1, gearIndex + 1 });
            }

            if (numbersAround.size() == 2) {
                size_t number0Start = numbersAround[0].second;
                size_t number0End = numbersAround[0].second;
                while (number0Start > 0 && isDigit(engine[numbersAround[0].first][number0Start - 1])) --number0Start;
                while (engine[numbersAround[0].first].size() - 1 > number0End && isDigit(engine[numbersAround[0].first][number0End + 1])) ++number0End;
                size_t number1Start = numbersAround[1].second;
                size_t number1End = numbersAround[1].second;
                while (number1Start > 0 && isDigit(engine[numbersAround[1].first][number1Start - 1])) --number1Start;
                while (engine[numbersAround[1].first].size() - 1 > number1End && isDigit(engine[numbersAround[1].first][number1End + 1])) ++number1End;

                int number0 = std::stoi(engine[numbersAround[0].first].substr(number0Start, number0End - number0Start + 1));
                int number1 = std::stoi(engine[numbersAround[1].first].substr(number1Start, number1End - number1Start + 1));
                result += number0 * number1;
            }

            gear = std::find_if(gear + 1, engine[i].end(), isGear);
        }
    }

    std::cout << result << '\n';

    return 0;
}