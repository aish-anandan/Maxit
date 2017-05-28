MAXIT

Maxit is usually played on an n x n grid of squares. Each square contains a value ranging from -9 to 15.One of the squares is 
initially designated with a marker (**) indicating the current position. Player 1 may take any square on the same row as the 
marker. When Player 1 is done, Player 2 makes a similar move, except choosing between the squares in the column.
Play alternates until all squares are taken or until a player is left without a valid move. The player with the most points 
at the end is the winner.

The project is subdivided into the following files :
	
Maxit.h - Header file containing the class definition and member function prototypes
Maxit.cpp - Member function definitions
main.cpp - Main application source file

We start by creating a class "Maxit" that has attributes such as the size of the grid, player moves, net scores of the players 
(integers), player names (strings) and the game stop and resume criteria (boolean). The various member functions work as follows:

1. Maxit() - Constructor, that allocates memory for the grid, by taking input from the user (via the DisplayRules () function),
and initializes the stopping criterion and the players' scores

2. DisplayRules() - Displays the introductory screen, explaining the game objectives and asking for the following inputs from
the user : Names of player 1 and player 2 and the level of difficulty (1 - 4X4 grid, 2 - 6x6 grid, 3 - 8x8 grid).

3. InitialGrid() - Initializes the grid by generating random numbers between -9 and 15. The frequency array makes sure 
that no number is repeated more than (n/2) times, where (n/2) is the size of the grid.  Also, one of the elements of the grid is
randomly allocated as the starting point, indicated by (**). This location is stored in c_row,c_column and it carries the value
of 100.

4. DisplayGrid() - Displays the grid with the values generated from InitialGrid() and also displays the net scores of player 1
and player 2.

5. Player1_Choice() - Takes the input of the column number from Player 1. In case of an invalid input ( specifying a number out
of bounds or selecting a column that is already taken), the user is prompted till a valid entry is obtained. In case no valid
choices exist, game terminates. Options to display help or quit the game at any point are also included.

6. Player2_Choice() - Similar to Player1_Choice() and takes the input of row number from Player 2.

7. DisplayHelp() - Displays help whenever player enters 'H'. Player can choose to resume the game after this or quit the game.

8. result() - Compares the scores of player 1 and  player 2 and displays the scores. Sets the stopping criterion to true.

9. endgame() - returns the stopping criterion value when called. 

The main functions calls the functions listed above, till the user quits the game or till the game ends.