using namespace std;
class Maxit
{
	int n;  // Grid size
	char level[10];  // Difficulty level (in case wrong choice entered)
	int **a;  // Grid
	int freq[25];  // Limit on freq. of no.s
	int c_row, c_col;  // Current position
	int P1sum, P2sum;  // Scores
	int P1choice, P2choice;  // Valid Moves 
	char P1move[10], P2move[10]; // User move input 
	bool stop;  // End game criterion
	string P1name;  // Players' names
	string P2name;

public:
	bool again;  // Resume game criterion
	Maxit();
	void DisplayRules();
	bool DisplayHelp();
	void InitialGrid();
	void DisplayGrid();
	void Player1_Choice();
	void Player2_Choice();
	void result();
	bool endgame();
	HANDLE hConsole;


};
