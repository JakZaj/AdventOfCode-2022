#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string line, firstElfSections, secondElfSections;

	ifstream myfile("input.txt");


	int points = 0, pointsOverlap = 0;
	int firstElfRange[2] = { 0 }, secondElfRange[2] = { 0 };

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			firstElfSections = line.substr(0, line.find(','));
			secondElfSections = line.substr(line.find(',') + 1);
			
			firstElfRange[0] = stoi(firstElfSections.substr(0, firstElfSections.find('-')));
			firstElfRange[1] = stoi(firstElfSections.substr(firstElfSections.find('-') + 1));

			secondElfRange[0] = stoi(secondElfSections.substr(0, secondElfSections.find('-')));
			secondElfRange[1] = stoi(secondElfSections.substr(secondElfSections.find('-') + 1));

			if ((firstElfRange[0] <= secondElfRange[0] && firstElfRange[1] >= secondElfRange[1]) || (firstElfRange[0] >= secondElfRange[0] && firstElfRange[1] <= secondElfRange[1]))
				points++;

			if ((firstElfRange[0] <= secondElfRange[0] && firstElfRange[1] >= secondElfRange[0]) || (firstElfRange[0] <= secondElfRange[1] && firstElfRange[1] >= secondElfRange[1]) || (firstElfRange[0] >= secondElfRange[0] && firstElfRange[1] <= secondElfRange[1]))
				pointsOverlap++;
		}

		cout << points << " " << pointsOverlap << '\n';

		myfile.close();
	}

	else cout << "Unable to open file";

}
