#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

// check if a given input is a legal legal
// bugs:
// any nonnumber input (eg f) produces inf loop :(
bool legalmove(size_t player1, size_t player2, size_t move)
{
    // only 9 spaces available
    if (move > 9 || move == 0)
	return false;

    // check if a player has alerady made that move
    if (player1 & (1 << (move -1)))
	return false;
    else
    {
	if (player2 & (1 << (move -1)))
	    return false;
	else
	    return true;
    }
}

// used to fill in the board
string fillboard(size_t player1, size_t player2, size_t square)
{
    if ( player1 & (1 << (square - 1)))
	return "o";
    else
    {
	if ( player2 & (1 << (square - 1)))
	    return "x";
	else
	    return to_string(square);
    }
}

// prints board to screen
// 1|2|3
// -+-+-
// 4|5|6
// -+-+-
// 7|8|9
void makeboard(size_t player1, size_t player2)
{
    cout << fillboard(player1, player2, 1) << "|"
	 << fillboard(player1, player2, 2) << "|"
	 << fillboard(player1, player2, 3) << '\n';
    cout << "-+-+-" << '\n';
    cout << fillboard(player1, player2, 4) << "|"
	 << fillboard(player1, player2, 5) << "|"
	 << fillboard(player1, player2, 6) << '\n';
    cout << "-+-+-" << '\n';
    cout << fillboard(player1, player2, 7) << "|"
	 << fillboard(player1, player2, 8) << "|"
	 << fillboard(player1, player2, 9) << '\n';
}

// check all game ending combinations
bool gameend(size_t player)
{
    if ((player & 84) == 84 || (player & 7) == 7 ||
	(player & 56) == 56 || (player & 448) == 448 ||
	(player & 273) == 273 || (player & 292) == 292 ||
	(player & 146) == 146 || (player & 73) == 73)
	return true;
    else
	return false;
}

int main(int argc, char *argv[])
{
    // init variables
    size_t player1 = 0;			//o
    size_t player2 = 0;			//x
    size_t move;
    bool legal;
    size_t movecount = 0;

    // main game loop
    while (true)
    {
	// print initial board
	makeboard(player1, player2);

	// player1's turn
	do
	{
	    cout << "Player 1, make a move: " << '\n';
	    cin >> move;
	    if (move > 9)
		break;
	    legal = legalmove(player1, player2, move);

	    if (!legal)
	        cout << "That is not a legal move :(" << '\n';
	    else
		player1 += (1 << (move - 1));
	}
	while (!legal);

	makeboard(player1, player2);

	// check if game is won by player1
	if (gameend(player1))
	{
	    cout << "GG, player 1 has won" << '\n';
	    break;
	}

	// counter for draw
	++movecount;
	if (movecount == 5)
	{
	    cout << "GG, the game is a draw" << '\n';
	    break;
	}

	// player2's turn
	do
	{
	    cout << "Player 2, make a move: " << '\n';
	    cin >> move;
	    legal = legalmove(player1, player2, move);

	    if (!legal)
	        cout << "That is not a legal move :(" << '\n';
	    else
		player2 += (1 << (move - 1));
	}
	while (!legal);

	// check if game is won by player2
	if (gameend(player2))
	{
	    cout << "GG, player 2 has won" << '\n';
	    makeboard(player1, player2);
	    break;
	}
    }
}
