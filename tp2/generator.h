#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"
#include "bus.h"
#include "systemc.h"

SC_MODULE(Generator) {
	ensitlm::initiator_socket<Generator> initiator;
	void processus(void);

	sc_signal<bool, SC_MANY_WRITERS> irq_signal;
	sc_event irq_event;
	void display_irq(void);

	SC_CTOR(Generator);
};

#endif

