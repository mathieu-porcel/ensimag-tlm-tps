#ifndef CONST_H
#define CONST_H

#include "LCDC.h"
#include "ROM.h"

#define IMG_SIZE		(LCDC::kWidth * LCDC::kHeight)

#define LDLC_BUS_ADDR   0x20000000

#define MEMORY_BUS_ADDR	0x10000000
#define MEMORY_SIZE		(IMG_SIZE + 10000)

#define ROM_BUS_ADDR	0x30000000

#endif
