#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void split(const string& str, char delim, vector<int>& out)
{
    stringstream str_strm {str};
    string elem{};

    while (getline(str_strm, elem, delim))
    {
        out.emplace_back(stoi(elem));
    }

}

int main()
{
    ifstream file {"../input.txt"};
    string line{};

    //Get times
    getline(file, line);
    vector<int> times{};
    split(line, ' ', times);


    //Get dists
    getline(file, line);
    vector<int> dists{};
    split(line, ' ', dists);

    int acc{1};
    for (int i{}; i < times.size(); i++)
    {
        int n_ways{};

        int time{times[i]};
        int dist{dists[i]};

        int held_time{time};
        while (held_time > 0)
        {
            int speed{held_time};
            int remaining_time{time - held_time};

            n_ways += ( (remaining_time * speed) > dist) ? 1 : 0;
            held_time--;
        }

        acc *= n_ways != 0 ? n_ways : 1;
    }

    cout << acc << endl;
    return 0;
}
