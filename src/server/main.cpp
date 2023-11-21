#include "server.h"



int main()
{
	Server master{ 60000, &validation_function };
	std::cout << "Starting server...\n";
	if (!master.Start())
	{
		std::cerr << "Server failed start up!\n";
		return 1;
	}
	std::cout << "Server started successfuly!\n";
	while (true)
	{
		master.Update();
	}
	std::cout << "Stopping server...\n";
	master.Stop();
	return 0;
}