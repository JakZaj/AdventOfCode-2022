#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  

using namespace std;

int main()
{
    string line;
    ifstream myfile("input.txt");

    vector < int > elfs_calories;

    int count_calories_for_elf = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.length() == 0) {
                elfs_calories.push_back(count_calories_for_elf);
                count_calories_for_elf = 0;
                continue;
            }
            count_calories_for_elf += stoi(line);
        }
        myfile.close();

        elfs_calories.push_back(count_calories_for_elf);

    }

    else cout << "Unable to open file";

    sort(elfs_calories.begin(), elfs_calories.end());
    reverse(elfs_calories.begin(), elfs_calories.end());

    cout << elfs_calories.at(0) << '\n' << elfs_calories.at(0) + elfs_calories.at(1) + elfs_calories.at(2) << '\n';
}
