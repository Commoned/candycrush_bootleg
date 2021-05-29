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