#include "nameTaker.h"

std::string windowsName()
{
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(buffer);
    GetComputerNameA(buffer, &size);
    return std::string(buffer);
}