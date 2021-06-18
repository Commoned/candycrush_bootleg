#include "Steuerung.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>

using std::string;
using std::vector;

Steuerung::Steuerung()
{	
	// 
	score = 0;
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			createBubble(x,y,"");
		}
	}
}

/// <summary>
/// Creates new Bubbles
/// </summary>
/// <param name="x"> x-coordinate</param>
/// <param name="y">y- coordinate </param>
/// <param name="color">color of the bubble (only needed for special bubbles)</param>
void Steuerung::createBubble(int x, int y, string color)
{
	if (color == "") {									//to allow for deleted bubbles / empty spaces on field
		color = colors[rand() % 4];
	}
	if (rand() % 100 <= 3|| color == "purple") {		//5% Chance eine Special Bubble zu erstellen
		bubs[x][y] = new Special(x, y, "purple",rand()% 3+1);
	}
	else {												//creates simple bubble
		bubs[x][y] = new Bubble(x, y, color);
	}
}
/// <summary>
/// Updates Field
/// return value determines if the field has remaining combinations
/// </summary>
bool Steuerung::update()
{
	analyze();

	// Sucht bubbles die wegfallen und faerbt sie weiss
	for (int y = 11; y >= 0; y--)
	{
		for (int x = 0; x < 12; x++)
		{
			Bubble* current = static_cast<Bubble*>(bubs[x][y]);

			//Vectors for X- & Y- neighbours
			vector<void*> bubblesX = static_cast<Bubble*>(bubs[x][y])->getXneighbours();
			vector<void*> bubblesY = static_cast<Bubble*>(bubs[x][y])->getYneighbours();

			if (bubblesX.size() + bubblesY.size() >= 2 && (bubblesX.size()>=2 || bubblesY.size()>=2)) // Dreier Reihe (2 neighbours)
			{
				string currentcolor = static_cast<Bubble*>(bubs[x][y])->getcol();
				current->setcol("white");

				if (bubblesX.size() == 3 && bubblesY.size() == 0 && static_cast<Bubble*>(bubs[x][y])->getwasmoved()) // 3 neighbours (4 bubbles of same color)
				{
					delete static_cast<Bubble*>(bubs[x][y]);
					createBubble(x, y, "purple"); // Create special bubble
					static_cast<Special*>(bubs[x][y])->setability(lineH);
				}
				if (bubblesY.size() == 3 && bubblesX.size() == 0 && static_cast<Bubble*>(bubs[x][y])->getwasmoved())// 3 neighbours (4 bubbles of same color)
				{
					delete static_cast<Bubble*>(bubs[x][y]);
					createBubble(x, y, "purple"); // Create special bubble
					static_cast<Special*>(bubs[x][y])->setability(lineV);
				}
				if (bubblesX.size() == 4 && bubblesY.size() == 0 && static_cast<Bubble*>(bubs[x][y])->getwasmoved()) //4 neighbours (5 bubbles of same color)
				{
					delete static_cast<Bubble*>(bubs[x][y]);
					createBubble(x, y, "purple"); // Create special bubble
					static_cast<Special*>(bubs[x][y])->setability(colorbomb);
					static_cast<Special*>(bubs[x][y])->setprevcolor(currentcolor);
				}
				if (bubblesY.size() == 4 && bubblesX.size() == 0 && static_cast<Bubble*>(bubs[x][y])->getwasmoved()) //4 neighbours (5 bubbles of same color)
				{
					delete static_cast<Bubble*>(bubs[x][y]);
					createBubble(x, y, "purple"); // Create special bubble
					static_cast<Special*>(bubs[x][y])->setability(colorbomb);
					static_cast<Special*>(bubs[x][y])->setprevcolor(currentcolor);
				}
				if (bubblesY.size() > 0 && bubblesX.size() > 0 && bubblesX.size() + bubblesY.size() > 2 && static_cast<Bubble*>(bubs[x][y])->getwasmoved()) // Cross of Bubbles with more than 2 bubbles in x and y direction
				{
					delete static_cast<Bubble*>(bubs[x][y]);
					createBubble(x, y, "purple"); // Create special bubble
					static_cast<Special*>(bubs[x][y])->setability(bomb);
				}
				
				static_cast<Bubble*>(bubs[x][y])->setwasmoved(false);

				score++;
			}
		}
	}

	feld.drawField(bubs,score);

	//Drops Bubbles
	for(int x=0; x<12;x++)
	{
		fall(x);
		
		while (static_cast<Bubble*>(bubs[x][0])->getcol() == "white")
		{
			delete static_cast<Bubble*>(bubs[x][0]);
			createBubble(x, 0,"");
			fall(x);
			feld.drawField(bubs, score);
		}
	}
	
	analyze();

	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			if (static_cast<Bubble*>(bubs[x][y])->getcol() == "white" || static_cast<Bubble*>(bubs[x][y])->getneighbours() >= 3)
			{ 
				return false; 
			}
		}
	}
	return true;
}

/// <summary>
/// Checks if input results in a possible combination
/// </summary>
/// <param name="x"> x-cordinate of bubble </param>
/// <param name="y"> y-cordinate of bubble </param>
/// <param name="direction">Direction of move</param>
/// <returns></returns>
int Steuerung::checkValidInput(int x, int y, char direction)
{
	int xInput = x;
	int xMove = 0;
	int yInput = y;
	int yMove = 0;

	//Fill up comparisonArray with bubblecolors
	string tempColor = "";
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			compArray[x][y] = (static_cast<Bubble*>(bubs[x][y])->getcol());
		}
	}

	//Check if input vars are in field
	if (x < 0 || y < 0 || x > 11 || y > 11) {
		return 0;
	}

	//Check if bubble would move out of array
	//ELSE IFs makes move in comparison array
	if (x == 0 && (direction == 'l' || direction == 'L')) {
		return 0;
	}
	else if (x != 0 && (direction == 'l' || direction == 'L')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x - 1][y];
		compArray[x - 1][y] = tempColor;
		xMove = x - 1;
	}
	if (x == 11 && (direction == 'r' || direction == 'R')) {
		return 0;
	}
	else if (x != 11 && (direction == 'r' || direction == 'R')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x + 1][y];
		compArray[x + 1][y] = tempColor;
		xMove = x + 1;
	}
	if (y == 0 && (direction == 'u' || direction == 'U')) {
		return 0;
	}
	else if (y != 0 && (direction == 'u' || direction == 'U')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x][y - 1];
		compArray[x][y - 1] = tempColor;
		yMove = y - 1;
	}
	if (y == 11 && (direction == 'd' || direction == 'D')) {
		return 0;
	}
	else if (y != 11 && (direction == 'd' || direction == 'D')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x][y + 1];
		compArray[x][y + 1] = tempColor;
		yMove = y + 1;
	}

	//Check Functions
	//Check Row
	if (checkRow(yInput) || checkRow(yMove)) {
		return 1;
	}


	//Check Column
	if (checkColumn(xInput) || checkColumn(xMove)) {
		return 1;
	}

	return 0;
}

/// <summary>
/// Makes move that was specified
/// </summary>
/// <param name="x"> x-cordinate of bubble </param>
/// <param name="y"> y-cordinate of bubble </param>
/// <param name="input"> Direction of move </param>
/// <returns></returns>
bool Steuerung::makemove(int x, int y, char input)
{
	void* temp;
	if (static_cast<Bubble*>(bubs[x][y])->getcol() == "purple")
	{
		int ability = static_cast<Special*>(bubs[x][y])->getability();
		int isside = 1;
		switch (ability)
		{
		case bomb:
			static_cast<Bubble*>(bubs[x][y])->setcol("white");
			if (x - 1 < 0) { isside = 0; }
			static_cast<Bubble*>(bubs[x - isside][y])->setcol("white");
			isside = 1;
			if (x + 1 == 12) { isside = 0; }
			static_cast<Bubble*>(bubs[x + isside][y])->setcol("white");
			isside = 1;
			if (y + 1 == 12) { isside = 0; }
			static_cast<Bubble*>(bubs[x][y + isside])->setcol("white");
			isside = 1;
			if (x + 1 == 12 || y + 1 == 12) { isside = 0; }
			static_cast<Bubble*>(bubs[x + isside][y + isside])->setcol("white");
			isside = 1;
			if (x - 1 < 0 || y + 1 == 12) { isside = 0; }
			static_cast<Bubble*>(bubs[x - isside][y + isside])->setcol("white");
			isside = 1;
			if (y - 1 < 0) { isside = 0; }
			static_cast<Bubble*>(bubs[x][y - isside])->setcol("white");
			isside = 1;
			if (x + 1 == 12 || y - 1 < 0) { isside = 0; }
			static_cast<Bubble*>(bubs[x + isside][y - isside])->setcol("white");
			isside = 1;
			if (x - 1 < 0 || y - 1 < 0) { isside = 0; }
			static_cast<Bubble*>(bubs[x - isside][y - isside])->setcol("white");
			break;
		case lineH: // zeile 
			for (int forx = 0; forx < 12; forx++) {
				static_cast<Bubble*>(bubs[forx][y])->setcol("white");
			}
			break;
		case lineV: // spalte
			for (int fory = 0; fory < 12; fory++) {
				static_cast<Bubble*>(bubs[x][fory])->setcol("white");
			}
			break;
		case colorbomb:
			for (int fory = 0; fory < 12; fory++)
			{
				for (int forx = 0; forx < 12; forx++)
				{
					if (static_cast<Bubble*>(bubs[forx][fory])->getcol() == static_cast<Special*>(bubs[x][y])->getprevcolor())
					{
						static_cast<Bubble*>(bubs[forx][fory])->setcol("white");
						static_cast<Bubble*>(bubs[x][y])->setcol("white");
					}
				}
			}
			break;
		default:
			break;
		}
		return true;
	}
	else {
		switch (input) // Checks if input is valid
		{
		case 'L':
		case 'l':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x - 1][y];
			bubs[x - 1][y] = temp;
			static_cast<Bubble*>(bubs[x][y])->setwasmoved(true);
			static_cast<Bubble*>(bubs[x - 1][y])->setwasmoved(true);
			break;
		case 'r':
		case 'R':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x + 1][y];
			bubs[x + 1][y] = temp;
			static_cast<Bubble*>(bubs[x][y])->setwasmoved(true);
			static_cast<Bubble*>(bubs[x + 1][y])->setwasmoved(true);
			break;
		case 'u':
		case 'U':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x][y - 1];
			bubs[x][y - 1] = temp;
			static_cast<Bubble*>(bubs[x][y])->setwasmoved(true);
			static_cast<Bubble*>(bubs[x][y - 1])->setwasmoved(true);
			break;
		case 'd':
		case 'D':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x][y + 1];
			bubs[x][y + 1] = temp;
			static_cast<Bubble*>(bubs[x][y])->setwasmoved(true);
			static_cast<Bubble*>(bubs[x][y + 1])->setwasmoved(true);
			break;
		default:
			break;
		}
		return true;
	}
}
/// <summary>
/// Analizes field for combinations of Bubbles with the same color
/// </summary>
void Steuerung::analyze()
{
	int reihe=0;
	vector<void*> neighboursX;
	vector<void*> neighboursY;
	int z = 1;
	
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			reihe = 1; 
			neighboursX.clear();
			neighboursY.clear();
			if (x != 11)
			{
				z = check_neighbour(x, y, x + 1, y);
				reihe = reihe + z; // nach rechts
				
				while (z > 0)
				{
					neighboursX.push_back(bubs[x+z][y]);
					z--;
				}
				z = 0;
			}
			
			if (x != 0)
			{
				z = check_neighbour(x, y, x - 1, y);
				reihe = reihe + z; // nach links

				while (z > 0)
				{
					neighboursX.push_back(bubs[x - z][y]);
					z--;
				}
				z = 0;
			}
			if (reihe == 2)// to stop corners with each 1 neighbour from being deleted
			{
				reihe = 1;
			}
			if (y != 11)
			{
				z = check_neighbour(x, y, x, y + 1);
				reihe = reihe + z; // nach unten
				
				while (z > 0)
				{
					neighboursY.push_back(bubs[x][y+z]);
					z--;
				}
				z = 0;
			}
			if (y != 0)
			{
				z = check_neighbour(x, y, x, y - 1);
				reihe = reihe + z; // nach nach oben

				while (z > 0)
				{
					neighboursY.push_back(bubs[x][y - z]);
					z--;
				}
				z = 0;
			}
			static_cast<Bubble*>(bubs[x][y])->setneighbours(reihe,neighboursX,neighboursY);
		}
	}
}

/// <summary>
/// Checks neighbours for same color
/// </summary>
/// <param name="xcur">current Bubble x-coordinate </param>
/// <param name="ycur">current Bubble y-coordinate </param>
/// <param name="xcheck">x-coordinate to check </param>
/// <param name="ycheck">y-coordinate to check </param>
/// <returns></returns>
int Steuerung::check_neighbour(int xcur, int ycur, int xcheck, int ycheck)
{
	int newcheckx = xcheck - xcur;
	int newchecky = ycheck - ycur;
	
	if (static_cast<Bubble*>(bubs[xcur][ycur])->getcol() == static_cast<Bubble*>(bubs[xcheck][ycheck])->getcol() ){
		if (xcheck + newcheckx <12 && ycheck + newchecky<12 && xcheck + newcheckx >= 0 && ycheck + newchecky >= 0)
		{

			return 1 + check_neighbour(xcheck, ycheck, xcheck + newcheckx, ycheck + newchecky);

		}
		if (xcheck + newcheckx == -1 || ycheck + newchecky == -1)
		{
			return 1;
		}
		if (xcheck + newcheckx == 12 || ycheck + newchecky == 12)
		{
			return 1;
		}
	}
	return 0;
}
/// <summary>
/// lets bubbles fall
/// </summary>
/// <param name="col">column where Bubbles should fall</param>
void Steuerung::fall(int col)
{
	void* temp;
	for (int f = 0; f < 12; f++)
	{
		for (int y = 10; y >= 0; y--) {
			if (static_cast<Bubble*>(bubs[col][y])->getcol() != "white")
			{
				if (static_cast<Bubble*>(bubs[col][y + 1])->getcol() == "white")
				{

					temp = bubs[col][y+1];
					bubs[col][y+1] = bubs[col][y];
					bubs[col][y] = temp;

				}
			}
		}	
	}

}

bool Steuerung::checkRow(int y) {
	string tempColorKepper = compArray[0][y];				//Set initial Color from Row
	int rowCounter = 0;										//Set initial Rowcounters
	int maxRowCounter = 0;
	for (int x = 1; x < 12; x++)
	{
		if (tempColorKepper == compArray[x][y]) {			//If Purple should be included  "|| compArray[x][y] == "purple""
			rowCounter++;
		}
		if (tempColorKepper != compArray[x][y]) {
			if (rowCounter > maxRowCounter) {
				maxRowCounter = rowCounter;
				rowCounter = 1;
			}
			tempColorKepper = compArray[x][y];				//Change tempColorKeeper to move on
		}
	}
	if (maxRowCounter >= 3) {
		maxRowCounter = 0;
		rowCounter = 0;
		return true;
	}
	else {
		return false;
	}
}

bool Steuerung::checkColumn(int x) {
	string tempColorKepper = compArray[x][0];				//Set initial Color from Row
	int columnCounter = 0;									//Set initial Columncounters
	int maxColumnCounter = 0;
	for (int y = 1; y < 12; y++)
	{
		if (tempColorKepper == compArray[x][y] ) {			//If purple should be included "|| compArray[x][y] == "purple""
			columnCounter++;
		}
		if (tempColorKepper != compArray[x][y]) {
			if (columnCounter > maxColumnCounter) {
				maxColumnCounter = columnCounter;
				columnCounter = 1;
			}
			tempColorKepper = compArray[x][y];				//Change tempColorKeeper to move on
		}
	}
	if (maxColumnCounter >= 3) {
		maxColumnCounter = 0;
		columnCounter = 0;
		return true;
	}
	else {
		return false;
	}
}

//getter and setter
void Steuerung::setscore(int s)
{
	score = s;
}