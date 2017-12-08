#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "ROM.h"
#include "const.h"
#include "systemc.h"

int sc_main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    // Components
    Generator generator("Generator");
    Bus bus("Bus");
    Memory memory("Memory", MEMORY_SIZE);
    ROM rom("ROM");
    LCDC lcdc("LCDC", sc_time(1.0 / 25.0, SC_SEC));

    // Connect components to the bus
    generator.initiator.bind(bus.target);
    bus.initiator.bind(memory.target);
    bus.initiator.bind(rom.socket);
    bus.initiator.bind(lcdc.target_socket);
    lcdc.initiator_socket.bind(bus.target);
    lcdc.display_int.bind(generator.irq_signal);

    // Map bus addresses
    bus.map(memory.target, MEMORY_BUS_ADDR, MEMORY_SIZE);
    bus.map(rom.socket, ROM_BUS_ADDR, ROM_SIZE);
    bus.map(lcdc.target_socket, LDLC_BUS_ADDR, 3 * 0x04); // 3 registers of 32 bits

    // Start simu
    sc_core::sc_start();

    return 0;
}

