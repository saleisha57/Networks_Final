#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////
// This class will represent the main deck and the discard pile on the server
class Deck {
private:
	const int cards_in_deck = 13;
	const int total_cards = 52;
	string Cards[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" }; // The different cards in a deck (no Jokers)
	vector<string> Final_DECK;
	vector<string> single_DECK;
	vector<string> Discard_pile;

public:
	Deck() // This will create a new deck when a new Deck object is created
	{
		/////////////////////////////////////////
		// This loop will create a normal deck of cards
		for (int i = 0; i < cards_in_deck; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				single_DECK.push_back(Cards[i]);
			}
		}
		///////////////////////////////////////////

		//////////////////////////////////////////
		// This loop will combine 8 copies of a normal deck of cards together into one big Final_DECK
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < single_DECK.size(); j++) // Adding a copy of a normal 52 card deck (without Jokers)
			{
				Final_DECK.push_back(single_DECK[j]);
			}
		}

		/////////////////////////////////////////////////////////
		// This section is repsonisble for shuffling the cards in Final_DECK into a psuedo random order 
		srand(unsigned(time(NULL)));
		string content_save;
		int save_index = 0;
		int x = 0;
		int y = rand() % 15 + 5;

		for (int i = 0; i < y; i++) // This loop will run a random number of times, depending on the value of y
		{
			for (int i = 0; i < 5000; i++) // This loop will run for 500 iterations to ensure that each card is moved several times
			{
				x = rand() % Final_DECK.size();
				content_save = Final_DECK[x];
				save_index = x;
				x = rand() % Final_DECK.size();

				Final_DECK[save_index] = Final_DECK[x];
				Final_DECK[x] = content_save;
			}
		}
		/////////////////////////////////////////////////////////
	}

	vector<string> get_DECK() { // this finction will return the deck for the main.cpp page
		return this->Final_DECK;
	}

	vector<string> get_discard_pile() { // This will return the discard pile for the player to get cards
		return this->Discard_pile;
	}

	void add_discard(string discard_card) { // This will add one card from the player to the discard pile
		this->Discard_pile.push_back(discard_card);
	}

	vector<string> draw_from_discard_pile() // This will allow for the player to draw the top 5 cards in the disacard pile
	{
		vector<string> discard_cards;
		for (int i = Discard_pile.size(); i > (Discard_pile.size() - 4); i--)
			discard_cards.push_back(Final_DECK[i]);
		return discard_cards;
	}

	vector<string> show_top_five_cards() // This will show the top five cards that are in the discard pile
	{
		vector<string> top_five;
		for (int i = Discard_pile.size(); i > (Discard_pile.size() - 4); i--)
			top_five.push_back(Discard_pile[i]);
		return top_five;
	}
};

#endif