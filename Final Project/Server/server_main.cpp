#include <windows.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Socket.h"

using namespace std;

const int PORT1 = 50001;
const int PORT2 = 50002;
const int PORT3 = 50003;


bool go_again()
{
	char resp[100];

	cout << "Play again? (yes/no): ";
	cin >> resp;

	return strcmp(resp, "yes") == 0;
}


int done(const string message)
{
	Socket::Cleanup();
	cout << message;
	cin.get();
	exit(0);
}

int main()
{
		bool again = true;

		// Loop for connecting (VECTORS)
	//	vector<Socket> players;




		while (again)
		{				
			if (!Socket::Init()) {
				cerr << "Fail to initialize WinSock!\n";
				return -1;
			}


			Socket server1("tcp");
			Socket server2("tcp");
			Socket server3("tcp");

			vector<Socket> servers;

			servers.push_back(server1);
			servers.push_back(server2);
			servers.push_back(server3);

			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					if (!servers[i].sock_bind("", PORT1))
					{
						stringstream str;
						str << "Could not bind to port " << PORT1;
						done(str.str());
					}
					cout << PORT1 << " Is okay" << endl;
				}

				if (i == 1)
				{
					if (!servers[i].sock_bind("", PORT2))
					{
						stringstream str;
						str << "Could not bind to port " << PORT2;
						done(str.str());
					}
					cout << PORT2 << " Is okay" << endl;
				}

				if (i == 2)
				{
					if (!servers[i].sock_bind("", PORT3))
					{
						stringstream str;
						str << "Could not bind to port " << PORT3;
						done(str.str());
					}
					cout << PORT3 << " Is okay" << endl;
				}

			}


			for (int i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					if (!servers[i].sock_listen(1))
					{
						done("Could not get socket to listen");
					}
					cout << "Server is now listening on port " << PORT1 << endl;
				}
				

				if (i == 1)
				{
					if (!servers[i].sock_listen(2))
					{
						done("Could not get socket to listen");
					}
					cout << "Server is now listening on port " << PORT2 << endl;
				}
				

				if (i == 2)
				{
					if (!servers[i].sock_listen(3))
					{
						done("Could not get socket to listen");
					}
					cout << "Server is now listening on port " << PORT3 << endl;
				}
			}




			Socket conn = server.sock_accept();

			cout << "A client just connected to me!\n";
			

			conn.msg_send("How many players?");

			string msg = conn.msg_recv();
			cout << msg << endl;

	


			again = go_again();







			//system("pause");

	}


	//done("Press enter to exit");



	return 0;

} // END MAIN




