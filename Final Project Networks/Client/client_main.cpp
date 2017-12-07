#include "base.h"

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
	Socket client2("tcp");
	Socket client3("tcp");

	vector<Socket> players;

	players.push_back(client1);
	players.push_back(client2);
	players.push_back(client3);

	// 127.0.0.1 is the IP address for the local host
	cout << "Attempting to connect to 127.0.0.1" << PORT1 << endl;

	// Step 2: Connect to server
	for (int i = 0; i < 3; i++)
	{ // 10.200.100.46
		if (i == 0)
		{
	if (!client1.sock_connect("127.0.0.1", PORT1))
	{
		done("could not connect to server");
	}
	cout << "Connected to 127.0.0.1:" << PORT1 << endl;
		}
	else if (i == 1)
		{
			if (!players[i].sock_connect("127.0.0.1", PORT1))
			{
				done("could not connect to server");
			}

			cout << "Connected to 127.0.0.1:" << PORT1 << endl;
		}
	else if (i == 2)
		{
			if (!players[i].sock_connect("127.0.0.1", PORT1))
			{
				done("could not connect to server");
			}

			cout << "Connected to 127.0.0.1:" << PORT1 << endl;
		}		
	}

	for (int i = 0; i < 3; i++)
	{
		string msg = players[i].msg_recv();
		cout << msg << endl;
	}


	/*string msg = client1.msg_recv();
	cout << msg << endl;
	cin >> players;
	client1.msg_send(players);*/



	system("pause");


	done("Press enter to exit");
	return 0;
}
