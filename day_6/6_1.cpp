#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

void split(const string& str, char delim, vector<long>& out)
{
    stringstream str_strm {str};
    string elem{};

    while (getline(str_strm, elem, delim))
    {
        out.emplace_back(stol(elem));
    }

}

long double quadraticFormula(long double a, long double b, long double c) {
    // Calculate the discriminant
    long double discriminant = b * b - 4 * a * c;

    // Calculate the square root of the discriminant
    long double sqrtDiscriminant = sqrt(discriminant);

    // Calculate the real solutions
    long double root1 = (-b + sqrtDiscriminant) / (2 * a);
    long double root2 = (-b - sqrtDiscriminant) / (2 * a);

    return min(root1, root2);
}

int main()
{
    ifstream file {"../input.txt"};
    string line{};

    //Get times
    getline(file, line);
    vector<long> times{};
    split(line, ' ', times);


    //Get dists
    getline(file, line);
    vector<long> dists{};
    split(line, ' ', dists);

    long acc{1};
    for (int i{}; i < times.size(); i++)
    {
        long n_ways{};

        long time{times[i]};
        long dist{dists[i]};

        long held_time{time};

        //O(1) sol
        //Calculate apex
        long double apex = time/static_cast<long double>(2);

        //Calculate intersection of dist and curve
        long double minToBeat = quadraticFormula(-1, time, -dist);


        long whole_num_apex {static_cast<long>(floor(apex))};
        long whole_num_minToBeat {static_cast<long>(floor(minToBeat + 1))};

        //Case 1
        if (ceil(apex) == floor(apex)) //Check if whole number
        {
            n_ways += (whole_num_apex - whole_num_minToBeat) * 2 + 1;
        } else
        {
            n_ways += (whole_num_apex - whole_num_minToBeat + 1) * 2;
        }

        acc *= n_ways != 0 ? n_ways : 1;
        cout << n_ways << endl;

//        while (held_time > 0)
//        {
//            long speed{held_time};
//            long remaining_time{time - held_time};
////          t - 2h = 0 => apex = floor(t/2)
////          mintobeat = quadFormula(b=t, a = -1, c = -dist)
////          => mintobeat = floor(minToBeat + 1)
////           Case 1: If apex is a whole num then total_num = (apex - mintobeat) * 2 + 1;
////           Case 2: If apex is not a whole num then total_num = (apex - mintobeat + 1) * 2;
//
//
//
//
////            (t - h) * h = th - h^2
////            cout << (remaining_time * speed) << endl;
//            n_ways += ( (remaining_time * speed) > dist) ? 1 : 0;
//            held_time--;
//        }

//        acc *= n_ways != 0 ? n_ways : 1;
//        break;
    }

    cout << acc << endl;
    return 0;
}