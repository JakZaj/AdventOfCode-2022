#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <queue>
#include <map>

using namespace std;

typedef pair<int, int> Node;

int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

bool isValid(Node pt, map<Node, int> visited, int x, int y)
{
	return (pt.first >= 0) && (pt.first < x) &&
		(pt.second >= 0) && (pt.second < y) && !visited.count(pt);
}

int findPathPartOne(vector<vector<char>> const& mat, int x, int y)
{
	int matY = mat.size();
	int matX = mat[0].size();

	if (matY == 0 || matX == 0) {
		return -1;
	}

	queue<Node> q;
	Node src = { x, y };
	q.push(src);

	map<Node, int> visited;
	visited[src] = 0;
	
	while (!q.empty())
	{
		Node node = q.front();
		q.pop();

		int i = node.first;
		int j = node.second;
		int dist = visited[node];

		if (mat[j][i] == 'E') {

			return dist;
		}

		for (int k = 0; k < 4; k++)
		{
			Node next = { (i + row[k]), (j + col[k]) };

			if (isValid(next, visited, matX, matY))
			{

				if (mat[j][i] != 'z' && mat[next.second][next.first] == 'E') {
					continue;
				}

				if (mat[j][i] == 'S' && mat[next.second][next.first] == 'a') {
					q.push(next);
					visited[next] = dist + 1;
					continue;
				}

				if (mat[next.second][next.first] - mat[j][i] <= 1 ) {
					q.push(next);
					visited[next] = dist + 1;
				}
				
			}
		}
	}
	return -1;
}

int findPathPartTwo(vector<vector<char>> const& mat, int x, int y)
{
	int matY = mat.size();
	int matX = mat[0].size();

	if (matY == 0 || matX == 0) {
		return -1;
	}

	queue<Node> q;
	Node src = { x, y };
	q.push(src);

	map<Node, int> visited;
	visited[src] = 0;
	int i;
	int j;
	while (!q.empty())
	{
		Node node = q.front();
		q.pop();

		i = node.first;
		j = node.second;
		int dist = visited[node];

		for (int k = 0; k < 4; k++)
		{
			Node next = { (i + row[k]), (j + col[k]) };

			if (isValid(next, visited, matX, matY))
			{

				if (mat[j][i] == 'E' && mat[next.second][next.first] != 'z') {
					continue;
				}

				if ((mat[next.second][next.first] - mat[j][i] >= -1) || mat[j][i] == 'E') {
					q.push(next);
					visited[next] = dist + 1;
				}



			}
			else if(mat[j][i] == 'a' || mat[j][i] == 'S') {
				return dist;
			}
		}
	}
	return -1;
}

int findS(vector<vector<char>> const& mat) {
	for (int i = 0; i < mat.size(); i++)
		if (mat[i][0] == 'S')
			return i;

	return 0;
}

int main()
{
	ifstream myfile("input.txt");

	string line;

	string lineToken;

	int eCharPosX = 0;
	int eCharPosY = 0;

	if (myfile.is_open())
	{
		

		vector<vector<char>> matrix;
		while (getline(myfile, line)) {
			vector<char> row;
			matrix.push_back(row);
			for (int x = 0; x < line.length(); x++) {
				
				char c = line.at(x);
				
				if (c == 'E') {
					eCharPosX = x;
					eCharPosY = matrix.size() - 1;
				}

				matrix[matrix.size()-1].push_back(c);
			}
			
		}

		myfile.close();
		myfile.clear();

		int lenPartOne = findPathPartOne(matrix, 0, findS(matrix));
		cout << "Part One Fewest path reaches " << lenPartOne << " steps" << endl;

		int lenPartTwo = findPathPartTwo(matrix, eCharPosX, eCharPosY);
		cout << "Part Two Fewest path reaches " << lenPartTwo << " steps" << endl;
		
	}

	else cout << "Unable to open file";

	return 0;
}

