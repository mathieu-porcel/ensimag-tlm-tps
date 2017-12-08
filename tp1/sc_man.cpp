#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"

int sc_main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	
	Generator g1("Generator1");
	Bus b("Bus");
	Memory m("Memory", 8);
	
	// Connect
	g1.initiator.bind(b.target);
	b.initiator.bind(m.target);
	
	// Map memory
	b.map(m.target, 0x10000000, 0x100000FF);
	
	// Start simu
	sc_core::sc_start();
	return 0;
}

