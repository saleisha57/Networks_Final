#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <iostream>
#include <string>
#include "../Socket.h"
#include <list>

using namespace std;

// Inspired by "Service.h" which was written by Ed Walker

class Manager {
public:
	Manager(Socket *socket)
	{
		player = socket;
		add_player();
	}

	//list<Socket *> Manager::player_list;

	//void operator()()
	//{
	//	do {
	//		string msg = player->msg_rcv();
	//		send_to_all(msg);
	//	} while (true);
	//}


private:
	Socket *player;
	static list<Socket *> player_list;

	void add_player()
	{
		player_list.push_back(player);
	}


	void send_to_all(string msg)
	{
		list<Socket *>::iterator it;
		for (it = player_list.begin(); it != player_list.end(); ++it) {
			Socket *peer = *it;
			if (player != peer) {
				peer->msg_send(msg);
			}
		}


	//	list<Socket *>::iterator it;
	//	for (it = player_list.begin(); it != player_list.end(); ++it)
	//	{
	//		Socket *person;
	//		if (player != person)
	//			person->msg_send(msg);
	//	}
	}



	



};


#endif
