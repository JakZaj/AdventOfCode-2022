#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum RockPaperScissors {
	ROCK = 1,
	PAPER = 2,
	SCISSORS = 3,
};

enum BattleResult {
	DEFEAT = 0,
	DRAW = 3,
	WIN = 6
};

int main()
{
	string line;
	ifstream myfile("input.txt");

	RockPaperScissors opponentChoos = ROCK, playerChoos = ROCK;

	int playerPoints = 0, playerPointsPartTwo = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.front() == 'A')
				opponentChoos = ROCK;
			else if (line.front() == 'B')
				opponentChoos = PAPER;
			else if (line.front() == 'C')
				opponentChoos = SCISSORS;

			if (line.back() == 'X')
			{
				playerChoos = ROCK;
				switch (opponentChoos) {
				case ROCK:
					playerPointsPartTwo += SCISSORS;
					break;
				case PAPER:
					playerPointsPartTwo += ROCK;
					break;
				case SCISSORS:
					playerPointsPartTwo += PAPER;
					break;
				};
			}
			else if (line.back() == 'Y')
			{
				playerChoos = PAPER;
				playerPointsPartTwo += opponentChoos + DRAW;
			}
			else if (line.back() == 'Z')
			{
				playerChoos = SCISSORS;
				switch (opponentChoos) {
				case ROCK:
					playerPointsPartTwo += PAPER + WIN;
					break;
				case PAPER:
					playerPointsPartTwo += SCISSORS + WIN;
					break;
				case SCISSORS:
					playerPointsPartTwo += ROCK + WIN;
					break;
				};
			}

			if (opponentChoos == playerChoos) {
				playerPoints += playerChoos + DRAW;
			}
			else if ((opponentChoos == ROCK || playerChoos == ROCK) && (opponentChoos == PAPER || playerChoos == PAPER)) {

				if (opponentChoos < playerChoos)
				{
					playerPoints += playerChoos + WIN;
				}
				else {
					playerPoints += playerChoos + DEFEAT;
				}
			}
			else if ((opponentChoos == ROCK || playerChoos == ROCK) && (opponentChoos == SCISSORS || playerChoos == SCISSORS)) {
				if (opponentChoos > playerChoos)
				{
					playerPoints += playerChoos + WIN;
				}
				else {
					playerPoints += playerChoos + DEFEAT;
				}
			}
			else if ((opponentChoos == PAPER || playerChoos == PAPER) && (opponentChoos == SCISSORS || playerChoos == SCISSORS)) {
				if (opponentChoos < playerChoos)
				{
					playerPoints += playerChoos + WIN;
				}
				else {
					playerPoints += playerChoos + DEFEAT;
				}
			}

		}
		myfile.close();

	}

	else cout << "Unable to open file";

	cout << playerPoints << ' ' << playerPointsPartTwo << '\n';
}