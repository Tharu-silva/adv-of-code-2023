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

void split(const string& str, char delim, vector<vector<long>>& out)
{
    stringstream str_strm {str};
    string elem{};

    vector<long> range{};

    while (getline(str_strm, elem, delim))
    {
        if (range.size() == 2)
        {
            //Change second to max
            range[1] = range[0] + range[1] - 1;
            out.emplace_back(range);
            range.clear();
        }

        range.emplace_back(stol(elem));
    }

    range[1] = range[0] + range[1] - 1;
    out.emplace_back(range);
}

void split(const string& str, char delim, vector<long>& out)
{
    stringstream str_strm {str};
    string elem{};


    while (getline(str_strm, elem, delim))
    {
        out.emplace_back(stol(elem));
    }

}


bool checkWithinMin(long min, long range, long val)
{
    return (min <= val) && (val < (min + range));
}

bool checkWithinMax(long min, long  range, long val)
{
    return (min <= val) && (val < (min + range));
}

int main()
{
    ifstream file {"../input.txt"};
    string line{};

    //Get seeds
    vector<vector<long>> seed_ranges{};
    vector<bool> isMapped{};

    int SEED_START {7};
    getline(file, line);
    split(line.substr(SEED_START), ' ', seed_ranges);

    for (int i{0}; i < seed_ranges.size(); i++)
    {
        isMapped.emplace_back(false);
    }

//    for (const auto& seed_range: seed_ranges)
//    {
//        cout << seed_range[0] << ' ' << seed_range[1] << endl;
//    }


    //Move to soil map
    getline(file,line);
    getline(file,line);

    //Map
    while(getline(file, line))
    {
        //Next conversion hit
        if (!isdigit(line[0])) {
//          Reset isMapped
            for (int i{0}; i < isMapped.size(); i++) {
                isMapped[i] = false;
            }

            getline(file, line);

//            for (const auto& seed_range: seed_ranges)
//            {
//                cout << seed_range[0] << ' ' << seed_range[1] << endl;
//            }
//            cout << line << endl;
            continue;
        }

        vector<long> mapInfo{};
        split(line, ' ', mapInfo);

        long sourceMin{mapInfo[SOURCE]};
        long sourceMax{mapInfo[SOURCE] + mapInfo[RANGE] - 1};

        size_t idx{};

        while (idx < seed_ranges.size())
        {
            if (!isMapped[idx])
            {
                long seed_min{seed_ranges[idx][0]};
                long seed_max{seed_ranges[idx][1]};

                //Range is within max
                if (checkWithinMin(mapInfo[SOURCE], mapInfo[RANGE], seed_min))
                {
                    //Check if range needs to be split
                    if (seed_max > sourceMax) {
                        //Add new range
                        long new_max{seed_max};
                        long new_min{sourceMax + 1};
                        seed_ranges.emplace_back(vector<long>{new_min, new_max});

                        //Add to isMapped
                        isMapped.emplace_back(false);

                        //Update current max
                        seed_ranges[idx][1] = sourceMax;
                    }

                    //Map min
                    seed_ranges[idx][0] = seed_ranges[idx][0] - mapInfo[SOURCE] + mapInfo[DEST];
                    //Map max
                    seed_ranges[idx][1] = seed_ranges[idx][1] - mapInfo[SOURCE] + mapInfo[DEST];

                    //Set is mapped
                    isMapped[idx] = true;


                } else if (checkWithinMax(mapInfo[SOURCE], mapInfo[RANGE], seed_max))
                { //Within max
                    //Split
                    long new_min{seed_min};
                    long new_max{sourceMin - 1};

                    seed_ranges.emplace_back(vector<long>{new_min, new_max});
                    isMapped.emplace_back(false);

                    //Update current min
                    seed_ranges[idx][0] = sourceMin;

                    //Map min
                    seed_ranges[idx][0] = seed_ranges[idx][0] - mapInfo[SOURCE] + mapInfo[DEST];
                    //Map max
                    seed_ranges[idx][1] = seed_ranges[idx][1] - mapInfo[SOURCE] + mapInfo[DEST];

                    //Set is mapped
                    isMapped[idx] = true;
                }
            }

//            cout << seed_ranges[0][0] << ' ' << seed_ranges[0][1] << ' ' << seed_ranges.size() << endl;
            idx++;
        }


    }

//    for (const auto& seed_range: seed_ranges)
//    {
//        cout << seed_range[0] << ' ' << seed_range[1] << endl;
//    }



    long min_loc{seed_ranges[0][0]};
    for (const auto& seed_range: seed_ranges)
    {
        min_loc = min(seed_range[0], min_loc);
    }

    cout << min_loc << endl;

    return 0;
}

