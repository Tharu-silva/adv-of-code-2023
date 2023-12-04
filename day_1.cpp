#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <array>
#include <vector>

int main()
{
    std::ifstream file {"./test.txt"};
    std::string line{};

    std::array<std::string, 9> strDigits{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int calibration_sum{};
    while (std::getline(file, line))
    {
        int calibrationNum{};
        int isFirst {true};
        int first{};
        int last{};

        for (int i{0}; i < line.size(); i++)
        {
            char c{line.at(i)};
            if (isdigit(c))
            {
                int num{c - '0'};
                first = isFirst ? num: first;
                last = num;
                isFirst = false;
            }

            //Do stringified digit checking
            for (int k{0}; k < strDigits.size(); k++)
            {
                const auto& digit{strDigits[k]};

                //Check whether remaining length is enough to fit the current digit
                if ( (line.size() - i) >= digit.size() )
                {
//                    std::cout << "hits";
                    //Check if substr is eq
                    if (line.substr(i, digit.size()) == digit)
                    {
//                        std::cout << "hits: " << k << '\n';
                        first = isFirst ? (k + 1) : first;
                        last = k + 1;
                        isFirst = false;
                    }

                }
            }

        }

        calibrationNum = 10 * first + last;
        std::cout << calibrationNum << '\n';
        calibration_sum += calibrationNum;
        isFirst = true;
    }

    std::cout << calibration_sum <<'\n';


    return 0;
}

