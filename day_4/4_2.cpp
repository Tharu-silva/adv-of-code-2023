#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

void split(const string& str, char delim, vector<string>& out)
{
    stringstream str_strm {str};
    string elem{};

    while (getline(str_strm, elem, delim))
    {
        out.emplace_back(elem);
    }
}


bool is_whitespace(const std::string& str) {

    return str.find_first_not_of(' ') == string::npos;
}

int main()
{

    //Parse input. Add wining nums into hashset and then iterate over the numbers we have
    ifstream file {"../input.txt"};
    string line{};

    const size_t L {209};
    int curr_card {0};
    int copy_sum {0};
    array<int, L> copies {};

    while (getline(file, line))
    {
        size_t colon_idx {line.find(':')};
        vector<string> numSets{};
        split(line.substr(colon_idx + 2), '|', numSets);

        size_t WIN {0};
        size_t NUMS{1};

        //Add each winning num to hashset
        vector<string> winning_nums {};
        split(numSets[WIN], ' ', winning_nums);

        unordered_set<int> winning_set{};
        for (const auto& winning_num: winning_nums)
        {
//            cout << winning_num << '\n';
            if (!is_whitespace(winning_num))
            {
                winning_set.insert(stoi(winning_num));
            }
        }

        //Iterate over nums and check for matches in winnnig nums
        int matches {0};
        vector<string> ourNums {};
        split(numSets[NUMS], ' ', ourNums);
        for (const auto& num: ourNums)
        {
//            cout << num << '\n';
            if (!is_whitespace(num) && winning_set.find(stoi(num)) != winning_set.end())
            {
                matches += 1;
            }
        }

        //Increment the current card num by 1
        copies[curr_card] += 1;
        while (matches > 0)
        {
            copies[curr_card + matches] += copies[curr_card];
            matches -= 1;
        }
        copy_sum += copies[curr_card];
//        cout << copies[curr_card] << endl;
        curr_card += 1;
    }

    cout << copy_sum << endl;
    return 0;

}