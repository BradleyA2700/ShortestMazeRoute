// QuickestRoute.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Can be run in CMD using the first arg as the file name or will request a file name if none is given
Code takes a text document in the format of . for space x for wall A for start point and B for end point
Code uses a form of Bredeth first search by adding ajacent unsearched points to a que and looping threw
each one adding there adjacent points and marking them as searched,
At the end of finding a path it will loop back to find the path that was taken and will reverse it to show to the user
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int columns;
int rows;
vector<vector<char>> mapVector;
vector<int> destination{-1,-1};
queue<vector<int>> que;
bool foundEnd = false;
string finalPath;

struct PathFind
{
	char character;
	vector<int> pos{0,0};
};

PathFind pathFind;

void OpenFile(string fileName);
void GetNeighbors(vector<int> currentPlace);
void MakePath();

int main(int argc,char* argv[])
{
	string fileName;
	//Take in cmd args and check for file
	if (argc > 1) 
	{
		fileName = argv[1];
	}
	else 
	{
		cout << "What is the name of the text file of the maze?" << endl;
		cin >> fileName;
	}
	OpenFile(fileName);
	//error handling for no exit found
	if (destination[0] == -1) 
	{
		foundEnd = true;
		pathFind.character = 'K';
		cout << "No exit in file" << endl;
	}
	//error handling for no start found
	if (que.empty()) 
	{
		foundEnd = true;
		pathFind.character = 'K';
		cout << "No start in file" << endl;
	}
	//Core loop;
	while (!foundEnd)
	{
		//Continues as long as there are more nodes to find and manages errors when no exit is found
		if (que.empty())
		{
			cout << "No path to exit found" << endl;
			foundEnd = true;
			pathFind.character = 'K';
		}
		else {
			GetNeighbors(que.front());
		}
	}
	//Generates path and outputs if path was found
	if (pathFind.character != 'K')
	{
		MakePath();
		reverse(finalPath.begin(), finalPath.end());
		cout << "Shortest path to the exit is: " << finalPath << endl;
		cin >> rows;
	}
}

//Core function to convert the text document to readable for the project
void OpenFile(string fileName) {
	ifstream mazeFile;
	string finalLine;
	//checks for if the .txt extention is already given if not applies it itself
	if (fileName.at(fileName.length()-4) == '.') {
		mazeFile.open(fileName);
	}
	else {
		mazeFile.open(fileName + ".txt");
	}
	//Error handling for when no file can be found
	if (mazeFile.fail()) { cout << "Could not find file" << endl; }
	//loops threw each line in the text docunment
	while (!mazeFile.eof()) {
		mazeFile >> finalLine;
		rows++;
	}
	//set up for the size of the vector to store the map
	columns = finalLine.length();
	mapVector.resize(rows);
	int i = 0;
	//resets the place being checked in the document
	mazeFile.clear();
	mazeFile.seekg(0);
	while (!mazeFile.eof()) {
		mazeFile >> finalLine;
		mapVector[i] = vector<char>(columns);
		for (int x = 0; x < columns; x++)
		{
			mapVector[i][x] = finalLine[x];
			//sets the start position when the start is found
			if (finalLine[x] == 'A') {
				vector<int> startPos = { x,i };
				que.push(startPos);
			}
			//sets the destination when the destination is found
			if (finalLine[x] == 'B') {
				destination[0] = x;
				destination[1] = i;
			}
		}
		i++;
	}
	mazeFile.close();
}
void GetNeighbors(vector<int> currentPlace)
{
	//removes the curent node from the que
	que.pop();
	int i = 0;
	//loops threw each direction to find child nodes
	while (i < 4) 
	{
		vector<int> tempVector{ 0,0 };
		tempVector = currentPlace;
		switch (i)
		{
		case 0:
			if (currentPlace[1] != -(rows-1)) {
				tempVector[1] -= 1;
				if (mapVector[tempVector[1]][tempVector[0]] == '.')
				{
					//adds the next node to the que
					que.push(tempVector);
					mapVector[tempVector[1]][tempVector[0]] = 'N';
				}
				else if (mapVector[tempVector[1]][tempVector[0]] == 'B')
				{
					//handles when the exit has been found
					pathFind.character = 'N';
					pathFind.pos = tempVector;
					foundEnd = true;
					i = 10;
				}
			}
			break;
		case 1:
			if (currentPlace[0] != columns-1) {
				tempVector[0] += 1;
				if (mapVector[tempVector[1]][tempVector[0]] == '.')
				{
					que.push(tempVector);
					mapVector[tempVector[1]][tempVector[0]] = 'E';
				}
				else if (mapVector[tempVector[1]][tempVector[0]] == 'B')
				{
					pathFind.character = 'E';
					pathFind.pos = tempVector;
					foundEnd = true;
					i = 10;
				}
			}
			break;
		case 2:
			if (currentPlace[1] != 0) {
				tempVector[1] += 1;
				if (mapVector[tempVector[1]][tempVector[0]] == '.')
				{
					que.push(tempVector);
					mapVector[tempVector[1]][tempVector[0]] = 'S';
				}
				else if (mapVector[tempVector[1]][tempVector[0]] == 'B')
				{
					pathFind.character = 'S';
					pathFind.pos = tempVector;
					foundEnd = true;
					i = 10;
				}
			}
			break;
		case 3:
			if (currentPlace[0] != 0) {
				tempVector[0] -= 1;
				if (mapVector[tempVector[1]][tempVector[0]] == '.')
				{
					que.push(tempVector);
					mapVector[tempVector[1]][tempVector[0]] = 'W';
				}
				else if (mapVector[tempVector[1]][tempVector[0]] == 'B')
				{
					pathFind.character = 'W';
					pathFind.pos = tempVector;
					foundEnd = true;
					i = 10;
				}
			}
			break;
		default:
			break;
		}
		i++;
	}
}

//function to create the final shortest path text given (reversed)
void MakePath() {
	finalPath.append(&pathFind.character);
	switch (pathFind.character)
	{
	case 'N':
		pathFind.pos[1] += 1;
		pathFind.character = mapVector[pathFind.pos[1]][pathFind.pos[0]];
		if (pathFind.character != 'A')
		{
			MakePath();
		}
		break;
	case 'E':
		pathFind.pos[0] -= 1;
		pathFind.character = mapVector[pathFind.pos[1]][pathFind.pos[0]];
		if (pathFind.character != 'A')
		{
			MakePath();
		}
		break;
	case 'S':
		pathFind.pos[1] -= 1;
		pathFind.character = mapVector[pathFind.pos[1]][pathFind.pos[0]];
		if (pathFind.character != 'A')
		{
			MakePath();
		}
		break;
	case 'W':
		pathFind.pos[0] += 1;
		pathFind.character = mapVector[pathFind.pos[1]][pathFind.pos[0]];
		if (pathFind.character != 'A') 
		{
			MakePath();
		}
		break;
	default:
		break;
	}
}
/*
Instead of having the project save the path for each thread I decided that by after finding the path looping backward I would
be able to save on both the time it takes to do everything as well as the memory being saved as I would not need to save a string for each
possible thread just to remove them.
*/