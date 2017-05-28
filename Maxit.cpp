#include<iostream>
#include<cstdlib>
#include<string>
#include<windows.h>
#include"Maxit.h"
using namespace std;

Maxit::Maxit()
{
	again = 0;                                   // To resume the game
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // For text colour
	DisplayRules();
	a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];  // Game Grid
	for (int i = 0; i < 25; i++)
		freq[i] = 0;  // Limits max. occurences 
	P1sum = 0;  // Player 1 Score
	P2sum = 0;  // Player 2 Score
	stop = 0;  // End Game criterion
}
void Maxit :: InitialGrid()  // Initializes a random grid 
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			do
			{
				temp = -9 + rand() % 25; // No.s between -9 to 15
			} while (freq[9 + temp] >= n/2); // Max freq. of each no. = 4
			a[i][j] = temp;
			freq[9 + temp]++;
		}
	}
	c_row = rand() % n;  // Starting position of game
	c_col = rand() % n; 

}

void Maxit::DisplayGrid()  // To display updated grid and scores
{
	
	cout <<endl;
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\t\t     [Press H for help (or) Q to quit]" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl;
	a[c_row][c_col] = 100; // Current pointer position
	SetConsoleTextAttribute(hConsole, 14);
	cout << endl;
	for (int i = 1; i <= n; i++)
		cout << "\t" << i; 
	cout<<"\n    ";
	SetConsoleTextAttribute(hConsole, 7); // Grid lines
	for (int i = 0; i < 8*n; i++)cout << "_";
	for (int i = 0; i < n; i++)
	{
		cout << "\n   |\n";
		SetConsoleTextAttribute(hConsole, 14);
		cout << "  " << i + 1;
		SetConsoleTextAttribute(hConsole, 7);
		cout<< "|";
		cout << "\t";
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 100)
			{	SetConsoleTextAttribute(hConsole, 14);		cout << "** \t"; SetConsoleTextAttribute(hConsole, 7); // Current Pointer
			}
			else if (a[i][j] == -100)
			{
				cout << "   \t";           // No. already taken
			}
			else
				cout << a[i][j] << " \t";  // Remaining No.s
		}
		cout << "  \n   |\n   |";
		for (int i = 0; i < 8*n; i++)cout << "_";
	}
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n\n  "<<P1name<<" score : " << P1sum;   // Player 1 Score
	cout << "\n\n  "<< P2name<<" score : " << P2sum;  // Player 2 Score
	SetConsoleTextAttribute(hConsole, 7);
}

void Maxit::Player1_Choice()  // Record and update Player 1 choice and scores
{
	bool error, flag = 0;
	// Error - When incorrect choice is entered
	// Flag - Whether valid move exists
	again = 0;  // Whether Player 1 resumes the game
	for (int i = 0; i < n; i++)
		if (a[c_row][i] != 100 && a[c_row][i] != -100) flag = 1;  // When Player 1 has no valid move left
	if (flag)
	{
		do
		{
			error = 0;
			cout << "\n\n  Enter the column number: ";
			cin.getline(P1move, 10);
			if (strcmp(P1move,"Q")==0)  result();  // If Player 1 quits game
			else if (strcmp(P1move, "H") == 0) { if (DisplayHelp()) { DisplayGrid();   again = 1; return; } }  // Help invoked
			else
			{
				P1choice = atoi(P1move);  // Converts string to integer move
				if (P1choice < 1 || P1choice >n) { cout << "\n Error : Choose a column no. between 1 and "<<n<<"\n "; error = 1; } // If chosen column is out of bounds
			else if (a[c_row][P1choice - 1] == 100 || a[c_row][P1choice - 1] == -100) { cout << "\nError : Invalid Move\n "; error = 1; }  // If chosen column is current or taken
			}
			} while (error); // Until a valid move is chosen
			if (!stop)       // Executes if Player 1 hasn't quit
			{
				P1sum += a[c_row][P1choice - 1];  // Score
				a[c_row][c_col] = -100;           // Update no. as taken
				c_col = P1choice - 1;             // Update current column
			}
	}
	else
		result();                                 // Final Scores and result
}
void Maxit::Player2_Choice()                      // Record and update Player 2 choice and scores
{
	bool error, flag=0;
	again = 0;
	for (int i = 0; i < n; i++)
		if (a[i][c_col] != 100 && a[i][c_col] != -100) flag = 1;
	if (flag)
	{
		do
		{
			error = 0;
			cout << "\n\n  Enter the row number: ";
			cin.getline(P2move, 10);
			if (strcmp(P2move, "Q") == 0) result();
			else if (strcmp(P2move, "H") == 0){ if (DisplayHelp()) { DisplayGrid();   again = 1; return;}}
			else
			{
				P2choice = atoi(P2move);
				if (P2choice < 1 || P2choice >n) { cout << "\nError : Choose a row no. between 1 and "<<n<<" \n "; error = 1; }   // If chosen row is out of bounds
				else if (a[P2choice - 1][c_col] == 100 || a[P2choice - 1][c_col] == -100) { cout << "\nError : Invalid Move\n "; error = 1; }  // If chosen row is current or taken
			}
		} while (error);
		if (!stop)   // Executes if Player 2 hasn't quit
		{
			P2sum += a[P2choice - 1][c_col];
			a[c_row][c_col] = -100;     // Update no. as taken
			c_row = P2choice - 1;       // Update current row
		}
	}
	else
		result();

}
void Maxit::DisplayRules()  // Title screen with rules
{
	SetConsoleTextAttribute(hConsole, 14);
	cout << "\n                                    MAXIT                                         \n";
	cout << "                 Copyright: Aishwarya Anandan, Rachneet Kaur\n\n ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n$ Maxit is played on an n x n grid of squares.\n\n$ Each square contains a value ranging from -9 to 15.\n\n$ One of the squares is initially designated with a marker (**) indicating the\n current position.\n";
	cout << "\n$ Player 1 may take any square on the same row as the marker.\n\n$ When Player 1 is done, Player 2 makes a similar move, except choosing between the squares in the column.\n\n$ Play alternates until all squares are taken or until a player is ";
	cout << "left without a valid move.\n\n$ The player with the most points at the end is the winner.\n";
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n\n$ Enter Player 1 name: ";
	SetConsoleTextAttribute(hConsole, 7); getline(cin, P1name);
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n\n$ Enter Player 2 name: "; 
	SetConsoleTextAttribute(hConsole, 7); getline(cin, P2name);
	do
	{
		SetConsoleTextAttribute(hConsole, 11); 
		cout << "\n\n$ Enter a play level ranging from 1 to 3 (1 - Easiest and 3 - Hardest): "; 
		SetConsoleTextAttribute(hConsole, 7); 
		cin.getline(level, 10);  // Level of the game defines grid size
		if (atoi(level) != 1 && atoi(level) != 2 && atoi(level) != 3) cout << "\nEnter a valid level";
	} while (atoi(level) != 1 && atoi(level) != 2 && atoi(level) != 3);
	cout << "\n\n";
	if (atoi(level) == 1) n = 4;  // Grid size
	else if (atoi(level) == 2) n = 6;
	else n = 8;
}

bool Maxit::DisplayHelp()  // To show rules 
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 14);
	cout << "\n                                    HELP                                         \n";
	SetConsoleTextAttribute(hConsole, 7);
	char ch[10];
	cout << "\n$ Initially the marker square is highlighted (**).\n\n$ The player may now select any square on the current row (for Player 1)\n or column (for Player 2).\n\n$ If you enter a row or a column already taken, you will be prompted again.";
	cout << "\n\n$ When no moves remains, the player with the highest point total is the winner.";
	cout << endl << endl;
	do   // Decide to quit or resume the game
	{
		SetConsoleTextAttribute(hConsole, 11);
		cout << "\t\t     Press R to resume (or) Q to quit : ";
		 cin.getline(ch, 10); SetConsoleTextAttribute(hConsole, 7);
		if (!strcmp(ch, "Q") && !strcmp(ch, "R")) cout << "\nEnter a valid choice";
	} while (!strcmp(ch, "Q") && !strcmp(ch, "R"));
	if (!strcmp(ch, "Q"))  // If Playes chooses to quit the game
	{
		result(); return 0;
	}
	else return 1;   // If Player chooses to resume the game
}
void Maxit:: result()  // To display final scores and winner
{
	SetConsoleTextAttribute(hConsole, 14);
	cout << "\n\nGAME OVER!!!";
	if (P1sum > P2sum) cout << "\n\n"<<P1name<<" wins!\n\n";  // Decides the winner
	else if (P1sum < P2sum) cout << "\n\n"<<P2name<<" wins!\n\n";
	else cout << "\n\nGame Draw\n\n"; 
	SetConsoleTextAttribute(hConsole, 7);
	stop = 1;   // To end game
}
bool Maxit::endgame()  // Ends Game
{
	return stop;
}
