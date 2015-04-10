#include "main.h"

/******************************************************
 *Function Name: full_game()
 *Description: This function is the main function of work.c
 *		It calls all the functions and runs key aspects to
 *		the game and it is the only call in main
 *Parameters: None
 ******************************************************/
int full_game ( void )
{
	FILE *out_file = NULL; //Battleship.txt
	char p1_board[10][10]; //Player1s board
	char cpu_board[10][10]; //CPUs board
	char p1_hit_board[10][10]; //Player1s board of guessed squares
	char cpu_hit_board[10][10]; //CPUs board of guessed squares
	int x = 0, y = 0; // For the loops
	int first_or_sec = 0; //Random number of who goes first
	int phits = 0, chits = 0, rounds = 0; //Player hits, computer hits, rounds
	char row_num_letter = 'a'; //For printing boards, it prints the letter on the left of the row

	/**************************/

	print_game_rules ( );

	//Initialize all four boards, two player boards, and two hit boards
	initialize_board ( p1_board );
	initialize_board ( cpu_board );
	initialize_board ( p1_hit_board );
	initialize_board ( cpu_hit_board );


	//Open battleship.log
	out_file = fopen ( "Battleship.txt", "w" );

	//asks user to place ships, then randomly chooses places for computer's board
	create_board ( p1_board );
	rand_board ( cpu_board );


	//Prints users board
	printf ( "Your complete board:\n");
	for (x = 0; x < 10; x++)
	{
		row_num_letter = x + 97;
		printf ( "%c ", row_num_letter );
		for (y = 0; y < 10; y++)
		{
			printf ( "%c ", p1_board[x][y] );
		}
		putchar('\n');
	}

	//Random guesses who goes first, number is ) or 1. If 1, player goes first
	printf ( "Randomly choosing who goes first...\n");
	first_or_sec = rand() % 2;


	//If first_or_sec is 1, player goes first
	if (first_or_sec == 1)
	{
		printf ( "You have been chosen to go first!\n");

		//While loop states that the game plays as the hits are less than 17. If 17, every ship has sunk
		while ((phits < 17) && (chits < 17))
		{
			//Always makes hits 0 at the beginning of each round. I couldnt keep a running total
			//so I just recount at the end of every round using forloops
			phits = 0;
			chits = 0;
			//Running total of round for printing
			rounds++;
			printf ( "This is round %d\n", rounds);

			printf ( "It's your turn!\n");
			printf ( "Your guesses to this point: \n");

			//Prints users hit_board(guesses) to this point
			for (x = 0; x < 10; x++)
			{
				row_num_letter = x + 97;
				printf ( "%c ", row_num_letter );
				for (y = 0; y < 10; y++)
				{
					printf ( "%c ", p1_hit_board[x][y] );
				}
				putchar('\n');
			}

			//Users_input gets user's guess of a square on the board
			users_input ( cpu_board, p1_hit_board, out_file );
			//Calcs player hits
			for (x = 0; x < 10; x++)
			{
				for (y = 0; y < 10; y++)
				{
					if (p1_hit_board[x][y] == 'X')
					{
						phits++;
					}
				}
			}

			//Does the same as above for the computer

			printf ( "It's the computer's turn!\n");
			printf ( "Computer guesses to this point: \n");

			for (x = 0; x < 10; x++)
			{
				row_num_letter = x + 97;
				printf ( "%c ", row_num_letter );
				for (y = 0; y < 10; y++)
				{
					printf ( "%c ", cpu_hit_board[x][y] );
				}
				putchar('\n');
			}
			computer_input ( p1_board, cpu_hit_board, out_file );
			for (x = 0; x < 10; x++)
			{

				for (y = 0; y < 10; y++)
				{
					if (cpu_hit_board[x][y] == 'X')
					{
						chits++;
					}
				}
			}
			printf ( "Computer hits: %d\n",  chits );
			printf ( "Player hits: %d\n", phits );
		}
	}

	//If computer is randomly chosen first. This works the same way as the part above.
	else
	{
		printf ( "The computer has been chosen to go first..\n");

		while ((phits < 17) && (chits < 17))
		{
			phits = 0;
			chits = 0;
			rounds++;
			printf ( "This is round %d\n", rounds);

			printf ( "It's the computer's turn!\n");
			printf ( "Computer guesses to this point: \n");
			for (x = 0; x < 10; x++)
			{
				row_num_letter = x + 97;
				printf ( "%c ", row_num_letter );
				for (y = 0; y < 10; y++)
				{
					printf ( "%c ", cpu_hit_board[x][y] );
				}
				putchar('\n');
			}

			computer_input ( p1_board, cpu_hit_board, out_file);
			for (x = 0; x < 10; x++)
			{
				for (y = 0; y < 10; y++)
				{
					if (cpu_hit_board[x][y] == 'X')
					{
						chits++;
					}
				}
			}

			printf ( "It's your turn!\n");
			printf ( "Your guesses to this point: \n");
			for (x = 0; x < 10; x++)
			{
				row_num_letter = x + 97;
				printf ( "%c ", row_num_letter );
				for (y = 0; y < 10; y++)
				{

					printf ( "%c ", p1_hit_board[x][y] );
				}
				putchar('\n');
			}
			users_input ( cpu_board, p1_hit_board, out_file );
			for (x = 0; x < 10; x++)
			{
				for (y = 0; y < 10; y++)
				{
					if (p1_hit_board[x][y] == 'X')
					{
						phits++;
					}
				}
			}
			printf ( "Computer hits: %d\n",  chits );
			printf ( "Player hits: %d\n", phits );
		}
	}

	//If player has hit more times than computer, player wins
	if (phits > chits)
	{
		printf ( "Game over!!!\n");
		printf ( "You beat the computer!\n");
		printf ( "You guessed every one of his ships and his fleet is sunk!\n");
		printf ( "Thank you for playing \n");
	}

	//If computer has hit more times than player, computer wins
	else if (chits > phits)
	{
		printf ( "Game over!!!\n");
		printf ( "The computer beat you...\n");
		printf ( "They guessed every one of your ships and your whole fleet sunk\n");
		printf ( "Thank you for playing \n");
	}
	//If hits are the same after the same round, tie!
	else
	{
		printf ( "I think this was a tie!\n");
		printf ( "You both sunk each other's fleet on the same move!\n");
		printf ( "Thank you for playing\n");
	}

	//Close file
	fclose ( out_file );

	return 0;
}

/******************************************************
 *Function Name: print_game_rules()
 *Description: Prints game rules...
 *Parameters: None
 ******************************************************/
void print_game_rules ( void )
{
	printf ( "Welcome to battleship!\n");
	printf ( "Here are the game rules...\n");
	printf ( "There is a 10 x 10 grid for each player\n");
	printf ( "Each grid has 5 different ships on it, all of different sizes\n");
	printf ( "Each player guesses a position on the opponent's grid\n");
	printf ( "If there is a ship on that exact position, it is a hit\n");
	printf ( "If the player hits every position on a ship, it is sunk.\n");
	printf ( "Once a player sinks every ship on their opponent's grid, they win\n");
	printf ( "Players take turns guessing on each other's board\n");
	printf ( "Hope you have fun, good luck!\n\n");
}

/******************************************************
 *Function Name: users_input()
 *Description: This asks the user to guess where the computer's
 *				pieces are. It returns what square you guessed,
 *				if it was a hit or not, and prints to Battleship.log
 *Parameters: board, hit_board, Battleship.log
 ******************************************************/
void users_input ( char board[10][10], char hit_board[10][10], FILE *outfile )
{
	char users_char_choice; //User puts in a letter-number combination and this is the letter
	int number_choice, char_choice_num; //The number of users input, and the number that the letter corresponds to
	int x = 0, y = 0, replay = 0; //For loop initiation variables

	//Gets users input for what square to fire at
	printf ( "What square would you like to fire at? Enter a letter-number combination: ");
	scanf ( " %c%d", &users_char_choice, &number_choice );

	//Checks to make sure user's input is a legit possibility
	if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

	//Because array first possible square starts with 0
	number_choice--;

	//Replay to make sure the square is a possible square to guess
	while (replay == 0)
	{
		//Makes sure the square is a square user hasnt guessed
		if (hit_board[char_choice_num][number_choice] == '~')
		{
			//If that square is a ship, its a hit
			if (board[char_choice_num][number_choice] == 'O')
			{
				board[char_choice_num][number_choice] = 'H';
				printf ( "That's a hit!!!!!\n");
				hit_board[char_choice_num][number_choice] = 'X';

				fprintf ( outfile, "%c%d player hit\n", users_char_choice, number_choice );

			}

			//If that square is open water, its a miss
			else
			{
				printf ( "That's a miss!!!\n");
				hit_board[char_choice_num][number_choice] = 'O';

				fprintf ( outfile, "%c%d player miss\n", users_char_choice, number_choice );
			}
			replay++;
		}
		//If user has already guessed that square, it re guesses
		else
		{
			printf ( "You have already guessed that\n");
			printf ( "Enter a different combination: ");
			scanf ( " %c%d", &users_char_choice, &number_choice );

			if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
			{
				char_choice_num = users_char_choice - 97;
			}

			number_choice--;
		}
	}
}

/******************************************************
 *Function Name: computer_input()
 *Description: Guesses a random square for the computer. If
 *				they have already guessed that square it checks
 *				for that and guesses a new square. It returns
 *				if a hit or not, and prints to Battleship.log
 *Parameters: board, hit_board, Battleship.log
 ******************************************************/
void computer_input ( char board[10][10], char hit_board[10][10], FILE *outfile )
{
	int rand_col = 0, rand_row = 0, rand_colE = 0; //Random columns for the computer's guess
	char rand_char_row = 'a'; //To print what computer's guess was in letter-number form
	int replay = 0; //TO make sure computer hasnt guessed this one yet

	rand_col = rand() % 10; //Random column for guess
	rand_row = rand() % 10; //Random row for guess
	rand_char_row = rand_row + 97; //To print computer's guess, makes new variable with ascii
	while ( replay == 0)
	{
		//make sure they havent guessed that square yet
		if (hit_board[rand_row][rand_col] == '~')
		{
			//Prints computer's guess
			rand_colE = rand_col + 1;
			printf ( "The computer guessed square %c%d\n", rand_char_row, rand_colE);

			//If there is a ship there, hit!
			if (board[rand_row][rand_col] == 'O')
			{
				printf ( "That was a hit!!!\n");
				hit_board[rand_row][rand_col] = 'X';
				board[rand_row][rand_col] = 'H';
				fprintf ( outfile, "%c%d cpu hit\n", rand_char_row, rand_col );
			}

			//If open water there, miss!
			else
			{
				printf ( "The computer missed!\n");
				hit_board[rand_row][rand_col] = 'O';
				fprintf ( outfile, "%c%d cpu miss\n", rand_char_row, rand_col );
			}
			replay++;

		}

		//If computer has already guessed that square, it guesses again
		else
		{
			rand_row = rand() % 10;
			rand_col = rand() % 10;
			rand_char_row = rand_row + 97;
			replay = 0;
		}
	}

}

/******************************************************
 *Function Name: initialize_board()
 *Description: initializes board by printing a 10 x 10 array
 *				of ~
 *Parameters: board
 ******************************************************/
void initialize_board ( char board[10][10] )
{
	int x = 0, y = 0;

	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			board[x][y] = '~';
		}
	}
}

/******************************************************
 *Function Name: create_board()
 *Description: asks user where they want to put their ships
 *				on the board. it prints Os where their ships
 *				are placed.
 *Parameters: board
 ******************************************************/
void create_board ( char board[10][10] )
{
	char vert_or_hor; //Asks if ship should be vertical or horizontal
	char users_char_choice = 'n'; //User's row choice in letter
	int users_num_choice = 0, char_choice_num = 0; //Users column choice and users row choice in number form
	int x = 0, y = 0; //For loop initialation
	char row_num_letter = 'a';

	//asks user to place carrier
	printf ( "Where would you like to place your ships?\n");
	printf ( "You have 5 ships, carrier, battleship, submarine, destroyer, and cruiser\n");
	printf ( "Would you like to place your carrier vertical(v) or horizontal(h)?: ");
	scanf ( " %c", &vert_or_hor);
	//If horizontal ship
	if ( vert_or_hor == 'h')
	{
		printf ( "What is the far left position of the carrier you're placing?\n");
		printf ( "Enter a letter number combination, no space: ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );

		users_num_choice--;

		//make sure users ship placement is legit
		if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

		//Places ship where user guessed
		for (x = 0; x < 5; x++)
		{
			board[char_choice_num][users_num_choice + x] = 'O';
		}
	}

	//If users input says vertical. This works the same way as horizontal but adds one to every row
	// In the for loop instead of column.
	else if (vert_or_hor == 'v')
	{
		printf ( "What is the top position of the carrier you're placing? (letter number): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		while (users_char_choice > 'f')
		{
			if (users_char_choice > 'f')
			{
				printf ( "That is not a possible situation, remember the carrier is 5 spaces long, ");
				printf ( "so it has to be at least row 6 or higher\n");
				printf ( "Type in a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
			}
		}

		if ((users_char_choice >= 'a') && (users_char_choice <= 'f'))
		{
			char_choice_num = users_char_choice - 97;
		}


	for (x = 0; x < 5; x++)
		{
			board[char_choice_num + x][users_num_choice] = 'O';
		}

	}

	//Prints your board after the carrier
	printf ( "Your board after one ship:\n");
	for (x = 0; x < 10; x++)
	{
		row_num_letter = x + 97;
		printf ( "%c ", row_num_letter );
		for (y = 0; y < 10; y++)
		{
			printf ( "%c ", board[x][y] );
		}
		putchar('\n');
	}

	//BATTLESHIP
	//every other ship works the same way as the carrier except the dimentions of the
	//ship are different every time. i am not going to comment all of it because it is
	//super repetitive. The ship lengths are the only thing that changes. It prints the
	//board every time after the ship is placed.
	printf ( "Would you like to place your battleship vertical(v) or horizontal(h)?: ");
	scanf ( " %c", &vert_or_hor);
	if ( vert_or_hor == 'h')
	{
		printf ( "What is the far left position of the battleship you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

		for (x = 0; x < 4; x++)
		{
			if (board[char_choice_num][users_num_choice + x] != '~')
			{
				for (y = 0; y < 4; y++)
				{
					board[char_choice_num][users_num_choice + y] = '~';
				}
				board[char_choice_num][users_num_choice + x] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num][users_num_choice + x] = 'O';
			}
		}
	}
	else if (vert_or_hor == 'v')
	{
		printf ( "What is the top position of the battleship you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		while (users_char_choice > 'g')
		{
			if (users_char_choice > 'g')
			{
				printf ( "That is not a possible situation, remember the battleship is 4 spaces long, ");
				printf ( "so it has to be at least row 7 or higher\n");
				printf ( "Type in a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
			}
		}
		if ((users_char_choice >= 'a') && (users_char_choice <= 'g'))
		{
			char_choice_num = users_char_choice - 97;
		}


	for (x = 0; x < 4; x++)
		{
			if (board[char_choice_num + x][users_num_choice] != '~')
			{
				for (y = 0; y < 4; y++)
				{
					board[char_choice_num + y][users_num_choice] = '~';
				}
				board[char_choice_num + x][users_num_choice] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num + x][users_num_choice] = 'O';
			}
		}

	}

	printf ( "Your board after two ships:\n");
	for (x = 0; x < 10; x++)
	{
		row_num_letter = x + 97;
		printf ( "%c ", row_num_letter );
		for (y = 0; y < 10; y++)
		{
			printf ( "%c ", board[x][y] );
		}
		putchar('\n');
	}

	printf ( "Would you like to place your submarine vertical(v) or horizontal(h)?: ");
	scanf ( " %c", &vert_or_hor);
	if ( vert_or_hor == 'h')
	{
		printf ( "What is the far left position of the submarine you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

		for (x = 0; x < 3; x++)
		{
			if (board[char_choice_num][users_num_choice + x] != '~')
			{
				for (y = 0; y < 3; y++)
				{
					board[char_choice_num][users_num_choice + y] = '~';
				}
				board[char_choice_num][users_num_choice + x] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num][users_num_choice + x] = 'O';
			}
		}
	}
	else if (vert_or_hor == 'v')
	{
		printf ( "What is the top position of the submarine you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		while (users_char_choice > 'h')
		{
			if (users_char_choice > 'h')
			{
				printf ( "That is not a possible situation, remember the submarine is 3 spaces long, ");
				printf ( "so it has to be at least row 8 or higher\n");
				printf ( "Type in a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
			}
		}
		if ((users_char_choice >= 'a') && (users_char_choice <= 'h'))
		{
			char_choice_num = users_char_choice - 97;
		}


	for (x = 0; x < 3; x++)
		{
			if (board[char_choice_num + x][users_num_choice] != '~')
			{
				for (y = 0; y < 3; y++)
				{
					board[char_choice_num + y][users_num_choice] = '~';
				}
				board[char_choice_num + x][users_num_choice] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num + x][users_num_choice] = 'O';
			}
		}
	}

	printf ( "Your board after three ships:\n");
	for (x = 0; x < 10; x++)
	{
		row_num_letter = x + 97;
		printf ( "%c ", row_num_letter );
		for (y = 0; y < 10; y++)
		{
			printf ( "%c ", board[x][y] );
		}
		putchar('\n');
	}

	printf ( "Would you like to place your destroyer vertical(v) or horizontal(h)?: ");
	scanf ( " %c", &vert_or_hor);
	if ( vert_or_hor == 'h')
	{
		printf ( "What is the far left position of the destroyer you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

		for (x = 0; x < 3; x++)
		{
			if (board[char_choice_num][users_num_choice + x] != '~')
			{
				for (y = 0; y < 3; y++)
				{
					board[char_choice_num][users_num_choice + y] = '~';
				}
				board[char_choice_num][users_num_choice + x] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num][users_num_choice + x] = 'O';
			}
		}
	}
	else if (vert_or_hor == 'v')
	{
		printf ( "What is the top position of the destroyer you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		while (users_char_choice > 'h')
		{
			if (users_char_choice > 'h')
			{
				printf ( "That is not a possible situation, remember the destroyer is 3 spaces long, ");
				printf ( "so it has to be at least row 8 or higher\n");
				printf ( "Type in a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
			}
		}
		if ((users_char_choice >= 'a') && (users_char_choice <= 'h'))
		{
			char_choice_num = users_char_choice - 97;
		}


	for (x = 0; x < 3; x++)
	{
		if (board[char_choice_num + x][users_num_choice] != '~')
		{
			for (y = 0; y < 3; y++)
			{
				board[char_choice_num + y][users_num_choice] = '~';
			}
			board[char_choice_num + x][users_num_choice] = 'O';
			printf ( "You already have a ship in one of those positions!\n");
			printf ( "Enter a new position: ");
			scanf ( " %c%d", &users_char_choice, &users_num_choice );
			users_num_choice--;
			if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
			{
				char_choice_num = users_char_choice - 97;
			}
			x = -1;
		}
		else
		{
			board[char_choice_num + x][users_num_choice] = 'O';
		}
	}
	}

	printf ( "Your board after four ships:\n");
	for (x = 0; x < 10; x++)
	{
		row_num_letter = x + 97;
		printf ( "%c ", row_num_letter );
		for (y = 0; y < 10; y++)
		{
			printf ( "%c ", board[x][y] );
		}
		putchar('\n');
	}

	printf ( "Would you like to place your cruiser vertical(v) or horizontal(h)?: ");
	scanf ( " %c", &vert_or_hor);
	if ( vert_or_hor == 'h')
	{
		printf ( "What is the far left position of the cruiser you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
		{
			char_choice_num = users_char_choice - 97;
		}

		for (x = 0; x < 2; x++)
		{
			if (board[char_choice_num][users_num_choice + x] != '~')
			{
				for (y = 0; y < 2; y++)
				{
					board[char_choice_num][users_num_choice + y] = '~';
				}
				board[char_choice_num][users_num_choice + x] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num][users_num_choice + x] = 'O';
			}
		}
	}
	else if (vert_or_hor == 'v')
	{
		printf ( "What is the top position of the cruiser you're placing? (number letter): ");
		scanf ( " %c%d", &users_char_choice, &users_num_choice );
		users_num_choice--;

		while (users_char_choice > 'i')
		{
			if (users_char_choice > 'i')
			{
				printf ( "That is not a possible situation, remember the cruiser is 2 spaces long, ");
				printf ( "so it has to be at least row 9 or higher\n");
				printf ( "Type in a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
			}
		}
		if ((users_char_choice >= 'a') && (users_char_choice <= 'i'))
		{
			char_choice_num = users_char_choice - 97;
		}


	for (x = 0; x < 2; x++)
		{
			if (board[char_choice_num + x][users_num_choice] != '~')
			{
				for (y = 0; y < 2; y++)
				{
					board[char_choice_num + y][users_num_choice] = '~';
				}
				board[char_choice_num + x][users_num_choice] = 'O';
				printf ( "You already have a ship in one of those positions!\n");
				printf ( "Enter a new position: ");
				scanf ( " %c%d", &users_char_choice, &users_num_choice );
				users_num_choice--;
				if ((users_char_choice >= 'a') && (users_char_choice <= 'j'))
				{
					char_choice_num = users_char_choice - 97;
				}
				x = -1;
			}
			else
			{
				board[char_choice_num + x][users_num_choice] = 'O';
			}
		}
	}
}

/******************************************************
 *Function Name: rand_board()
 *Description: Randomly places pieces on the board for the
 *				computer. If it randomly chooses a square or
 *				squares that were previously chosen, it randomly
 *				chooses another square.
 *Parameters: board
 ******************************************************/
void rand_board ( char board[10][10] )
{
	int rand_row, rand_col, rand_v_or_h; //Randomly generated column, row, vertical or horizontal
	int x, y = 0, re_do = 0; //For loop initiation

	//CARRIER


	rand_v_or_h = rand() % 2; //Randomly chooses if ship is vertical or horizontal
	// if rand_v_or_h is 1, horizontal
	if (rand_v_or_h == 1)
	{
		rand_col = rand() % 10; //Random column generator
		rand_row = rand() % 6; //Random row generator
		//horizontal

		//Places carrier off randomly generated values
		for (x = 0; x < 5; x++)
		{
			board[rand_row + x][rand_col] = 'O';
		}
	}

	// If generates randomly vertical, it works the same way except rows change
	// instead of columnsw
	else if (rand_v_or_h == 0)
	{
		//vertical
		rand_col = rand() % 6;
		rand_row = rand() % 10;
		for (x = 0; x < 5; x++)
		{
			board[rand_row][rand_col + x] = 'O';
		}
	}

	//BATTLESHIP
	//Battleship works almost the same way as carrier and so does every other ship. The only two
	//differences are that the ship lengths are different and that there is a series of checks to
	//make sure those squares are a possible place for the computer to guess.
	while (re_do == 0)
	{


		rand_v_or_h = rand() % 2;
		if (rand_v_or_h == 1)
		{
			//horizontal
			rand_col = rand() % 10;
			rand_row = rand() % 7;
			x = 0;
			while (x < 4)
			{
				if (board[rand_row + x][rand_col] == 'O')
				{
					x = 0;
					rand_col = rand() % 10;
					rand_row = rand() % 7;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 4; x++)
			{
				board[rand_row + x][rand_col] = 'O';
			}
		}
		if (rand_v_or_h == 0)
		{
			//vertical
			rand_col = rand() % 7;
			rand_row = rand() % 10;
			x = 0;
			while (x < 4)
			{
				if (board[rand_row][rand_col + x] == 'O')
				{
					x = 0;
					rand_col = rand() % 7;
					rand_row = rand() % 10;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x <4; x++)
			{
				board[rand_row][rand_col + x] = 'O';
			}
		}
	}
	re_do = 0;
	while (re_do == 0)
	{


		rand_v_or_h = rand() % 2;
		if (rand_v_or_h == 1)
		{
			//horizontal
			rand_col = rand() % 10;
			rand_row = rand() % 8;
			x = 0;
			while (x < 3)
			{
				if (board[rand_row + x][rand_col] == 'O')
				{
					x = 0;
					rand_col = rand() % 10;
					rand_row = rand() % 8;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 3; x++)
			{
				board[rand_row + x][rand_col] = 'O';
			}
		}
		if (rand_v_or_h == 0)
		{
			//vertical
			rand_col = rand() % 8;
			rand_row = rand() % 10;
			x = 0;
			while (x < 3)
			{
				if (board[rand_row][rand_col + x] == 'O')
				{
					x = 0;
					rand_col = rand() % 8;
					rand_row = rand() % 10;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 3; x++)
			{
				board[rand_row][rand_col + x] = 'O';
			}
		}
	}
	re_do = 0;
	while (re_do == 0)
	{

		rand_v_or_h = rand() % 2;
		if (rand_v_or_h == 1)
		{
			//horizontal
			rand_col = rand() % 10;
			rand_row = rand() % 8;
			x = 0;
			while (x < 3)
			{
				if (board[rand_row + x][rand_col] == 'O')
				{
					x = 0;
					rand_col = rand() % 10;
					rand_row = rand() % 8;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 3; x++)
			{
				board[rand_row + x][rand_col] = 'O';
			}
		}
		if (rand_v_or_h == 0)
		{
			//vertical
			rand_col = rand() % 8;
			rand_row = rand() % 10;
			x = 0;
			while (x < 3)
			{
				if (board[rand_row][rand_col + x] == 'O')
				{
					x = 0;
					rand_col = rand() % 8;
					rand_row = rand() % 10;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 3; x++)
			{
				board[rand_row][rand_col + x] = 'O';
			}
		}
	}
	re_do = 0;
	while (re_do == 0)
	{

		rand_v_or_h = rand() % 2;
		if (rand_v_or_h == 1)
		{
			//horizontal
			rand_col = rand() % 10;
			rand_row = rand() % 9;
			x = 0;
			while (x < 2)
			{
				if (board[rand_row + x][rand_col] == 'O')
				{
					x = 0;
					rand_col = rand() % 10;
					rand_row = rand() % 9;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 2; x++)
			{
				board[rand_row + x][rand_col] = 'O';
			}
		}
		else if (rand_v_or_h == 0)
		{
			//vertical
			rand_col = rand() % 9;
			rand_row = rand() % 10;
			x = 0;
			while (x < 2)
			{
				if (board[rand_row][rand_col + x] == 'O')
				{
					x = 0;
					rand_col = rand() % 9;
					rand_row = rand() % 10;
				}
				else
				{
					re_do = 1;
					x++;
				}
			}
			for (x = 0; x < 2; x++)
			{
				board[rand_row][rand_col + x] = 'O';
			}
		}
	}

}
