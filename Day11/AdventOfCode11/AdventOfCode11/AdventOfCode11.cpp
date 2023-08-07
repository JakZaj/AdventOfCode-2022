#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "BigInt.hpp" 

using namespace std;

const int numberOfRounds = 20;
const int numberOfRoundsPartTwo = 10000;

const int boredDivided = 3;

struct ITEM {
	BigInt value;
	ITEM* nextItem = nullptr;
};

struct OPERATION {
	char operation;
	bool oldValue = false;
	BigInt number;
};

struct MONKEY {
	ITEM* itemsPartOne = nullptr;
	ITEM* itemsPartTwo = nullptr;
	OPERATION operation;
	BigInt testDivisible;
	int ifTrue;
	int ifFalse;
	int inspectedItems = 0;
};

BigInt doOperation(BigInt oldItemValue, OPERATION operation) {

	if (operation.oldValue) {
		operation.number = oldItemValue;
	}

	switch (operation.operation) {
	case '+': 
		return oldItemValue + operation.number;
	case '-': 
		return oldItemValue - operation.number;
	case '*':
		return oldItemValue * operation.number; 
	case '/':
		return oldItemValue / operation.number;
	default:
		return oldItemValue;
	}
}

void throwItemToMonkey(MONKEY* fromMonkey, MONKEY* toMonkey, bool partOne = true) {
	ITEM* ptrItem;
	
	if (partOne) {
		ptrItem = toMonkey->itemsPartOne;
		if (ptrItem == nullptr)
		{
			toMonkey->itemsPartOne = fromMonkey->itemsPartOne;
			fromMonkey->itemsPartOne = fromMonkey->itemsPartOne->nextItem;
			toMonkey->itemsPartOne->nextItem = nullptr;

			fromMonkey->inspectedItems++;
			return;
		}

		while (ptrItem->nextItem != nullptr) {
			ptrItem = ptrItem->nextItem;
		}

		ptrItem->nextItem = fromMonkey->itemsPartOne;
		fromMonkey->itemsPartOne = fromMonkey->itemsPartOne->nextItem;
		ptrItem->nextItem->nextItem = nullptr;
		fromMonkey->inspectedItems++;
	}
	else {
		ptrItem = toMonkey->itemsPartTwo;
		if (ptrItem == nullptr)
		{
			toMonkey->itemsPartTwo = fromMonkey->itemsPartTwo;
			fromMonkey->itemsPartTwo = fromMonkey->itemsPartTwo->nextItem;
			toMonkey->itemsPartTwo->nextItem = nullptr;

			fromMonkey->inspectedItems++;
			return;
		}

		while (ptrItem->nextItem != nullptr) {
			ptrItem = ptrItem->nextItem;
		}

		ptrItem->nextItem = fromMonkey->itemsPartTwo;
		fromMonkey->itemsPartTwo = fromMonkey->itemsPartTwo->nextItem;
		ptrItem->nextItem->nextItem = nullptr;
		fromMonkey->inspectedItems++;
	}
}

void throwItemToMonkeyPartTwo(MONKEY* fromMonkey, MONKEY* toMonkey) {
	ITEM* ptrItem;
	ptrItem = toMonkey->itemsPartTwo;
	if (ptrItem == nullptr)
	{
		toMonkey->itemsPartTwo = fromMonkey->itemsPartTwo;
		fromMonkey->itemsPartTwo = fromMonkey->itemsPartTwo->nextItem;
		toMonkey->itemsPartTwo->nextItem = nullptr;

		fromMonkey->inspectedItems++;
		return;
	}

	while (ptrItem->nextItem != nullptr) {
		ptrItem = ptrItem->nextItem;
	}

	ptrItem->nextItem = fromMonkey->itemsPartTwo;
	fromMonkey->itemsPartTwo = fromMonkey->itemsPartTwo->nextItem;
	ptrItem->nextItem->nextItem = nullptr;
	fromMonkey->inspectedItems++;
}

void findMostActiveMonkey(vector<MONKEY*> monkeysVector, BigInt* mostActiveOne, BigInt* mostActiveTwo) {
	
	if (monkeysVector.at(0)->inspectedItems > monkeysVector.at(1)->inspectedItems) {
		*mostActiveOne = monkeysVector.at(0)->inspectedItems;
		*mostActiveTwo = monkeysVector.at(1)->inspectedItems;
	}
	else {
		*mostActiveOne = monkeysVector.at(1)->inspectedItems;
		*mostActiveTwo = monkeysVector.at(0)->inspectedItems;
	}

	for (int k = 2; k < monkeysVector.size(); k++) {
		if (*mostActiveOne < monkeysVector.at(k)->inspectedItems) {
			*mostActiveTwo = *mostActiveOne;
			*mostActiveOne = monkeysVector.at(k)->inspectedItems;
			continue;
		}

		if (*mostActiveTwo < monkeysVector.at(k)->inspectedItems) {
			*mostActiveTwo = monkeysVector.at(k)->inspectedItems;
		}
	}
}

void clearMonkeyInspectedItems(vector<MONKEY*> monkeysVector) {
	for (int k = 0; k < monkeysVector.size(); k++) {
		monkeysVector.at(k)->inspectedItems = 0;
	}
}

void freeMonkeyStruct(vector<MONKEY*> monkeysVector) {
	for (int k = 0; k < monkeysVector.size(); k++) {

		ITEM* ptrItemNext = nullptr;
		ITEM* ptrItem = monkeysVector.at(k)->itemsPartOne;

		ITEM* ptrItemNextPartTwo = nullptr;
		ITEM* ptrItemPartTwo = monkeysVector.at(k)->itemsPartTwo;

		if (ptrItem != nullptr)
			ptrItemNext = ptrItem->nextItem;

		if (ptrItemPartTwo != nullptr)
			ptrItemNextPartTwo = ptrItemPartTwo->nextItem;


		while (ptrItem != nullptr)
		{
			delete ptrItem;
			ptrItem = ptrItemNext;

			if (ptrItemNext != nullptr) {
				ptrItemNext = ptrItemNext->nextItem;
			}
		}

		while (ptrItemPartTwo != nullptr)
		{
			delete ptrItemPartTwo;

			ptrItemPartTwo = ptrItemNextPartTwo;

			if (ptrItemNextPartTwo != nullptr) {
				ptrItemNextPartTwo = ptrItemNextPartTwo->nextItem;
			}
		}

		delete monkeysVector.at(k);

	}
}

BigInt commonMultiple(vector<MONKEY*> monkeysVector) {
	BigInt biggestNumber = 0;
	for (int k = 0; k < monkeysVector.size(); k++) {
		if (biggestNumber < monkeysVector.at(k)->testDivisible)
			biggestNumber = monkeysVector.at(k)->testDivisible;
	}
	bool endLoop = false;
	BigInt returnValue = 0;

	while (!endLoop) {
		returnValue += biggestNumber;
		endLoop = true;
		for (int k = 0; k < monkeysVector.size(); k++) {
			if (returnValue % monkeysVector.at(k)->testDivisible != 0) {
				endLoop = false;
				break;
			}
		}
	}

	return returnValue;
}

void doRounds(vector<MONKEY*> monkeysVector, int numberOfRounds, bool firstPart = true, BigInt modNumber = 0) {

	for (int i = 0; i < numberOfRounds; i++) {
		if (firstPart) {
			for (int k = 0; k < monkeysVector.size(); k++) {
				ITEM* ptrItem = monkeysVector.at(k)->itemsPartOne;
				while (ptrItem != nullptr)
				{
				
						ptrItem->value = doOperation(ptrItem->value, monkeysVector.at(k)->operation) / boredDivided;
				

					if (ptrItem->value % monkeysVector.at(k)->testDivisible == 0) {
						throwItemToMonkey(monkeysVector.at(k), monkeysVector.at(monkeysVector.at(k)->ifTrue));
					}
					else {
						throwItemToMonkey(monkeysVector.at(k), monkeysVector.at(monkeysVector.at(k)->ifFalse));
					}

					ptrItem = monkeysVector.at(k)->itemsPartOne;
				}
			}
		}
		else {
			for (int k = 0; k < monkeysVector.size(); k++) {
				ITEM* ptrItem = monkeysVector.at(k)->itemsPartTwo;
				while (ptrItem != nullptr)
				{

					ptrItem->value = doOperation(ptrItem->value, monkeysVector.at(k)->operation) % modNumber;


					if (ptrItem->value % monkeysVector.at(k)->testDivisible == 0) {
						throwItemToMonkey(monkeysVector.at(k), monkeysVector.at(monkeysVector.at(k)->ifTrue), false);
					}
					else {
						throwItemToMonkey(monkeysVector.at(k), monkeysVector.at(monkeysVector.at(k)->ifFalse), false);
					}

					ptrItem = monkeysVector.at(k)->itemsPartTwo;
				}
			}
		}



	}
}

int main()
{
	ifstream myfile("input.txt");

	string line;

	string lineToken;

	vector<MONKEY*> monkeysVector;

	int currentMonkey = -1;

	if (myfile.is_open())
	{

		while (getline(myfile, line)) {
			istringstream iss(line);

			iss >> lineToken;
			
			if (lineToken == "Monkey") {
				monkeysVector.push_back(new MONKEY);
				currentMonkey++;
				continue;
			}

			if (lineToken == "Starting") {
				iss >> lineToken;
				iss >> lineToken;

				ITEM* ptrItemHead = nullptr;
				ITEM* ptrItem = nullptr;

				ITEM* ptrItemHeadPartTwo = nullptr;
				ITEM* ptrItemPartTwo = nullptr;

				while (lineToken.find(",") != string::npos) {
					
					if (ptrItem == nullptr) {
						ptrItem = new ITEM;
						ptrItemPartTwo = new ITEM;

					}
					else {
						ptrItem->nextItem = new ITEM;
						ptrItem = ptrItem->nextItem;
						
						ptrItemPartTwo->nextItem = new ITEM;
						ptrItemPartTwo = ptrItemPartTwo->nextItem;
					}

					if (ptrItemHead == nullptr) {
						ptrItemHead = ptrItem;

						ptrItemHeadPartTwo = ptrItemPartTwo;
					}

					ptrItem->value = stoi(lineToken.substr(0, lineToken.length() - 1));
					
					ptrItemPartTwo->value = ptrItem->value;

					iss >> lineToken;
				}

				if (ptrItem == nullptr) {
					ptrItem = new ITEM;
					ptrItemHead = ptrItem;
					ptrItem->value = stoi(lineToken);

					ptrItemPartTwo = new ITEM;
					ptrItemHeadPartTwo = ptrItemPartTwo;
					ptrItemPartTwo->value = ptrItem->value;
				}
				else {
					ptrItem->nextItem = new ITEM;
					ptrItem = ptrItem->nextItem;
					ptrItem->value = stoi(lineToken);

					ptrItemPartTwo->nextItem = new ITEM;
					ptrItemPartTwo = ptrItemPartTwo->nextItem;
					ptrItemPartTwo->value = ptrItem->value;
				}

				monkeysVector.at(currentMonkey)->itemsPartOne = ptrItemHead;
				monkeysVector.at(currentMonkey)->itemsPartTwo = ptrItemHeadPartTwo;

				continue;
			}

			if (lineToken == "Operation:") {
				
				iss >> lineToken; // new
				iss >> lineToken; // =
				iss >> lineToken; // old
				iss >> lineToken;

				monkeysVector.at(currentMonkey)->operation.operation = lineToken.at(0);

				iss >> lineToken;

				if (lineToken == "old") {
					monkeysVector.at(currentMonkey)->operation.oldValue = true;
					continue;
				}
				monkeysVector.at(currentMonkey)->operation.number = stoi(lineToken);
				continue;
			}

			if (lineToken == "Test:") {
				iss >> lineToken; // divisible 
				iss >> lineToken; // by
				iss >> lineToken; 

				monkeysVector.at(currentMonkey)->testDivisible = stoi(lineToken);
			}

			if (lineToken == "If") {
				iss >> lineToken;

				if (lineToken == "true:") {
					iss >> lineToken; // throw
					iss >> lineToken; // to
					iss >> lineToken; // monkey
					iss >> lineToken;

					monkeysVector.at(currentMonkey)->ifTrue = stoi(lineToken);
				}
				if (lineToken == "false:") {
					iss >> lineToken; // throw
					iss >> lineToken; // to
					iss >> lineToken; // monkey
					iss >> lineToken;

					monkeysVector.at(currentMonkey)->ifFalse = stoi(lineToken);
				}
				
				continue;
			}

		}

		myfile.close();
		myfile.clear();

		doRounds(monkeysVector, numberOfRounds);

		BigInt mostActiveOne = 0;
		BigInt mostActiveTwo = 0;

		findMostActiveMonkey(monkeysVector, &mostActiveOne, &mostActiveTwo);
		clearMonkeyInspectedItems(monkeysVector);

		cout << "Monkey business " << mostActiveOne * mostActiveTwo << endl;

		mostActiveOne = 0;
		mostActiveTwo = 0;

		doRounds(monkeysVector, numberOfRoundsPartTwo, false, commonMultiple(monkeysVector));
		
		findMostActiveMonkey(monkeysVector, &mostActiveOne, &mostActiveTwo);

		cout << "Monkey business Part Two: " << mostActiveOne * mostActiveTwo << endl;

		freeMonkeyStruct(monkeysVector);
	}

	else cout << "Unable to open file";

	return 0;
}

