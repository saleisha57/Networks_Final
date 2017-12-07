#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Socket.h"
#include<string>
#include <iostream>

using namespace std;

class Player
{
public:
	Player(Socket *sock)
	{
		this->sock = sock;
	}

	void operator()() {
		string msg;
		do {
			msg = sock->msg_recv();
		} while (msg != "");		
	}

private:
	Socket *sock;

};

#endif