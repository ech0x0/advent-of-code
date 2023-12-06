#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

std::vector<std::map<std::string, int>> parseGameData(const std::string& gameDataString) {
    std::istringstream gameDataStream(gameDataString);

    std::vector<std::map<std::string, int>> gameData;
    gameData.push_back(std::map<std::string, int>());

    bool run = true;
    while (run) {
        int n;
        std::string color;
        gameDataStream >> n >> color;

        switch (color.back()) {
        case ',':
            color.pop_back();
            gameData.back()[color] = n;
            break;
        case ';':
            color.pop_back();
            gameData.back()[color] = n;
            gameData.push_back(std::map<std::string, int>());
            break;
        default:
            run = false;
            gameData.back()[color] = n;
            break;
        }
    }

    return gameData;
}

int main() {
    std::ifstream in("input");

    int result = 0;
    std::string gameString;

    while (getline(in, gameString)) {
        const size_t colonIndex = gameString.find_first_of(':');
        int gameId = std::stoi(gameString.substr(4, colonIndex - 4));

        auto gameData = parseGameData(gameString.substr(colonIndex + 2));

        bool isValid = true;
        for (auto m : gameData) {
            if (m["red"] > 12) {
                isValid = false;
                break;
            }
            if (m["green"] > 13) {
                isValid = false;
                break;
            }
            if (m["blue"] > 14) {
                isValid = false;
                break;
            }
        }
        if (isValid) result += gameId;
    }

    std::cout << result << '\n';
    return 0;
}