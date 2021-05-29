#include "Feld.h"
#include <iostream>
#include <string>
#include <windows.h> 
#include "Special.h"
using std::string;

Feld::Feld()
{
}
/// <summary>
/// Draws the current field.
/// </summary>
/// <param name="bub"> gets the currrent Bubbles on the field.</param>
/// 

void Feld::drawField(void* bub[12][12])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Handler um Konsolentext umzuf�rben
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   
	cfi.dwFontSize.Y = 24;                  
	cfi.FontWeight = 1000;
	SetCurrentConsoleFontEx(hConsole,FALSE,&cfi);
	int k=0;
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{ //If abfragen um die Farbe der jeweiligen Bubble abzufragen
			if (static_cast<Bubble*>(bub[x][y])->getcol() == "blue")
			{
				k = 1;
			}
			if (static_cast<Bubble*>(bub[x][y])->getcol() == "green")
			{
				k = 2;
			}
			if (static_cast<Bubble*>(bub[x][y])->getcol() == "yellow")
			{
				k = 6;
			}
			if (static_cast<Bubble*>(bub[x][y])->getcol() == "red")
			{
				k = 4;
			}
			if (static_cast<Bubble*>(bub[x][y])->getcol() == "purple")
			{
				k = 5;
			}
			//Setzen der Farbe und Zeichnen des Platzhalter
			SetConsoleTextAttribute(hConsole, k);
			std::cout  << "#";
			std::cout << ' ';
			k = 15;
		}
		std::cout << "\n";
	}
	SetConsoleTextAttribute(hConsole, 15);
}
