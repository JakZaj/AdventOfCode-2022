#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string line;
    ifstream myfile("input.txt");

    vector < char > stacks[9];
    vector < char > stacksPart2[9];
    char tmp;

    if (myfile.is_open())
    {

        while (getline(myfile, line))
        {
            if (line.find('1') != -1)
            {
                getline(myfile, line);
                break;
            }
            for (int i = 0; i < 9; i++) {
                tmp = line.at(i * 4 + 1);
                if (tmp != ' ')
                {
                    stacks[i].push_back(tmp);
                }
            }
        }

        for (int i = 0; i < 9; i++)
        {
            reverse(stacks[i].begin(), stacks[i].end());

            stacksPart2[i] = stacks[i];
        }

        int numberOfMove, fromStack, toStack = 0;

        while (getline(myfile, line))
        {
            numberOfMove = stoi(line.substr(4, line.find("from") - 1));
            fromStack = stoi(line.substr(line.find("from") + 5, line.find("to") - 1));
            toStack = stoi(line.substr(line.find("to") + 2));

            for (int i = 0; i < numberOfMove; i++)
            {
                stacks[toStack-1].push_back(stacks[fromStack-1].back());
                stacks[fromStack-1].pop_back();
            }

            for (int i = 0; i < numberOfMove; i++)
            {
                stacksPart2[toStack - 1].push_back(stacksPart2[fromStack - 1].at(stacksPart2[fromStack - 1].size() - numberOfMove + i));
            }

            for (int i = 0; i < numberOfMove; i++) {
                stacksPart2[fromStack - 1].pop_back();
            }

        }
        myfile.close();

    }

    else cout << "Unable to open file";

    for (int i = 0; i < 9; i++)
    {
        cout << stacks[i].back();
    }
    cout << '\n';

    for (int i = 0; i < 9; i++)
    {
        cout << stacksPart2[i].back();
    }
    cout << '\n';
}
