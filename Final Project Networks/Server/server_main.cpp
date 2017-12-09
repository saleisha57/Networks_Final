#include "base.h"
#include "Manager.h"

using namespace std;

const int PORT1 = 50001;


// Function to ask about going again.
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

		// Create two sockets called 'server1' and 'conn'.
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

		// Code Snippet Below Source: 'relay_server.cpp' which was written by Kent Jones.
		// Set up threads that will manage the player threads.
		do {
			conn = server1.sock_accept();                // Waiting to receive a connection. 
			cout << "Connection made \n";                // Display when a connection is set up.
			Manager *m = new Manager(conn);              // Create a manager object to use with the thread.
			thread *thr = new thread(*m);                // Create a thread.
			//thr->detach();                               // Detach the thread.						
		} while (true);                                  // Do while loop.


														 // Citations in documentation

														 // Call the go again function.
		again = go_again();


	}


	done("Press enter to exit");



	return 0;

} // END MAIN