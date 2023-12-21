#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

typedef std::vector<std::string> Grid;

struct Pos
{
    std::size_t row{};
    std::size_t col{};
};

//When given a pos and a grid. Will parse to left and right for a contigious num containing pos
//Then it will rewrite the num ints to be '.'
int parseNum(Grid& grid, std::size_t row, std::size_t col)
{
//    std::cout << grid[row][col] << '\n';

    std::string left_int_str{};
    std::string right_int_str{};

    //Parse to the right
    std::size_t curr_col {col};
    std::size_t end_idx{col};

    while (isdigit(grid[row][curr_col]) && curr_col < grid[0].size())
    {
        //Rewrite int char
        curr_col += 1;
    }
    end_idx = curr_col;

    //Parse to the left
    std::size_t start_idx{col};
    if (col != 0)
    {
        curr_col = col - 1;
        while (isdigit(grid[row][curr_col]) && curr_col >= 0)
        {
            curr_col -= 1;
        }
        start_idx = curr_col + 1;
    }

    //Convert to int
//    std::cout << start_idx << ',' << end_idx << ',' << grid[row].substr(start_idx, end_idx - start_idx) << '\n';
    int num {std::stoi(grid[row].substr(start_idx, end_idx - start_idx))};
    //Rewrite num
    for (; start_idx < end_idx; start_idx++)
    {
        grid[row][start_idx] = '.';
    }

    return num;
}

//Return true if modification to row and col is within grid bounds
bool check_coord_mod(Grid& grid, std::size_t row, std::size_t col, int row_mod, int col_mod)
{
    return (row + row_mod) >= 0 && (row + row_mod) < grid.size() && (col + col_mod) >= 0 && (col + col_mod) < grid[0].size();
}


int main()
{
    //Input parsing
    std::ifstream file {"../input.txt"};
    std::string line{};
    Grid grid{};

    while (std::getline(file, line))
    {
        grid.emplace_back(line);
    }


    //Loop over grid
    //When a * is reached look at each possible dir
    //If it is a number then call parse_num with that pos
    //Then add it to the parts sum

    int part_sum {};
    std::size_t ROWS {grid.size()};
    std::size_t COLS {grid[0].size()};
    int dirs[8][2] {
            {0,1},
            {0, -1},
            {1,1},
            {1,-1},
            {1,0},
            {-1,0},
            {-1,1},
            {-1,-1},
    };

    for (std::size_t row{0}; row < ROWS; row++)
    {
        for (std::size_t col{0}; col < COLS; col++)
        {
            char symbol {grid[row][col]};
            if (symbol == '*')
            {
                //Count num of adj cells
                int adj_gears{};
                int gear_ratio{1};
                for (const auto& dir: dirs)
                {
                    std::size_t new_row {row};
                    std::size_t new_col {col};
                    if (check_coord_mod(grid, row, col, dir[0], dir[1]))
                        new_row = row + dir[0]; new_col = col + dir[1];

                    if (isdigit(grid[new_row][new_col]))
                    {
                        adj_gears += 1;
                        gear_ratio *= parseNum(grid, new_row, new_col);
                    }
                }

                if (adj_gears == 2)
                {
                    part_sum += gear_ratio;
                }
            }
        }
    }

    std::cout << part_sum << '\n';
    return 0;
}

