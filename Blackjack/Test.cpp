#include <iostream>
#include <array>
#include <ctime>
#include <string>
using namespace std;

#define MAX_SUITS 4
#define MAX_RANKS 13
#define MAX_CARDS_DECK 52

enum CardSuit
{
	SUIT_CLUBS,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_SPADES,
};

enum CardRank
{
	RANK_2,
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
	RANK_ACE,
};

class Card
{
public:
	CardRank rank;
	CardSuit suit;
};

int cardToInt(Card card)
{
	switch (card.rank)
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

void cardToString(Card card)
{
	switch (card.rank)
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

	switch (card.suit)
	{
	case SUIT_CLUBS:	cout << "Clubs"; break;
	case SUIT_DIAMONDS:	cout << "Diamonds"; break;
	case SUIT_HEARTS:	cout << "Hearts"; break;
	case SUIT_SPADES:	cout << "Spades"; break;
	}
}

class Deck
{
public:

	int count = 0;
	array<Card, 52> c_Deck;

	void fillDeck(array<Card, 52> &c_deck)
	{
		int count = 0;
		for (int suit = 0; suit < MAX_SUITS; ++suit)
			for (int rank = 0; rank < MAX_RANKS; ++rank)
			{
				c_deck[count].suit = static_cast<CardSuit>(suit);
				c_deck[count].rank = static_cast<CardRank>(rank);
				++count;
			}
	}

	void shuffleDeck(array<Card, 52> &c_deck)
	{
		for (int count = 0; count < MAX_CARDS_DECK; count++)
			swap(c_deck[count], c_deck[rand() % 52]);
	}
};

class CardSet
{
public:

	int count = 0;
	int sum = 0;
	bool choice = true;
	array<Card, 11> cards;

	void draw(Deck Deck)
	{
		swap(cards[count], Deck.c_Deck[Deck.count]);
		cardToString(Deck.c_Deck[Deck.count]);
		cout << " was drawn.";
		sum += cardToInt(cards[count]);
		cout << "\nThe sum is " << sum << endl;
		count++;
		Deck.count++;
	}

	void makeChoice(Deck Deck)
	{
		char placeHolder;
		cout << "Do you want to hit or stand? (H or S) ";
		cin >> placeHolder;

		if (placeHolder == 'H' || 'h')
			choice = true;
		else if (placeHolder == 'S' || 's')
			choice = false;

		if (choice)
			draw(Deck);
	}

	void houseChoice(Deck Deck, CardSet Player)
	{
		if (sum <= 16 || sum < Player.sum)
			choice = true;
		else
			choice = false;

		if (choice)
			draw(Deck);

	}
};

int mainTest()
{
	Deck Deck;
	CardSet Player;
	CardSet House;

	Deck.fillDeck(Deck.c_Deck);
	Deck.shuffleDeck(Deck.c_Deck);

	Player.draw(Deck);
	House.draw(Deck);
	Player.draw(Deck);
	House.draw(Deck);

	while (Player.choice && House.choice)
	{
		if (Player.choice)
			Player.makeChoice(Deck);

		//Loss Condidtion
		if (Player.sum > 21)
		{
			cout << "I got caught, I died, and I was put in jail!\n";
			return 0;
			system("pause");
		}

		if (House.choice)
			House.houseChoice(Deck, Player);

		//Win Condidtion
		if (House.sum > 21)
		{
			cout << "Catch me, kill me, and put me in jail!\n";
			return 0;
			system("pause");
		}
	}

	//Loose Condidtion
	if (House.sum > Player.sum)
	{
		cout << "Neverluckybeberage...\n";
		return 0;
		system("pause");
	}
	//Win Condidtion
	else if (House.sum < Player.sum)
	{
		cout << "Chess! na--na-na--na---na--na-na-na-na-na\n";
		return 0;
		system("pause");
	}
	//Tie Condidtion
	else
	{
		cout << "Seriously, you tied?\n";
		return 0;
		system("pause");
	}
}

