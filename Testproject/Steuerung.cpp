#include "Steuerung.h"
#include <iostream>
#include <vector>
#include <random>


Steuerung::Steuerung()
{	
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			createBubble(x,y);
		}
	}
}

// Creates Bubble with random Color from array
void Steuerung::createBubble(int x, int y)
{
	if (rand() % 100 <= 3) // 3% Chance eine Special Bubble zu erstellen
	{
		bubs[x][y] = new Special(x, y, "purple","COOL");
	}
	else
	{
		bubs[x][y] = new Bubble(x, y, colors[rand() % 4]);
		
	}
}
/// <summary>
/// Updates Field
/// </summary>
void Steuerung::update()
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			if (static_cast<Bubble*>(bubs[x][y])->getneighbours() >= 3)
			{
				static_cast<Bubble*>(bubs[x][y])->setcol("black");
			}
		}
	}
	feld.drawField(bubs);
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
			update();
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
				if (reihe == 2)
				{
					reihe = 1;
				}
			}
			//x = x + reihe;
			//std::cout << reihe;
			if (x != 0)
			{
				reihe = reihe + check_neighbour(x, y, x-1, y); // nach links
				if (reihe == 2)
				{
					reihe = 1;
				}
			}
			if (y != 11)
			{
				reihe = reihe + check_neighbour(x, y, x, y + 1); // nach unten
				if (reihe == 2)
				{
					reihe = 1;
				}
			}
			if (y != 0)
			{
				reihe = reihe + check_neighbour(x, y, x, y - 1); // nach nach oben
				if (reihe == 2)
				{
					reihe = 1;
				}
			}

			static_cast<Bubble*>(bubs[x][y])->setneighbours(reihe);
			std::cout << static_cast<Bubble*>(bubs[x][y])->getneighbours()<<';';
			std::cout << x<< ';';
			std::cout << y << '\n';
		}
	}
}

int Steuerung::check_neighbour(int xcur,int ycur, int xcheck, int ycheck)
{
	int newcheckx = xcheck - xcur;
	int newchecky = ycheck - ycur;
	

	if (static_cast<Bubble*>(bubs[xcur][ycur])->getcol() == static_cast<Bubble*>(bubs[xcheck][ycheck])->getcol()){
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