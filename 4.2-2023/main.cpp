#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <numeric>

std::map<int, int> cardNumber;

int processCard(const std::string& card) {
    const size_t separator = card.find_first_of('|');
    std::istringstream winningNumbersStream(card.substr(0, separator - 1));
    std::istringstream yourNumbersStream(card.substr(separator + 2));

    int number;
    std::set<int> winningNumbers;
    while (winningNumbersStream >> number) {
        winningNumbers.insert(number);
    }

    int matches = 0;
    while (yourNumbersStream >> number) {
        if (winningNumbers.find(number) != winningNumbers.end()) ++matches;
    }

    return matches;
}

int main() {
    std::ifstream in("input");

    int cardIndex = 0;
    std::string card;
    while (getline(in, card)) {
        card = card.substr(card.find_first_of(':') + 2);

        const int matches = processCard(card);
        for (int i = 1; i <= matches; ++i) {
            cardNumber[i + cardIndex] += cardNumber[cardIndex] + 1;
        }

        ++cardIndex;
    }

    int result = 0;
    for (int i = 0; i < cardIndex; ++i) {
        result += cardNumber[i] + 1;
    }

    std::cout << result << '\n';
}