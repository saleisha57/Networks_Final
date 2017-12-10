#include "base.h"
#include "Player.h"

const int PORT1 = 50001;

int done(const string message)
{
	Socket::Cleanup();
	cout << message;
	cin.get();
	exit(0);
}

// THE CLIENT: Connects to Server
int main()
{

	if (!Socket::Init()) {
		cerr << "Fail to initialize WinSock!\n";
		return -1;
	}

	// Step 1: Create a TCP socket
	Socket client1("tcp");

	// Connect to the IP of the host the server will be running on.
	cout << "Attempting to connect to 10.200.100.29" << PORT1 << endl;

	// Step 2: Connect to server
	if (!client1.sock_connect("10.200.100.29", PORT1))
	{
		done("could not connect to server");
	}
	cout << "Connected to 10.200.100.29:" << PORT1 << endl;

	// Set up the player items.
	vector<string> player_hand;
	vector<string> player_foot;
	bool in_hand;
	map<string, int> point_rules;

	Player Player1; // Creates a player
	Player1.set_Hand(player_hand); // Gives players their hand
	Player1.set_Foot(player_foot); // Gives players trehir foot
	point_rules = Player1.get_point_system(); // Gives players the scores that each card has
	//player_hand.clear();
	//player_foot.clear();

	// Recieve message from the server.
	string msg = client1.msg_recv();                              // Recieve a hand from the server.

	// Parsing the string from the server to retrieve the player's hand.
	int checkpoint = 0;
	string holder;
	char c;
	for (int i = 0; player_hand.size() < 11; i++)
	{
		for (int j = checkpoint; checkpoint < msg.length(); j++)  // Checkpoint used to distinguish where new card name starts.
		{
			if (msg[j] == '\n')
			{
				checkpoint = j;
				checkpoint++;
				break;
			}
			c = msg[j];                                          // Fill the holder string with characters until a newline is reached.
			holder += c;
		}
		player_hand.push_back(holder);                           // Push the holder string into the vector to store the value
		holder.clear();                                          // Clear the holder string.
	}

	Player1.set_Hand(player_hand);                               // Reset the players hand with the new one recieved from the server

	msg = client1.msg_recv();                                    // Recieve the foot from the server.

	// Parsing the string from the server to retrieve the player's foot.
	checkpoint = 0;
	holder = "";
	for (int i = 0; player_foot.size() < 11; i++)
	{
		for (int j = checkpoint; checkpoint < msg.length(); j++) // Checkpoint used to distinguish where new card name starts.
		{
			if (msg[j] == '\n')
			{
				checkpoint = j;
				checkpoint++;
				break;
			}
			c = msg[j];                                        // Fill the holder string with characters until a newline is reached.
			holder += c;
		}
		player_foot.push_back(holder);                         // Push the holder string into the vector to store the value
		holder.clear();                                        // Clear the holder string.
	}

	Player1.set_Foot(player_foot);                             // Reset the players foot with the new one recieved from the server

	//for (int i = 0; i < player_hand.size(); i++)
	//	cout << player_hand[i] << endl;

	


	int resp;
	in_hand = Player1.get_current_cards_status();                // Check if the player is in the hand or foot.

	string bool_num;
	if (in_hand)
		bool_num = "1";                                          // Set bool_num string to 1 if in hand.
	else if (!in_hand)
		bool_num = "0";                                          // Set bool_num string to 0 if in foot.

	client1.msg_send(bool_num);                                  // Send bool_num to the server.

	// Display menu, and get user response
	cout << "\n1 - View Cards" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "2 - Draw 2 Cards: " << endl;
	cout << "3 - Discard: " << endl;	
	cout << "--------------------------------------------" << endl;
	cin >> resp;

	if (resp == 1)
	{
		player_hand = Player1.get_cards(); // gets cards the player currently has
		vector<string> displayed; // Keeps track of card already outputted
		bool display; // Determine if a card has already been displayed
		int count;

		// Organizes output by card type, quantity, and total point for each card grouping
		cout << "Cards\t\tQuantity\tPoints\n" << endl;

		///////////////////////////////////////////////////
		// Will go through the players hand/foot to display what they have currently
		for (int i = 0; i < player_hand.size(); i++)
		{
			display = false; // Assume that a card has not been displayed yet
			for (int g = 0; g < displayed.size(); g++) // Will determine if a card has been displayed yet
			{
				if (displayed[g] == player_hand[i]) // Check each card with what has been displayed before
				{
					display = true;
					break; // end loop if a match has been found
				}
			}

			if (display)
				continue; // End current iteration of the loop if a match was found

			count = 0;
			for (int j = 0; j < player_hand.size(); j++) // This loop will count the occurance of each different card
			{
				if (player_hand[i] == player_hand[j]) // If a match has been found count will increase by 1
					count++;
			}
			displayed.push_back(player_hand[i]); // Stores the card into the vector for already displayed cards
			cout << player_hand[i] << "\t\t" << count << "\t\t" << (count * point_rules[player_hand[i]]) << endl; // Ouputs card info
		}
		/////////////////////////////////////////////////////////////////////
		cout << endl;
	}
	else
	{
		if (resp == 2)
		{
			if (bool_num == "1")                          // If in the hand
			{
				client1.msg_send(to_string(resp));        // Send the menu number to the server.

				msg = client1.msg_recv();                 // Recieve the new hand with drawn cards from the server.

				checkpoint = 0;
				holder = "";
				int size = player_hand.size();            // Set up a size integer to hold the size of the original hand.
				player_hand.clear();                      // Empty the original hand.
				for (int i = 0; i < (size+2); i++)
				{
					for (int j = checkpoint; checkpoint < msg.length(); j++) // Checkpoint used to distinguish where new card name starts.
					{
						
						if (msg[j] == '\n')
						{
							checkpoint = j;
							checkpoint++;
							break;
						}
						c = msg[j];
						holder += c;                                         // Fill the holder string with characters until a newline is reached.
					}
					player_hand.push_back(holder);	                         // Push the holder string into the vector to store the value
					holder.clear();                                          // Clear the holder string.
				}
				Player1.set_Hand(player_hand);
				for (int i = 0; i < player_hand.size(); i++)
					cout << player_hand[i] << endl;
			}

			

			else if (bool_num == "0")
			{
				client1.msg_send(to_string(resp));
				msg = client1.msg_recv();

				checkpoint = 0;
				holder = "";
				for (int i = 0; player_foot.size() < (player_foot.size() + 2); i++)
				{
					for (int j = checkpoint; checkpoint < msg.length(); j++) // Checkpoint used to distinguish where new card name starts.
					{
						if (msg[j] == '\n')
						{
							checkpoint = j;
							checkpoint++;
							break;
						}
						c = msg[j];
						holder += c;                                         // Fill the holder string with characters until a newline is reached.
					}
					player_foot.push_back(holder);                           // Push the holder string into the vector to store the value
					holder.clear();                                          // Clear the holder string.
				}

				Player1.set_Foot(player_foot);
				player_foot.clear();
			}
		}
		
	}

	system("pause");


	done("Press enter to exit");
	return 0;
}


