#include<iostream>
#include<cstdlib>    // Random no.
#include<string>
#include<windows.h>  // Colour in console
#include"Maxit.h"
using namespace std;
int main()
{
	Maxit m;
	system("pause");
	m.InitialGrid();
	do
	{
		do {
			system("cls");
			m.DisplayGrid();
			m.Player1_Choice();
		} while (m.again);  // Until Player 1 chooses to quit
		if (m.endgame()) return 0;
		do { 
			system("cls");  
			m.DisplayGrid();  
			m.Player2_Choice(); } while (m.again);  // Until Player 2 chooses to quit
	} while (!m.endgame());  // Until end of game
	return 0;
}
