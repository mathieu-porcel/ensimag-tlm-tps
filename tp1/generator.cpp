#include "generator.h"

using namespace std;

void Generator::processus(void) {
	for (uint32_t i = 0; i < 2; i++) {
	    ensitlm::addr_t addr = 0x10000000 + 4*i;
	    ensitlm::data_t data = i;
	    initiator.write(addr, data);
	}
	for (uint32_t i = 0; i < 2; i++) {
	    ensitlm::addr_t addr = 0x10000000 + 4*i;
	    ensitlm::data_t data;
	    initiator.read(addr, data);
	    if (data != i) {
	        cout << "Read error" << endl;
	    }
	}
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
    SC_THREAD(processus);
}

