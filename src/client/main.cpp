#include "client.h"

int main()
{
	Client client(&validation_function);
	std::cout << "Connecting to server...\n";
	if (!client.Connect("86.125.231.183", 60000))
	{
		std::cout << "Failed connecting to server!\n";
		return 1;
	}
	std::cout << "Successfuly connected to server!\n";

	while (true)
	{

	}

	std::cout << "Disconnecting from server...\n";
	client.Disconnect();

	return 0;
}