#include <windows.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "Manager.h"
#include "../Socket.h"

using namespace std;

const int PORT1 = 50001;


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

	while (again)
	{
		if (!Socket::Init()) {
			cerr << "Fail to initialize WinSock!\n";
			return -1;
		}


		Socket server1("tcp");
		Socket *conn;

		//SOCKET BIND
		if (!server1.sock_bind("", PORT1))
		{
			stringstream str;
			str << "Could not bind to port " << PORT1;
			done(str.str());
		}
		cout << PORT1 << " Is okay" << endl;

		// SOCKET LISTEN
		if (!server1.sock_listen(1))
		{
			done("Could not get socket to listen");
		}
		cout << "Server is now listening on port " << PORT1 << endl;

		//Socket conn = server.sock_accept();

		 // Source: relay_server which was written by Kent Jones.

		do {
			conn = server1.sock_accept(); // waiting to receive a connection 
			cout << "Got a chat connection! \n";
			Manager *server = new Manager(conn); // create the functor
			thread * thr = new thread(*server); // spawn the thread
			thr->detach();   // detach it since we don't need to wait on it
							 // Go back to accept a new connection now!!
		} while (true);




		/*do {
			Socket conn = server.sock_accept();
			cout << "Connection made";
			Manager *m = new Manager(conn);
			thread *thr = new thread(*m);
			thr->detach();
		} while (true);*/
		




		again = go_again();







		//system("pause");

	}


	//done("Press enter to exit");



	return 0;

} // END MAIN
