#ifndef _CHIBI_KERNEL_H
#define _CHIBI_KERNEL_H

#include <stdint.h>

void chibi_kernel_launch(uint32_t quanta);

void chibi_kernel_init(void);

uint8_t add_chibi_thread(void(*C_thread)(void));

#endif