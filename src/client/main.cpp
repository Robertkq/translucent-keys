#include "client.h"



int main()
{
	client Client(&validation_function);
	

	Client.run();



	return 0;
}