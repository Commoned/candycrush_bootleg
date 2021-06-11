#include "Steuerung.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>

using std::string;
using std::vector;

Steuerung::Steuerung()
{	
	score = 0;
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			createBubble(x,y,"");
		}
	}
}

// Creates Bubble with random Color from array
void Steuerung::createBubble(int x, int y, string color)
{
	if (color == "") // to allow for deleted bubbles / empty spaces on field
	{
		color = colors[rand() % 4];
	}
	if (rand() % 100 <= 5) // 3% Chance eine Special Bubble zu erstellen
	{
		bubs[x][y] = new Special(x, y, "purple",rand()% 3+1);
	}
	else
	{
		bubs[x][y] = new Bubble(x, y, color);
		
	}
}
/// <summary>
/// Updates Field
/// return wert bestimmt ob noch L�cher oder m�gliche kombinationen bestehen
/// </summary>
bool Steuerung::update()
{

	analyze();
	// Sucht bubbles die wegfallen und f�rbt sie wei�
	for (int y = 11; y >= 0; y--)
	{
		for (int x = 0; x < 12; x++)
		{
			
			//DEBUG
			
			vector<void*> bubl = static_cast<Bubble*>(bubs[x][y])->getactualneighbours();
			if (bubl.size() > 0)
			{
				std::cout << bubl.size()<< ':'<< static_cast<Bubble*>(bubs[x][y])->getneighbours() << "X:" << x << "  Y:" << y << std::endl;
			}

			//!DEBUG

			if (bubl.size() >= 2) // Dreier Reihe
			{
				static_cast<Bubble*>(bubs[x][y])->setcol("white");
				//Specialabilities
				int abil = static_cast<Special*>(bubs[x][y])->getability();
				int isside = 1;
				switch (abil)
				{
				case bomb: 
					if (x - 1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x- isside][y])->setcol("white");
					isside = 1;
					if (x + 1 == 12) { isside = 0; }
					static_cast<Bubble*>(bubs[x+ isside][y])->setcol("white");
					isside = 1;
					if (y + 1 == 12) { isside = 0; }
					static_cast<Bubble*>(bubs[x][y + isside])->setcol("white");
					isside = 1;
					if (x + 1 ==12 || y + 1 == 12) { isside = 0; }
					static_cast<Bubble*>(bubs[x + isside][y + isside])->setcol("white");
					isside = 1;
					if (x - 1 < 0 || y+1==12) { isside = 0; }
					static_cast<Bubble*>(bubs[x - isside][y + isside])->setcol("white");
					isside = 1;
					if (y - 1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x][y - isside])->setcol("white");
					isside = 1;
					if (x + 1 == 12 || y-1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x + isside][y - isside])->setcol("white");
					isside = 1;
					if (x - 1 < 0 || y - 1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x - isside][y - isside])->setcol("white");
					break;
				case lineH: // zeile 

					break;
				case lineV: // spalte

					break;
				case colorbomb:

					break;
				default:
					break;
				}
				score++;
			}
		}
	}
	feld.drawField(bubs,score);
	//L�sst Bubbles fallen
	for(int x=0; x<12;x++)
	{
		fall(x);
		while (static_cast<Bubble*>(bubs[x][0])->getcol() == "white")
		{
			createBubble(x,0,"");
			fall(x);
		}
	}
	
	feld.drawField(bubs,score);
	analyze();
	bool whites;
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

int Steuerung::checkValidInput(int x, int y, char direction)
{
	int xInput = x;
	int yInput = y;
	string compArray[12][12];
	string tempColor = "";
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			compArray[x][y] = (static_cast<Bubble*>(bubs[x][y])->getcol());
		}
	}

	//Check if input vars are in field
	if (x < 0 || y < 0) {
		return 0;
	}
	if (x > 11 || y > 11){
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
		xInput = x - 1;
	}
	if (x == 11 && (direction == 'r' || direction == 'R')) {
		return 0;
	}
	else if (x != 11 && (direction == 'r' || direction == 'R')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x + 1][y];
		compArray[x + 1][y] = tempColor;
		xInput = x + 1;
	}
	if (y == 0 && (direction == 'u' || direction == 'U')) {
		return 0;
	}
	else if (y != 0 && (direction == 'u' || direction == 'U')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x][y - 1];
		compArray[x][y - 1] = tempColor;
		yInput = y - 1;
	}
	if (y == 11 && (direction == 'd' || direction == 'D')) {
		return 0;
	}
	else if (y != 11 && (direction == 'd' || direction == 'D')) {
		tempColor = compArray[x][y];
		compArray[x][y] = compArray[x][y + 1];
		compArray[x][y + 1] = tempColor;
		yInput = y + 1;
	}

	//Check Functions
	string tempColorKepper;
	//Check Row
	tempColorKepper = compArray[0][yInput];
	int rowCounter = 1;
	int maxRowCounter = 0;
	for (int x = 1; x < 12; x++)
	{
		if (tempColorKepper == compArray[x][yInput] || compArray[xInput][y] == "purple") {
			rowCounter++;
		}
		if (tempColorKepper != compArray[x][yInput]) {
			if (rowCounter > maxRowCounter) {
				maxRowCounter = rowCounter;
				rowCounter = 1;
			}
			tempColorKepper = compArray[x][yInput];
		}
	}
	if (maxRowCounter >= 3) {
		maxRowCounter = 0;
		rowCounter = 1;
		return 1;
	}
	
	//Check Column
	tempColorKepper = compArray[xInput][0];
	int columnCounter = 1;
	int maxColumnCounter = 0;
	for (int y = 1; y < 12; y++)
	{
		if (tempColorKepper == compArray[xInput][y] || compArray[xInput][y] == "purple") {
			columnCounter++;
		}
		if (tempColorKepper != compArray[xInput][y]) {
			if (columnCounter > maxColumnCounter) {
				maxColumnCounter = columnCounter;
				columnCounter = 1;
			}
			tempColorKepper = compArray[xInput][y];
		}
	}
	if (maxColumnCounter >= 3) {
		maxColumnCounter = 0;
		columnCounter = 1;
		return 1;
	}

	return 0;
}

/// <summary>
/// Allows Input through player 
/// </summary>
/// <returns></returns>
bool Steuerung::makemove(int x, int y, char input)
{
	void* temp;
	switch (input) // Checks if input is valid
	{
	case 'L':
	case 'l':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x - 1][y];
			bubs[x - 1][y] = temp;
			break;
	case 'r':
	case 'R':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x + 1][y];
			bubs[x + 1][y] = temp;
		break;
	case 'u':
	case 'U':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x][y - 1];
			bubs[x][y - 1] = temp;
		break;
	case 'd':
	case 'D':
			temp = bubs[x][y];
			bubs[x][y] = bubs[x][y + 1];
			bubs[x][y + 1] = temp;
		break;
	default:
		break;
	}
	return true;
}

void Steuerung::analyze()
{
	int reihe=0;
	vector<void*> neighbours;
	int z = 1;
	
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			reihe = 1; 
			neighbours.clear();
			if (x != 11)
			{
				z = check_neighbour(x, y, x + 1, y);
				reihe = reihe + z; // nach rechts
				
				while (z > 0)
				{
					neighbours.push_back(bubs[x+z][y]);
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
					neighbours.push_back(bubs[x - z][y]);
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
					neighbours.push_back(bubs[x][y+z]);
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
					neighbours.push_back(bubs[x][y - z]);
					z--;
				}
				z = 0;
				
			}
			
			static_cast<Bubble*>(bubs[x][y])->setneighbours(reihe,neighbours);


			//std::cout << static_cast<Bubble*>(bubs[x][y])->getneighbours()<<';';
			//std::cout << x<< ';';
			//std::cout << y << '\n';
		}
	}
}
/// <summary>
/// �berpr�ft nachbarn auf gleiche Farbe
/// </summary>
/// <param name="xcur"></param>
/// <param name="ycur"></param>
/// <param name="xcheck"></param>
/// <param name="ycheck"></param>
/// <returns></returns>
int Steuerung::check_neighbour(int xcur,int ycur, int xcheck, int ycheck)
{
	
	int newcheckx = xcheck - xcur;
	int newchecky = ycheck - ycur;
	

	if (static_cast<Bubble*>(bubs[xcur][ycur])->getcol() == static_cast<Bubble*>(bubs[xcheck][ycheck])->getcol() || static_cast<Bubble*>(bubs[xcheck][ycheck])->getcol()== "purple" || static_cast<Bubble*>(bubs[xcur][ycur])->getcol() == "purple"){
		if (xcheck + newcheckx <12 && ycheck + newchecky<12 && xcheck + newcheckx >= 0 && ycheck + newchecky >= 0)
		{

			return 1 + check_neighbour(xcheck, ycheck, xcheck + newcheckx, ycheck + newchecky);

		}
		if(xcheck + newcheckx == -1 || ycheck + newchecky == -1)
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

//getter and setter

void Steuerung::setscore(int s)
{
	score = s;
}