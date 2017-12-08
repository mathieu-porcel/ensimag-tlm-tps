#include "ensitlm.h"
#include "bus.h"

SC_MODULE(Generator) {
    ensitlm::initiator_socket<Generator> initiator;
    void processus(void);
    SC_CTOR(Generator);
};

