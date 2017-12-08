#include "ensitlm.h"
#include "bus.h"

SC_MODULE(Memory) {
	ensitlm::target_socket<Memory> target;
	
	tlm::tlm_response_status write(const ensitlm::addr_t addr, const ensitlm::data_t data);
	tlm::tlm_response_status read(const ensitlm::addr_t addr, ensitlm::data_t &data);
	
	ensitlm::data_t *storage;
	uint32_t size;
	
    Memory(sc_core::sc_module_name name, int size);
    ~Memory();
};

