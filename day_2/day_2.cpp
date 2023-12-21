#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <array>


std::vector<std::string> split(const std::string& elem ,const std::string& delimiter) {
    std::vector<std::string> components{};
    std::size_t start_idx{0};
    std::size_t next_delim_idx{elem.find(delimiter)};

    std::cout << elem << '\n';
    std::cout << next_delim_idx << '\n';

    std::string new_elem {elem.substr(start_idx, next_delim_idx)};

    while (next_delim_idx != std::string::npos) {
        components.emplace_back(new_elem);
        start_idx = next_delim_idx;
        next_delim_idx = (elem.substr(next_delim_idx + 1)).find(delimiter);
        std::cout << next_delim_idx << '\n';
    }

    //Add last component
    components.emplace_back(elem.substr(start_idx));

    return components;
}

enum COLORS
{
    RED,
    GREEN,
    BLUE,
    MAX_COLOURS
};

int main()
{
    std::array color_max {12, 13, 14};

    std::ifstream file {"./input.txt"};
    std::string line{};
    int id_sum {};
    int power_sum {};
    while (std::getline(file, line))
    {
        std::array fewestCubes {0, 0, 0};
        std::size_t colon_idx { line.find(':') };
        int id { std::stoi(line.substr(line.find(' ') + 1, colon_idx))};
        bool isValidGame{ true };

        std::string set{};
        std::stringstream line_strm {line.substr(colon_idx + 1)};

        while (std::getline(line_strm, set, ';'))
        {
            std::string pick {};
            std::stringstream set_strm {set};

            //Get individual colour counts for a set
            while (std::getline(set_strm, pick, ','))
            {
                //remove first space
                pick = pick.substr(1);
                int amount { std::stoi(pick.substr(0, pick.find(' '))) };
//                std::cout << amount << '\n';

                std::string color {pick.at(pick.find(' ') + 1)};
//                std::cout << color << '\n';

                if (color == "b")
                {
                    fewestCubes[BLUE] = std::max(fewestCubes[BLUE], amount);
                    isValidGame = isValidGame && (amount <= color_max[BLUE]);

                } else if (color == "r")
                {
                    fewestCubes[RED] = std::max(fewestCubes[RED], amount);
                    isValidGame = isValidGame && (amount <= color_max[RED]);
                } else
                {
                    fewestCubes[GREEN] = std::max(fewestCubes[GREEN], amount);
                    isValidGame = isValidGame && (amount <= color_max[GREEN]);
                }
            }
        }
        id_sum += isValidGame ? id : 0;

        power_sum += (fewestCubes[RED] * fewestCubes[GREEN] * fewestCubes[BLUE]);


    }

    std::cout << id_sum << '\n';
    std::cout << power_sum << '\n';
}
