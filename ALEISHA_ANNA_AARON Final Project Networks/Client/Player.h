#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//////////////////////////////////////////////////////////
// This class represent a Player
class Player {

private:
	int player_book_score;
	int player_hand_score;
	int put_down_score;
	vector<string> Hand;
	vector<string> Foot;
	vector<string> Downed_Cards;
	int books;
	int books_to_end;
	vector<string> cards_are_books;
	bool IN_HAND;
	bool score_reached;
	bool cards_down;
	map<string, int> point_system;

public:

	Player() {
		this->books = 0;
		this->books_to_end = 4; // Number of books needed to win
		this->put_down_score = 150; // Score needed to put down cards
		this->player_hand_score = 0;
		this->score_reached = false; // Assumes that the player does not the score needed to put down cards
		this->cards_down = false; // Assumes that the player does not have cards put down
		this->IN_HAND = true; // Assumes that the player starts in their Hand

							  // This map contains the scores for each individual card
		this->point_system["Ace"] = 20;
		this->point_system["Two"] = 5;
		this->point_system["Three"] = 5;
		this->point_system["Four"] = 5;
		this->point_system["Five"] = 5;
		this->point_system["Six"] = 5;
		this->point_system["Seven"] = 5;
		this->point_system["Eight"] = 10;
		this->point_system["Nine"] = 10;
		this->point_system["Ten"] = 10;
		this->point_system["Jack"] = 10;
		this->point_system["Queen"] = 10;
		this->point_system["King"] = 10;
	}

	void set_Hand(vector<string> hand) { // Updates what cards are in the player's Hand
		this->Hand = hand;
		calculate_score(this->Hand);
	}

	void set_Foot(vector<string> foot) { // Updates what cards are in the player's Foot
		this->Foot = foot;
		calculate_score(this->Foot);
	}

	void set_downed_cards(vector<string> new_down)
	{
		this->Downed_Cards = new_down;
	}

	map<string, int> get_point_system() // Returns the map that contains the card score values 
	{
		return this->point_system;
	}

	vector<string> get_cards() // Returns either the player's Hand or Foot, depending on the IN_HAND boolian variable
	{
		if (IN_HAND)
			return this->Hand;
		else if (!IN_HAND)
			return this->Foot;
	}

	vector<string> get_all_cards_down() // Returns all the cards that the player has put down
	{
		return this->Downed_Cards;
	}

	int get_number_of_books() // Returns the number of books that the player has
	{
		return this->books;
	}

	void entered_FOOT() { // Indicates that the player has empyted their Handf and entered their Foot
		this->IN_HAND = false;
	}

	void reached_score() // Indictaes that the layer has reached the score requirment for putting down cards
	{
		this->score_reached = true;
	}

	bool get_score_status() // Gets the current boolian status for whther or not the player has reacch the score requirment for putting down cards
	{
		return this->score_reached;
	}

	int get_hand_score() // Returns what the current score the player has in their hand, prior to putting down cards
	{
		return this->player_hand_score;
	}

	bool get_current_cards_status() { // This will return the bool that determines of the player is in their Hand or Foot
		return this->IN_HAND;
	}

	bool get_cards_down() // This will return a bool that will show whether or not the player has put down cards
	{
		return this->cards_down;
	}

	void cards_put_down() // this function will show that the player has put down cards
	{
		this->cards_down = true;
	}

	void update_player_hand_score(int updated_score) // This will update the hand score of a player whenver the player views their cards
	{
		this->player_hand_score = updated_score;

		// This will call the function if the score of the Player hand is greater than the score requirement
		if (this->player_hand_score >= this->put_down_score && !get_score_status() && get_cards_down())
			reached_score();
	}

	void draw_from_deck(string cards) { // This function will return the player's current cards, either Hand or Foot
		if (get_current_cards_status())
			this->Hand.push_back(cards);
		else if (!get_current_cards_status())
			this->Foot.push_back(cards);
	}

	void calculate_score(vector<string> target_cards) { // This function will calculate the score in teh Player Hand or Foot
		vector<string> counted_cards;
		vector<int> card_counts;
		int count;
		int score = 0;

		//////////////////////////////////////////////////////////////////
		// This loop will iterate through the player's cards, counting them to establish how many point the player has currently
		for (int i = 0; i < target_cards.size(); i++)
		{
			count = 0;
			////////////////////////////////////////////////////
			// This loop will count the occurances of the current card in the outer loop 
			for (int j = 0; j < target_cards.size(); j++)
			{
				if (target_cards[i] == target_cards[j]) // If a match occurs, it will increment 'count' by 1
					count++;
			}
			//////////////////////////////////////////////////

			if (count >= 3) // Occurs if a card appears more than 3 times
			{
				counted_cards.push_back(target_cards[i]); // Svaes the crd tthat appeared more than 3 times
				card_counts.push_back(count); // Saved the number of occurances
			}
		}
		//////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////
		// This loop will get the score total for all cards that occur more than 3 times
		for (int i = 0; i < counted_cards.size(); i++)
		{
			score += this->point_system[counted_cards[i]];
		}
		/////////////////////////////////////////////////////

		update_player_hand_score(score); // This will update the player's Hand score
	}

	void put_down(vector<string> current_cards) // This function is responsible for the player putting cards down from the Hand or Foot 
	{
		int done_loop;
		int user_input;
		string current_card;
		vector<string> selected_cards;
		vector<string> left_over_cards;

		if (!get_score_status()) // This occurs if the player does not have the score requirement fulfilled (Hand only)
		{
			////////////////////////////////////////////////
			// This loop will output the card in the Player Hand and the indexes they are in within the vector
			for (int i = 0; i < this->Hand.size(); i++)
			{
				cout << this->Hand[i] << ":\t" << i << endl;
				if (i == this->Hand.size()) // This will output the value that will end the future loop
				{
					cout << "DONE:\t" << (i + 1) << endl;
					done_loop = (i + 1);
				}
			}
			/////////////////////////////////////////////////

			///////////////////////////////////////////////////
			// This loop will get input from the user about which cards they wish to put down
			//		The loop will end when the value shown in the preivous loop
			do {
				cout << "Which cards do you want to put down?" << endl;
				cin >> user_input;

				if (user_input < 0 || user_input > done_loop) // This will occur if the user in[uts a value that is not shown above
					cout << "Invalid Input. Try again." << endl;
				else
					selected_cards.push_back(this->Hand[user_input]); // Saves the card for which the user input represents
			} while (user_input != done_loop);
			//////////////////////////////////////////////

			calculate_score(selected_cards); // This will calculate the score of the cards that the player has choosen to put down

			if (get_score_status()) // This will occur if the player has enough points to put down cards
			{
				// This loop will put the selected cards in a vector that will hold all downed cardss for the player
				for (int i = 0; i < selected_cards.size(); i++)
					Downed_Cards.push_back(selected_cards[i]);
				cards_put_down();
			}

			else // This will occur if the selected card do not meet the score requirement to put down cards
			{
				cout << "You do not have enough points." << endl;
				cout << "Points Required:\t" << this->put_down_score << endl;
			}
		}

		else if (get_cards_down()) // This will occur if the player already put down cards
		{
			vector<string> current_CARDS;
			current_CARDS = get_cards();

			///////////////////////////////////////////////////
			// This loop will output the cards that are in teh Player Hand or Foot
			for (int i = 0; i < current_CARDS.size(); i++)
			{
				cout << current_CARDS[i] << "\t" << i << endl;
				if (i == current_CARDS.size()) // This will output the value that will end the upcoming loop
				{
					cout << "DONE:\t" << (i + 1) << endl;
					done_loop = (i + 1);
				}
			}
			/////////////////////////////////////////////////
			// This loop will get input from the user about which cards they wish to put down
			//		The loop will end when the value shown in the preivous loop
			do {
				cout << "Which cards do you want to put down?" << endl;
				cin >> user_input;

				if (user_input < 0 || user_input > done_loop) // This will occur if the user in[uts a value that is not shown above
					cout << "Invalid Input. Try again." << endl;
				else
					selected_cards.push_back(current_CARDS[user_input]);
			} while (user_input != done_loop);
			////////////////////////////////////////////////

			// This will send the player selected cards to the function responsible for putting down cards types that have already been put down
			selected_cards = cards_already_down(selected_cards);
			// This will send the player selected cards to the function responsible for putting down cards types that haven't been put down yet
			selected_cards = put_down_new_cards(selected_cards);

			/////////////////////////////////////////////////////////////
			// This loop will create a new vector that will take the remaining, non 'SKIP' cards, and make them the new Hand or Foot
			for (int i = 0; i < selected_cards.size(); i++)
			{
				if (selected_cards[i] != "SKIP")
					left_over_cards.push_back(selected_cards[i]);
			}
			//////////////////////////////////////////////////////////

			make_books(); // Calls the function responaisble for determing if the player has any books
		}

		if (this->IN_HAND && this->Hand.size() >= 0) // If the player does not empty their Hand, the cards they have left will be set as their Hand
			set_Hand(left_over_cards);
		else if (!this->IN_HAND && this->Foot.size() > 0) // If the player does not empty their Foot, the cards they have left will become their new Foot
			set_Foot(left_over_cards);

		if (this->IN_HAND && this->Hand.size() == 0) // if the player emptys their Hand, they will enter their Foot
			entered_FOOT();
	}

	// This function is repsonsible for putting down card types that have already been put down 
	vector<string> cards_already_down(vector<string> selected_cards)
	{
		int count;
		bool already_down;
		bool already_processed;
		vector<string> already_down_cards;
		vector<int> old_card_counts;
		vector<string> leftover_hand;

		////////////////////////////////////////////////////////
		// This loop is for determing if any of the selected cards are of the smae type as cards that have already been put down
		for (int i = 0; i < selected_cards.size(); i++)
		{
			count = 0;
			already_down = false;
			already_processed = false;

			/////////////////////////////////////////////////////////
			// This loop will check to see if any of the previously checked cards have duplicates within the vector 
			for (int g = 0; g < already_down_cards.size(); g++)
			{
				if (already_down_cards[g] == selected_cards[i]) // This occurs if a duplicate is found
				{
					already_processed = true; // Duplicate found
					break; // End the loop
				}
			}
			///////////////////////////////////////////////////////

			if (already_processed) // Occurs if a duplicate was found
				continue; // Skips the current iteration of the outer loop

						  //////////////////////////////////////////////////////////
						  // This loop will check the cards that have been put down with the selected cards to see if there are matchs
			for (int j = 0; j < this->Downed_Cards.size(); j++)
			{
				if (selected_cards[i] == this->Downed_Cards[j]) // Occurs if a match has been found
				{
					if (!already_down)
						already_down = true;
					count++; // Counts how many times a match has occured
				}
			}
			////////////////////////////////////////////////////////

			if (already_down) // Occurs if a match was found
			{
				already_down_cards.push_back(selected_cards[i]); // Saves the card type that has already been comfirmed for putdown
				old_card_counts.push_back(count);
			}
		}
		/////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////
		// This loop will put cards down, which will add on to ones that are of the same type
		for (int i = 0; i < already_down_cards.size(); i++)
		{
			for (int j = 0; j < old_card_counts[j]; j++) // Adds comfirmed cards to the cards already put down
				this->Downed_Cards.push_back(already_down_cards[i]);
		}
		//////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// This section is for removing the cards that have been put down
		for (int i = 0; i < already_down_cards.size(); i++)
		{
			///////////////////////////////////////////////////////////
			// This is for determing which cards have been put down
			for (int j = 0; j < selected_cards.size(); j++)
			{
				if (selected_cards[j] == already_down_cards[i]) // If a card was put down it is replaced with 'SKIP'
					selected_cards[j] = "SKIP"; // Replacing the value of a card that has been put down
			}
			///////////////////////////////////////////////////////////
		}
		/////////////////////////////////////////////////////////////

		leftover_hand = selected_cards;

		return leftover_hand;
	}

	// Tis function is for putting down cards whoose types are different than the ones that have been put down preivously
	vector<string> put_down_new_cards(vector<string> selected_cards)
	{
		// This will determine if new card types have enough copies to be put down
		int count;
		bool already_counted;
		vector<string> enough_cards;
		vector<int> card_counts;
		vector<string> leftover_cards;

		/////////////////////////////////////////////////////////////////
		// This loop will count how many times the same card appears in the cards selected by the player 
		for (int i = 0; i < selected_cards.size(); i++)
		{
			if (selected_cards[i] == "SKIP")
				continue;
			count = 0;
			already_counted = false; // Assumes that the current card is a new card
			for (int q = 0; q < enough_cards.size(); q++) // This loop will determine if the current card has already been counted
			{
				if (enough_cards[q] == selected_cards[i]) // This occurs a card is matched with one that has already been counted
				{
					already_counted = true; // Shows that the current card has already been counted
					break; // Ends the loop
				}
			}

			if (already_counted) // This occurs if a card was found to have already been counted 
				continue; // Skips the current iteration of the outer loop

						  ///////////////////////////////////////////////////////
						  // This loop will count the number of times that a card appears in the cards that the player has salected to put down 
			for (int j = 0; j < selected_cards.size(); j++)
			{
				if (selected_cards[i] == selected_cards[j]) // If a match has been found
					count++;
			}
			//////////////////////////////////////////////////////

			if (count >= 3) // Occurs if 3 or more matchs have been found
			{
				enough_cards.push_back(selected_cards[i]); // Saves the card that meets the count requirment 
				card_counts.push_back(count); // Saves the number of times that the card appears in the selected cards
			}
		}
		/////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////
		// This loop will add new card types to the cards that are already down
		for (int i = 0; i < enough_cards.size(); i++)
		{
			for (int j = 0; j < card_counts[i]; j++) // Puts down the new cards the number of times that it appears in the Player selected cards 
				this->Downed_Cards.push_back(enough_cards[i]);
		}
		///////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		// This is for determing which cards have been put down
		for (int i = 0; i < enough_cards.size(); i++)
		{
			///////////////////////////////////////////////////////
			// This loop will attempt to match cards that have been put down with the cards that the player selected earlier
			for (int j = 0; j < selected_cards.size(); j++)
			{
				if (enough_cards[i] == selected_cards[j]) // Occurs if a card was put down
					selected_cards[j] = "SKIP"; // Replaces the value with 'SKIP'
			}
			/////////////////////////////////////////////////////////
		}
		////////////////////////////////////////////////////////////

		leftover_cards = selected_cards;

		return leftover_cards;
	}

	void make_books() // This is in charge of determining if a player already has enough cards currently put down to make a book
	{
		int count;
		bool already_booked;

		//////////////////////////////////////////////////////////////
		// This loop will count the cards that have been put down to see if there are enough to make a book
		for (int i = 0; i < this->Downed_Cards.size(); i++)
		{
			count = 0;
			already_booked = false;
			for (int q = 0; q < cards_are_books.size(); q++) // This loop will check to see if any cardss have already been added as a book
			{
				if (this->Downed_Cards[i] == this->cards_are_books[q]) // If a card type has already been added as a book 
				{
					already_booked = true;
					break;
				}
			}

			if (already_booked) // If a card type has already be added as a book
				continue;

			/////////////////////////////////////////////////////////////////
			// This loop will count the occurences of each card type in the cardfs that have been put down  
			for (int j = 0; j < this->Downed_Cards.size(); j++)
			{
				if (this->Downed_Cards[i] == this->Downed_Cards[j]) // If a match has been found
					count++;
			}
			///////////////////////////////////////////////////////////////////

			if (count >= 7) // Occurs if a card type appears 7 times or more
				this->cards_are_books.push_back(this->Downed_Cards[i]); // Add the card type to the list of books collected
		}
		///////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////
		// This loop will elimia=nat ecard that havebeen added as a book from the cards that have been put down
		for (int j = 0; j < this->cards_are_books.size(); j++)
		{
			for (int i = 0; i < this->Downed_Cards.size(); i++)
			{
				// Occurs if a match is found between cards that have been put down and cards that have been added as a book
				if (this->cards_are_books[j] == this->Downed_Cards[i])
					this->Downed_Cards[i] = "SKIP";
			}
		}
		//////////////////////////////////////////////////////////////////////

		vector<string> new_down_cards; // This vector will act as a placeholder for the cards that are down
									   //////////////////////////////////////////////////////////////////
									   // This loop will skip over cards that have the value of 'SKIP' so that the Downed_Cards vector will have only caards that are not books
		for (int i = 0; i < this->Downed_Cards.size(); i++)
		{
			if (this->Downed_Cards[i] != "SKIP") // Occurs
				new_down_cards.push_back(this->Downed_Cards[i]);
		}
		//////////////////////////////////////////////////////////////////

		set_downed_cards(new_down_cards); // Sets the Down_cards vector to the vector that contains non-'SKIP' values
	}

	string discard() // This function will be reponsible for the player discarding one card from the Hand or Foot
	{
		bool discard_fail = false;
		int user_input;
		string discard;
		vector<string> placeholder;
		if (get_current_cards_status()) // This will occur if the player is stil in their Hand
		{
			for (int i = 0; i < this->Hand.size(); i++) // This loop will output the cards in their Hand and the card indexes within the vector
				cout << this->Hand[i] << ":\t" << i << endl;

			cout << "\nWhich card are you going to discard?" << endl;
			cin >> user_input; // This will ask the user which card the player wants to discard
			discard = this->Hand[user_input];

			for (int i = 0; i < this->Hand.size(); i++) // This loop will create a new vector without the discarded card
			{
				if (this->Hand[i] != discard)
					placeholder.push_back(this->Hand[i]);
			}

			set_Hand(placeholder); // This sets the Hand to the vector without the card that was discarded
		}

		else if (!get_current_cards_status()) // This will occur if the player is in their Foot
		{

			if (!this->IN_HAND && this->Foot.size() == 1) // This will display a message that the player has one card left in their Foot
			{
				if (this->books > this->books_to_end)
					cout << "You can go out and win!" << endl;

				else
				{
					cout << "YOU FAILED! YOU SHOULD HAVE PLANNED AHEAD!" << endl;
					discard_fail = true;
					goto failure;
				}
			}

			for (int i = 0; i < this->Foot.size(); i) // This loop will display the card in the Player foot and their indexes within the vector
				cout << this->Foot[i] << ":\t" << i << endl;

			cout << "\nWhich card are you going to discard?" << endl;
			cin >> user_input; // gets input from the user to get/save the discard
			discard = this->Foot[user_input];

			for (int i = 0; i < this->Foot.size(); i++) // This loop will remve the discard card from the Player Foot
			{
				if (this->Foot[i] != discard)
					placeholder.push_back(this->Foot[i]);
			}

			set_Foot(placeholder); // Sets the Player Foot to the vector without the discard card
		}

		if (this->IN_HAND && this->Hand.size() == 0) // Will signalfy that the player has entered their Foot
			entered_FOOT();

	failure:
		if (discard_fail)
			discard.clear();

		return discard; // Returns the discarded cards
	}
};
///////////////////////////////////////////////////////////////

#endif