#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


enum AlmanacRange: size_t
{
    DEST,
    SOURCE,
    RANGE
};

void split(const string& str, char delim, vector<long>& out)
{
    stringstream str_strm {str};
    string elem{};

    while (getline(str_strm, elem, delim))
    {
        out.emplace_back(stol(elem));
    }
}

bool checkInRange(long min, long range, long val)
{
    return (min <= val) && ( val < ( (min + range) ) );
}

int main()
{
    ifstream file {"../input.txt"};
    string line{};

    //Get seeds
    vector<long> seeds{};
    vector<bool> isMapped{};

    int SEED_START {7};
    getline(file, line);
    split(line.substr(SEED_START), ' ', seeds);

    for (int i{0}; i < seeds.size(); i++)
    {
        isMapped.emplace_back(false);
    }

    //Move to soil map
    getline(file,line);
    getline(file,line);

    //Map
    while(getline(file, line))
    {
        //Next conversion hit
        if (!isdigit(line[0]))
        {
//          Reset isMapped
            for (int i{0}; i < isMapped.size(); i++)
            {
                isMapped[i] = false;
            }
            getline(file,line);
            continue;
        }

        vector<long> mapInfo{};
        split(line, ' ', mapInfo);


        //Loop over seeds and check if map is reached
        for (int i{0}; i < seeds.size(); i++)
        {
            if (!isMapped[i])
            {
                long seed {seeds[i]};
                if (checkInRange(mapInfo[SOURCE], mapInfo[RANGE], seed))
                {
                    long dest { seed - mapInfo[SOURCE] + mapInfo[DEST] };
                    seeds[i] = dest;
                    isMapped[i] = true;
                }
            }
        }
//        cout << line << endl;
//        cout << seeds[0] << endl;
    }

    long min_loc{seeds[0]};
    for (const auto& seed: seeds)
    {
        min_loc = min(seed, min_loc);
    }

    cout << min_loc << endl;

    return 0;
}

