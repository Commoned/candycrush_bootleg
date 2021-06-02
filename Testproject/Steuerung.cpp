#include "Steuerung.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>

using std::string;

Steuerung::Steuerung()
{	
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
	if (color == "") // to allow for deleted bubbles
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
/// return wert bestimmt ob noch Löcher oder mögliche kombinationen bestehen
/// </summary>
bool Steuerung::update()
{

	analyze();
	// Sucht bubbles die wegfallen und färbt sie weiß
	for (int y = 11; y >= 0; y--)
	{
		for (int x = 0; x < 12; x++)
		{
			if (static_cast<Bubble*>(bubs[x][y])->getneighbours() >= 3) // Dreier Reihe
			{
				static_cast<Bubble*>(bubs[x][y])->setcol("white");
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
					if (x + 1 == 12 && y-1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x + isside][y - isside])->setcol("white");
					isside = 1;
					if (x - 1 < 0 || y - 1 < 0) { isside = 0; }
					static_cast<Bubble*>(bubs[x - isside][y - isside])->setcol("white");
					break;
				case line:

					break;
				case colorbomb:
					break;
				default:
					break;
				}
			}
		}
	}
	feld.drawField(bubs);
	//Lässt Bubbles fallen
	for(int x=0; x<12;x++)
	{
		fall(x);
		while (static_cast<Bubble*>(bubs[x][0])->getcol() == "white")
		{
			createBubble(x,0,"");
			fall(x);
		}
	}
	
	feld.drawField(bubs);
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

/// <summary>
/// Allows Input through player 
/// </summary>
/// <returns></returns>
bool Steuerung::makemove()
{

	int x;
	int y;
	char input;
	input = 'I';
	std::cout << "X Variable 1 eingeben!";
	std::cin >> x;
	
	std::cout << "Y Variable 1 eingeben!";
	std::cin >> y;
	
	//std::cout << bubs[x][y].getability();
	
	while (input == 'I') {
		std::cout << "Where to move bubble? (L=left;R=right;U=up;D=down)";

		std::cin >> input;

		void* temp;
		
			switch (input) // Checks if input is valid
			{
			case 'L':
				if (x == 0)
				{
					std::cout << "Move not available!" << '\n';
					input = 'I';
				}
				else {
					temp = bubs[x][y];
					bubs[x][y] = bubs[x - 1][y];
					bubs[x - 1][y] = temp;
				}
					break;

			case 'R':
				if (x == 11)
				{
					std::cout << "Move not available!" << '\n';
					input = 'I';
				}
				else {
					temp = bubs[x][y];
					bubs[x][y] = bubs[x + 1][y];
					bubs[x + 1][y] = temp;
				}
				break;
			case 'U':
				if (y == 0)
				{
					std::cout << "Move not available!" << '\n';
					input = 'I';
				}
				else
				{
					temp = bubs[x][y];
					bubs[x][y] = bubs[x][y - 1];
					bubs[x][y - 1] = temp;
				}
				break;
			case 'D':
				if (y == 11)
				{
					std::cout << "Move not available!" << '\n';
					input = 'I';
				}
				else
				{
					temp = bubs[x][y];
					bubs[x][y] = bubs[x][y + 1];
					bubs[x][y + 1] = temp;
				}
				break;
			default:
				input = 'I';
				std::cout << "Invalid Input!" << '\n';
				break;
			}
			
	}

	return true;
}

void Steuerung::analyze()
{
	int reihe=0;
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			reihe = 1; 
			
			if (x != 11)
			{
				
				reihe = reihe + check_neighbour(x, y, x + 1, y); // nach rechts
				
			}
			//x = x + reihe;
			//std::cout << reihe;
			if (x != 0)
			{
				
				reihe = reihe + check_neighbour(x, y, x - 1, y); // nach links
				
			}
			if (reihe == 2)// to stop coners with eac 1 neighbour from being deleted
			{
				reihe = 1;
			}
			if (y != 11)
			{
				
				reihe = reihe + check_neighbour(x, y, x, y + 1); // nach unten
				
			}
			if (y != 0)
			{
				
				reihe = reihe + check_neighbour(x, y, x, y - 1); // nach nach oben
				
			}
			
				static_cast<Bubble*>(bubs[x][y])->setneighbours(reihe);

			//std::cout << static_cast<Bubble*>(bubs[x][y])->getneighbours()<<';';
			//std::cout << x<< ';';
			//std::cout << y << '\n';
		}
	}
}
/// <summary>
/// Überprüft nachbarn auf gleiche Farbe
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
					//bubs[x][y+1] = bubs[x][y];
					//static_cast<Bubble*>(bubs[col][y + 1])->setcol(static_cast<Bubble*>(bubs[col][y])->getcol());
					temp = bubs[col][y+1];
					bubs[col][y+1] = bubs[col][y];
					bubs[col][y] = temp;
					//static_cast<Bubble*>(bubs[col][y])->setcol("white");
				}
			}
		}	
	}

}