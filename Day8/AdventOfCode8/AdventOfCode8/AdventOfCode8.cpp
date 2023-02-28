#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void checkVisibleTreeTop(int** treeGrid, int** treeVisible, const int x, const int y) {
    
    int treeToCheck = 0;
    for (int i = 1; i < x-1; i++)
    {
        treeToCheck = treeGrid[0][i];
        for (int j = 1; j < y-1; j++) {
            if (treeToCheck >= treeGrid[j][i]) {
                continue;
            }
            treeToCheck = treeGrid[j][i];
            treeVisible[j][i] += 1;
        }
    }
}

void checkVisibleTreeLeft(int** treeGrid, int** treeVisible, const int x, const int y) {

    int treeToCheck = 0;
    for (int i = 1; i < y - 1; i++)
    {
        treeToCheck = treeGrid[i][0];
        for (int j = 1; j < x - 1; j++) {
            if (treeToCheck >= treeGrid[i][j]) {
                continue;
            }
            treeToCheck = treeGrid[i][j];
            treeVisible[i][j] += 1;
        }
    }
}

void checkVisibleTreeDown(int** treeGrid, int** treeVisible, const int x, const int y) {

    int treeToCheck = 0;
    for (int i = 1; i < x - 1; i++)
    {
        treeToCheck = treeGrid[y-1][i];
        for (int j = y - 2; j > 1; j--) {
            if (treeToCheck >= treeGrid[j][i]) {
                continue;
            }
            treeToCheck = treeGrid[j][i];
            treeVisible[j][i] += 1;
        }
    }
}

void checkVisibleTreeRight(int** treeGrid, int** treeVisible, const int x, const int y) {

    int treeToCheck = 0;
    for (int i = 1; i < y - 1; i++)
    {
        treeToCheck = treeGrid[i][x-1];
        for (int j = x-2; j > 0; j--) {
            if (treeToCheck >= treeGrid[i][j]) {
                continue;
            }
            treeToCheck = treeGrid[i][j];
            treeVisible[i][j] += 1;
        }
    }
}
int getViewDistanceTop(int** treeGrid, const int checkedX, const int checkedY) {
    int returnDistance = 0;
    for (int i = checkedY-1; i >= 0; i--) {
        if (treeGrid[checkedY][checkedX] <= treeGrid[i][checkedX]) {
            return ++returnDistance;
        }
        returnDistance++;
    }
    return returnDistance;
}

int getViewDistanceLeft(int** treeGrid, const int checkedX, const int checkedY) {
    int returnDistance = 0;
    for (int i = checkedX - 1; i >= 0; i--) {
        if (treeGrid[checkedY][checkedX] <= treeGrid[checkedY][i]) {
            return ++returnDistance;
        }
        returnDistance++;
    }
    return returnDistance;
}

int getViewDistanceDown(int** treeGrid, const int checkedX, const int checkedY, const int y) {
    int returnDistance = 0;
    for (int i = checkedY + 1; i < y; i++) {
        if (treeGrid[checkedY][checkedX] <= treeGrid[i][checkedX]) {
            return ++returnDistance;
        }
        returnDistance++;
    }
    return returnDistance;
}

int getViewDistanceRight(int** treeGrid, const int checkedX, const int checkedY, const int x) {
    int returnDistance = 0;
    for (int i = checkedX + 1; i < x; i++) {
        if (treeGrid[checkedY][checkedX] <= treeGrid[checkedY][i]) {
            return ++returnDistance;
        }
        returnDistance++;
    }
    return returnDistance;
}

int getScenicScore(int** treeGrid, const int x, const int y) {

    int returnScore = 0, scoreToCheck = 0;

    for (int i = 1; i < y - 1; i++)
    {
        for (int j = 1; j < x - 1; j++) {
            scoreToCheck = getViewDistanceTop(treeGrid, j, i) * getViewDistanceLeft(treeGrid, j, i) * getViewDistanceDown(treeGrid, j, i, y) * getViewDistanceRight(treeGrid, j, i, x);
            if (returnScore < scoreToCheck) {
                returnScore = scoreToCheck;
            }
        }
    }
    return returnScore;
}

void destroyGrid(int** gridToDestroy, const int y) {
    for (int i = 0; i < y; i++) {
        delete gridToDestroy[i];
    }
    delete gridToDestroy;
}

int main()
{
    ifstream myfile("input.txt");
    int **treeGrid, **treeVisible;
    int xLenght = 0, yLenght = 0;
    int visibleTreeCounter = 0;

    string line;

    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            if(xLenght == 0) 
                xLenght = line.length();
            yLenght++;
            
        }
        myfile.close();
        myfile.clear();


        treeGrid = new int* [yLenght];
        treeVisible = new int* [yLenght];
        
        for (int i = 0; i < yLenght; i++){
            treeGrid[i] = new int[xLenght];
            treeVisible[i] = new int[xLenght];
        }

        myfile.open("input.txt");

        for (int i = 0; i < yLenght; i++)
        {
            for (int j = 0; j < xLenght; j++) {
                treeGrid[i][j] = 0;
                treeVisible[i][j] = 0;
            }
        }

        if (myfile.is_open())
        {
            yLenght = 0;
            while (getline(myfile, line)) {
                for (int i = 0; i < xLenght; i++) {
                    treeGrid[yLenght][i]=line.at(i)-'0';

                }
                yLenght++;
            }
            myfile.close();
            myfile.clear();


            checkVisibleTreeTop(treeGrid, treeVisible, xLenght, yLenght);
            checkVisibleTreeLeft(treeGrid, treeVisible, xLenght, yLenght);
            checkVisibleTreeDown(treeGrid, treeVisible, xLenght, yLenght);
            checkVisibleTreeRight(treeGrid, treeVisible, xLenght, yLenght);
            
            visibleTreeCounter += xLenght * 2 + yLenght * 2 - 4;

            for (int i = 0; i < yLenght; i++)
            {
                for (int j = 0; j < xLenght; j++) {
                    if (treeVisible[i][j] > 0) {
                        visibleTreeCounter++;
                    }
                }
            }

            cout << "Visible Tree = " << visibleTreeCounter << "\n";

            cout << "Highest scenic score = " << getScenicScore(treeGrid, xLenght, yLenght);

            destroyGrid(treeVisible, yLenght);
            destroyGrid(treeGrid, yLenght);
        }

        else cout << "Unable to open file";

    }

    else cout << "Unable to open file";

    return 0;
}

