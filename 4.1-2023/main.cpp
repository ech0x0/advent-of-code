#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

int main() {
    std::ifstream in("input");

    int result = 0;
    std::string card;
    while (getline(in, card)) {
        card = card.substr(card.find_first_of(':') + 2);

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

        if (matches != 0) result += 1 << (matches - 1);
    }

    std::cout << result << '\n';
}