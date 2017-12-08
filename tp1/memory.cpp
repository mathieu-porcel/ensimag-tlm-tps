#include "memory.h"

using namespace std;

tlm::tlm_response_status Memory::write(const ensitlm::addr_t addr, const ensitlm::data_t data) {
    cout << "[" << name() << "] write(" << addr << ", " << data << ")" << endl;
    if (addr % 4 == 0 && addr+3 < size) {
        storage[addr / 4] = data;
	    return tlm::TLM_OK_RESPONSE;
	} else {
	    cout << "Address error" << endl;
	    return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}
}

tlm::tlm_response_status Memory::read(const ensitlm::addr_t addr, ensitlm::data_t &data) {
    cout << "[" << name() << "] read(" << addr << ")" << endl;
	if (addr % 4 == 0 && addr+3 < size) {
        data = storage[addr / 4];
	    return tlm::TLM_OK_RESPONSE;
	} else {
	    cout << "Address error" << endl;
	    return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}
}

Memory::Memory(sc_core::sc_module_name name, int size) : sc_core::sc_module(name) {
    this->size = size;
    storage = new ensitlm::data_t[size / 4];
}

Memory::~Memory() {
   delete storage;
}

