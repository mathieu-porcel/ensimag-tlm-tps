#include "generator.h"
#include "const.h"
#include "LCDC_registermap.h"

using namespace std;

void Generator::processus(void) {
	static unsigned int offset = 0;

	// Init LCDC
	initiator.write(LDLC_BUS_ADDR + LCDC_ADDR_REG, MEMORY_BUS_ADDR);
	initiator.write(LDLC_BUS_ADDR + LCDC_START_REG, 1);

	while (true) {
		for (unsigned int i = 0; i < ROM_SIZE; i += 4) {
			// Read ROM
			ensitlm::data_t rom_data;
			initiator.read(ROM_BUS_ADDR + i, rom_data);

			// Change pixel quantization
			ensitlm::data_t lcdc_data2 =	((rom_data & 0x0000000F) << 4) |
											((rom_data & 0x000000F0) << 8) |
											((rom_data & 0x00000F00) << 12) |
											((rom_data & 0x0000F000) << 16);
			ensitlm::data_t lcdc_data1 =	((rom_data & 0x000F0000) >> 12) |
											((rom_data & 0x00F00000) >> 8) |
											((rom_data & 0x0F000000) >> 4) |
											((rom_data & 0xF0000000) >> 0);

			// Write screen memory with translation offset
			initiator.write(MEMORY_BUS_ADDR + ((2 * i + 0) + offset * LCDC::kWidth) % IMG_SIZE, lcdc_data1);
			initiator.write(MEMORY_BUS_ADDR + ((2 * i + 4) + offset * LCDC::kWidth) % IMG_SIZE, lcdc_data2);
		}

		// Update offset
		offset = (offset + 1) % LCDC::kHeight;
	
		// Wait interrupt
		wait(irq_event);
	}
}

void Generator::display_irq() {
	// IRQ acknowledgement
	initiator.write(LDLC_BUS_ADDR + LCDC_INT_REG, 0);

	cout << "Generator: receive display interrupt " << endl;
	irq_event.notify(100, SC_MS);
}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(processus);

	SC_METHOD(display_irq);
	sensitive << irq_signal.posedge_event();
}

