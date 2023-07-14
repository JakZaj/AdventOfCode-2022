#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>

#include "point.h"

using namespace std;

bool tailMove(Point head, Point *tail) {

    if (abs(head.getY() - tail->getY()) > 1) {

        tail->setY(tail->getY() + (head.getY() - tail->getY()) / 2);

        if (head.getX() != tail->getX()) {
            if ((abs(head.getX() - tail->getX()) > 1)) {
                tail->setX(tail->getX() + (head.getX() - tail->getX()) / 2);
            }
            else {
                tail->setX(head.getX());
            }
        }

        return true;
    }

    if (abs(head.getX() - tail->getX()) > 1) {

        tail->setX(tail->getX() + (head.getX() - tail->getX()) / 2);

        if (head.getY() != tail->getY()) {
            tail->setY(head.getY());
        }
        return true;
    }

    return false;
}

int main()
{
    ifstream myfile("input.txt");

    string line;

    string moveDirection;
    int steps;

    Point head(0, 0);
    Point tail(0, 0);

    Point tailPartTwo[9];

    list<Point> visitedPoint;
    list<Point> visitedPointPartTwo;

    visitedPoint.push_back(Point(0,0));
    visitedPointPartTwo.push_back(Point(0,0));

    if (myfile.is_open())
    {
        string token;
        
        while (getline(myfile, line)) {
            istringstream iss(line);

            iss >> moveDirection;
            iss >> token;

            steps = stoi(token);

            for (int i = 0; i < steps; i++) {
                switch (moveDirection.at(0)) {
                    case 'U':
                        head.setY(head.getY() + 1);
                        break;
                    case 'R': 
                        head.setX(head.getX() + 1);
                        break;
                    case 'D': 
                        head.setY(head.getY() - 1);
                        break;
                    case 'L': 
                        head.setX(head.getX() - 1);
                        break;
                }

                list<Point>::iterator point;
                bool addNewPointToList = true;

                if (tailMove(head, &tail)) {                  

                    for (point = visitedPoint.begin(); point != visitedPoint.end(); point++)
                    {
                        if (*point == tail) {
                            addNewPointToList = false;
                            break;
                        }
                    }

                    if (addNewPointToList) {
                        visitedPoint.push_back(Point(tail.getX(), tail.getY()));
                    }
                }

                tailMove(head, &tailPartTwo[0]);
                
                bool isTailMoved = false;

                for (int k = 0; k < 8; k++) {
                    isTailMoved = tailMove(tailPartTwo[k], &tailPartTwo[k + 1]);
                }

                if (isTailMoved) {

                    addNewPointToList = true;

                    for (point = visitedPointPartTwo.begin(); point != visitedPointPartTwo.end(); point++)
                    {
                        if (*point == tailPartTwo[8]) {
                            addNewPointToList = false;
                            break;
                        }
                    }

                    if (addNewPointToList) {
                        visitedPointPartTwo.push_back(Point(tailPartTwo[8].getX(), tailPartTwo[8].getY()));
                    }
                }
            }
        }
        myfile.close();
        myfile.clear();

        cout << "Visited at least once: " << visitedPoint.size() << endl;
        cout << "Visited at least once part two: " << visitedPointPartTwo.size() << endl;
    }

    else cout << "Unable to open file";

    return 0;
}

