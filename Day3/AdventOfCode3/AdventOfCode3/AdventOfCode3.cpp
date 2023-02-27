#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main()
{
	string line, firstCompartment, secondCompartment, thirdCompartment;
	char tmpChar;

	ifstream myfile("input.txt");


	int points = 0;
	int counterOfLetter[52] = { 0 };

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			firstCompartment = line.substr(0, line.length() / 2);
			secondCompartment = line.substr(line.length() / 2);

			for (char& var : firstCompartment)
			{
				size_t ret = secondCompartment.find(var);
				if (ret != -1)
				{
					tmpChar = var;
					break;
				}
			}

			if (tmpChar >= 'a')
				counterOfLetter[tmpChar - 'a']++;
			else
				counterOfLetter[tmpChar - 'A' + 26]++;

		}

		for (int i = 0; i < 52; i++) {
			points += counterOfLetter[i] * (i + 1);
			counterOfLetter[i] = 0;
		}
		cout << points << '\n';

		myfile.clear();
		myfile.seekg(0, ios::beg);
		points = 0;

		while (getline(myfile, firstCompartment))
		{
			getline(myfile, secondCompartment);
			getline(myfile, thirdCompartment);


			for (char& var : firstCompartment)
			{
				size_t ret = secondCompartment.find(var);
				if (ret != -1)
				{
					ret = thirdCompartment.find(var);
					if (ret != -1)
					{
						tmpChar = var;
						break;
					}
				}
			}

			if (tmpChar >= 'a')
				counterOfLetter[tmpChar - 'a']++;
			else
				counterOfLetter[tmpChar - 'A' + 26]++;

		}

		for (int i = 0; i < 52; i++) {
			points += counterOfLetter[i] * (i + 1);
		}
		cout << points << '\n';

		myfile.close();
	}

	else cout << "Unable to open file";
}
