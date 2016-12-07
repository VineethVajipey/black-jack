#include <iostream>
#include <array>
#include <ctime>
#include <string>
using namespace std;

#define MAX_CARDS_DECK 52
#define MAX_CARDS_DRAW 15
#define MAX_SUIT 4
#define MAX_RANK 13


enum Rank
{
	RANK_2 = 0,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE
};

enum Suit
{
	SUIT_CLUBS,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_SPADES
};

struct Card
{
	Rank Rank;
	Suit Suit;
};

void printCard(Card &Card)
{
	switch (Card.Rank)
	{
	case RANK_2:		cout << 2; break;
	case RANK_3:		cout << 3; break;
	case RANK_4:		cout << 4; break;
	case RANK_5:		cout << 5; break;
	case RANK_6:		cout << 6; break;
	case RANK_7:		cout << 7; break;
	case RANK_8:		cout << 8; break;
	case RANK_9:		cout << 9; break;
	case RANK_10:		cout << 10; break;
	case RANK_JACK:		cout << "Jack"; break;
	case RANK_QUEEN:	cout << "Queen"; break;
	case RANK_KING:		cout << "King"; break;
	case RANK_ACE:		cout << "Ace"; break;
	}

	cout << " of ";

	switch (Card.Suit)
	{
	case SUIT_CLUBS:	cout << "Clubs"; break;
	case SUIT_DIAMONDS:	cout << "Diamonds"; break;
	case SUIT_HEARTS:	cout << "Hearts"; break;
	case SUIT_SPADES:	cout << "Spades"; break;
	}

	cout << endl;
}

int valueCard(Card &Card)
{
	switch (Card.Rank)
	{
	case RANK_2:		return 2; break;
	case RANK_3:		return 3; break;
	case RANK_4:		return 4; break;
	case RANK_5:		return 5; break;
	case RANK_6:		return 6; break;
	case RANK_7:		return 7; break;
	case RANK_8:		return 8; break;
	case RANK_9:		return 9; break;
	case RANK_10:		return 10; break;
	case RANK_JACK:		return 10; break;
	case RANK_QUEEN:	return 10; break;
	case RANK_KING:		return 10; break;
	case RANK_ACE:		return 1; break;
	}
}


void fillArray(array<Card, MAX_CARDS_DECK> &Deck)
{
	int totalCount = 0;
	for (int rankCount = 0; rankCount < MAX_RANK; rankCount++)
		for (int suitCount = 0; suitCount < MAX_SUIT; suitCount++)
		{
			Deck[totalCount].Rank = static_cast<Rank>(rankCount);
			Deck[totalCount].Suit = static_cast<Suit>(suitCount);
			++totalCount;
		}
}

void shuffleArray(array<Card, MAX_CARDS_DECK> &Deck)
{
	srand(time(NULL));
	for (int count = 0; count < 50; count++)
		swap(Deck[rand() % MAX_CARDS_DECK], Deck[rand() % MAX_CARDS_DECK]);
}

void drawArray(array<Card, MAX_CARDS_DECK> &Deck, array<Card, MAX_CARDS_DRAW> &Player, int &topCard, int &playerTurn)
{
	Player[playerTurn] = Deck[topCard];
	topCard++;
}

void userChoice(array<Card, MAX_CARDS_DECK> &Deck, array<Card, MAX_CARDS_DRAW> &Player, int &topCard, int &playerCount, int &playerSum, int &houseSum, char &userInput)
{
	cout << "Do you want to HIT or STAND? (H or S): ";
	cin >> userInput;

	if (userInput == 'H' || userInput == 'h')
	{
		cout << "Your next card is: ";
		drawArray(Deck, Player, topCard, playerCount);
		printCard(Player[playerCount]);
		playerSum += valueCard(Player[playerCount]);
		playerCount++;
	}
	cout << "Your total is: " << playerSum << endl << endl;
}

void houseChoice(array<Card, MAX_CARDS_DECK> &Deck, array<Card, MAX_CARDS_DRAW> &House, int &topCard, int &houseCount, int &houseSum, int &playerSum, char &houseInput)
{
	if (houseSum <= 16 || houseSum < playerSum)
	{
		cout << "House drew a: ";
		drawArray(Deck, House, topCard, houseCount);
		printCard(House[houseCount]);
		houseSum += valueCard(House[houseCount]);
		houseCount++;
		cout << "House's total is: " << houseSum << endl << endl;
	}
	else
		houseInput = 's';
}

int mainCopy()
{
	// Initialize the arrays (Deck, Player, House)
	array<Card, MAX_CARDS_DECK> Deck;
	array<Card, MAX_CARDS_DRAW> Player;
	array<Card, MAX_CARDS_DRAW> House;

	//Get deck ready
	fillArray(Deck);
	shuffleArray(Deck);

	//Important variables
	int topCard = 0;
	int houseCount = 0;
	int playerCount = 0;
	int houseSum = 0;
	int playerSum = 0;
	char userInput = '.';
	char houseInput = '.';

	houseChoice(Deck, House, topCard, houseCount, houseSum, playerSum, houseInput);
	houseChoice(Deck, House, topCard, houseCount, houseSum, playerSum, houseInput);

	//Print players two draws
	cout << "Your first card is: ";
	drawArray(Deck, Player, topCard, playerCount);
	printCard(Player[playerCount]);
	playerSum += valueCard(Player[playerCount]);
	playerCount++;

	cout << "Your second card is: ";
	drawArray(Deck, Player, topCard, playerCount);
	printCard(Player[playerCount]);
	playerSum += valueCard(Player[playerCount]);
	playerCount++;

	cout << "Your total is: " << playerSum << endl << endl;

	while (1)
	{
		//User decision, Hit or Stand
		userChoice(Deck, Player, topCard, playerCount, playerSum, houseSum, userInput);

		//Check if "Sum" is greater than 21;
		if (playerSum > 21)
		{
			cout << "You lost, get wrecked son!\n";
			system("pause");
			return 0;
		}

		//House decision, Hit or Stand
		houseChoice(Deck, House, topCard, houseCount, houseSum, playerSum, houseInput);

		//Check if "Sum" is greater than 21;
		if (houseSum > 21)
		{
			cout << "Good job, you actually won! (You cheated didn't you)\n";
			system("pause");
			return 0;
		}

		if ((userInput == 's' || userInput == 'S') && houseInput == 's')
		{
			if (playerSum > houseSum)
			{
				cout << "Good job, you actually won! (You cheated didn't you)\n";
				system("pause");
				return 0;
			}
			else if (playerSum < houseSum)
			{
				cout << "You lost, get wrecked son!\n";
				system("pause");
				return 0;
			}
			else
			{
				cout << "You have tied... how anticlimactic.\n";
				system("pause");
				return 0;
			}
		}
	}
}
