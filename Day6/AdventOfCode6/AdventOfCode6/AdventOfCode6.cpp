#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int getResult(ifstream& openFile, int lenghtToChecked);

int main()
{
    ifstream myfile("input.txt");

    int resultFirstPart = 0, resultSecondPart = 0;

    if (myfile.is_open())
    {
        resultFirstPart = getResult(myfile, 4);

        myfile.close();
        myfile.clear();
    }

    else cout << "Unable to open file";

    cout << "Checked lenght 4: " << resultFirstPart << "\n";

    myfile.open("input.txt");
    if (myfile.is_open())
    {
        resultSecondPart = getResult(myfile, 14);

        myfile.close();
        myfile.clear();
    }

    else cout << "Unable to open file";

    cout << "Checked lenght 14: " << resultSecondPart << "\n";
   
}

int getResult(ifstream& openFile, int lenghtToChecked) {
        
        vector < char > stack;
        char characterRead;
        int result = 0;
        bool skipThisCheck = false, resultIsFound = false;

        for (int i = 0; i < lenghtToChecked - 1; i++) {
            openFile.get(characterRead);
            stack.insert(stack.begin(), characterRead);
            result++;
        }

        while (openFile.get(characterRead))
        {
            stack.insert(stack.begin(), characterRead);
            result++;

            for (int firstLoop = lenghtToChecked - 1; firstLoop > 0; firstLoop--) {
                for (int secondLoop = firstLoop - 1; secondLoop >= 0; secondLoop--) {
                    if (stack.at(firstLoop) == stack.at(secondLoop)) {
                        skipThisCheck = true;
                    }
                }

                if (skipThisCheck) {
                    skipThisCheck = false;
                    break;
                }

                if (firstLoop == 1)
                {
                    resultIsFound = true;
                }
            }

            if (resultIsFound) {
                break;
            }

            stack.pop_back();
        }
    return result;
}
