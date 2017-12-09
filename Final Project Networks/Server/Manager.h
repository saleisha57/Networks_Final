#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "base.h"
#include "Deck.h"

/**
Function class for execution in each thread spawned for a connection
@author: Ed Walker
*/
class Manager {
private:
	Socket *player;	// Socket for which this thread is responsible

	Deck DECK;
	vector<string> the_deck = DECK.get_DECK(); // Retrieves the deck from the class in the header file
	vector<string> player_hand;
	vector<string> player_foot;
	vector<string> drawed_cards;
	vector<string> top_discard_cards;
	map<string, int> point_rules;
	//std::string Name;		// Name of the person connecting

	static mutex player_lock;	// Global static lock for friends list
	static list<Socket *> friends_list; // Global static keeping track of all friends

	void send_to_all_friends(std::string msg) {
		// Step 3: Add code to send to all friends
		std::lock_guard<std::mutex> lk(player_lock);

		//std::string send_msg = Name + ": " + msg;

		list<Socket *>::iterator it;
		for (it = friends_list.begin(); it != friends_list.end(); ++it) {
			Socket *peer = *it;
			if (player != peer) {
				peer->msg_send(msg);
			}
		}
	}

	void add_listener() {
		// Step 1: Add code to manage a listener here
		lock_guard<std::mutex> lk(player_lock);
		friends_list.push_back(player);
	}

	void remove_listener() {
		// Step 2: Add code to remove a listener here
		lock_guard<std::mutex> lk(player_lock);
		for (auto it = friends_list.begin(); it != friends_list.end(); ++it) {
			// looking for entry in friends_list
			Socket *peer = *it;
			if (player == peer) { // found it!
				friends_list.erase(it); // remove it!
										//player->sock_close(); // close the socket
				delete player;
				break; // done
			}
		}
	}







public:
	Manager(Socket *socket) {
		player = socket;
		add_listener();
	}

	void operator()() {
		do {
			std::string msg;
			get_stuff();
			//player->msg_send("hello");
			msg = get_hand();
			player->msg_send(msg);
			msg = player->msg_recv();
			cout << msg << endl;
			/*msg = get_hand();
			player->msg_send(msg);*/

			

			/*for (int i = 0; i < 11; i++)
			{
				msg = get_hand()[i];
				player->msg_send(msg);
			}*/



			if (msg == "") {
				cout << "One listener exiting!\n";
				remove_listener();
				break; // client disconnected, time to go!
			}
			else {
				// send it to everyone!
				send_to_all_friends(msg);
			}
		} while (true);
	}


	void get_stuff()
	{
		for (int i = 0; i < 11; i++)
		{
			player_hand.push_back(the_deck[i]);
			cout << the_deck[i];
		}
		the_deck.erase(the_deck.begin(), the_deck.begin() + 11);

		for (int i = 0; i < 11; i++)
		{
			player_foot.push_back(the_deck[i]);
		}
		the_deck.erase(the_deck.begin(), the_deck.begin() + 11);
	}

	string get_hand()
	{
		string hand_h;

		for (int i = 0; i < 11; i++)
		{
			hand_h += player_hand[i];
		}

		return hand_h;
	}


	string get_foot()
	{
		string foot_h;

		for (int i = 0; i < 11; i++)
		{
			foot_h += player_foot[i];
		}

		return foot_h; 
	}




};

mutex Manager::player_lock;
list<Socket *> Manager::friends_list;

#endif