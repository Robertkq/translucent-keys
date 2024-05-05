#include "server.h"

int main() {
    Server master{60000, &validation_function};
    master.StartServer(); // blocking
    master.StopServer();  // currently unreachable

    return 0;
}