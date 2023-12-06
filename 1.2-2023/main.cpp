#include <iostream>
#include <fstream>
#include <string>

const std::string numbers[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int getCalibration(const std::string& str) {
    int firstDigit = 0, lastDigit = 0;
    size_t firstDigitIndex, lastDigitIndex;

    firstDigitIndex = str.find_first_of("0123456789");
    lastDigitIndex = str.find_last_of("0123456789");

    if (firstDigitIndex != std::string::npos) {
        firstDigit = str[firstDigitIndex] - '0';
    }
    if (lastDigitIndex != std::string::npos) {
        lastDigit = str[lastDigitIndex] - '0';
    } else {
        lastDigitIndex = 0;
    }

    for (int i = 0; i < 10; ++i) {
        size_t index = str.find(numbers[i]);
        if (index != std::string::npos && index < firstDigitIndex) {
            firstDigitIndex = index;
            firstDigit = i;
        }
        index = str.rfind(numbers[i]);
        if (index != std::string::npos && index > lastDigitIndex) {
            lastDigitIndex = index;
            lastDigit = i;
        }
    }

    return firstDigit * 10 + lastDigit;
}

int main() {
    std::ifstream in("input");

    std::string str;
    int result = 0;
    while (in >> str) {
        result += getCalibration(str);
    }

    std::cout << result;
    return 0;
}
