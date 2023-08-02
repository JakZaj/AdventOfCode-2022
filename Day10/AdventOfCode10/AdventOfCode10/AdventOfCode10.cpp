#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum InstructionName { NONE, NOOP, ADDX };

struct INSTRUCTION {
	InstructionName instructionName = NONE;
	int addToX = 0;
	int cyclesRequirement = 0;
};


int main()
{
	ifstream myfile("input.txt");

	string line;

	string instructionName;
	string instructionParameter;
	string image[6];

	INSTRUCTION instrutrion;

	int imageRow = 0;

	int cycles = 0;
	int x = 1;
	int signalStrengths = 0;

	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 40; i++) {
			image[k].push_back('.');
		}
	}

	if (myfile.is_open())
	{

		while (getline(myfile, line)) {
			istringstream iss(line);

			iss >> instructionName;
			if (instructionName == "noop") {
				instrutrion.instructionName = NOOP;
			}
			else if (instructionName == "addx") {
				instrutrion.instructionName = ADDX;
			}
			else {
				cout << "File is corrupted";
				break;
			}

			if (instrutrion.instructionName == ADDX) {
				iss >> instructionParameter;
				instrutrion.addToX = stoi(instructionParameter);
				instrutrion.cyclesRequirement = 2;
			}
			else {
				instrutrion.cyclesRequirement = 1;
			}

			for (int i = 0; i < instrutrion.cyclesRequirement; ) {

				cycles++;
				instrutrion.cyclesRequirement--;

				int currPixel = cycles % 40;
				if (currPixel == x || currPixel == x + 1 || currPixel == x + 2) {
					image[imageRow].at(currPixel - 1) = '#';
				}

				if (cycles % 40 == 0) {
					imageRow++;
				}

				if ((cycles - 20) % 40 == 0) {
					signalStrengths += cycles * x;
				}

				if (instrutrion.instructionName == ADDX && instrutrion.cyclesRequirement == 0)
					x += instrutrion.addToX;
			}
		}
		myfile.close();
		myfile.clear();

		cout << "The sum of signal strengths is " << signalStrengths << endl;
		cout << endl;

		for (string s : image) {
			cout << s << endl;
		}
	}

	else cout << "Unable to open file";

	return 0;
}

