// Assignment #3: DO NOT MODIFY THIS FILE

#ifndef _CACHE_H_
#define _CACHE_H

extern uint8_t ram[RAM_SIZE];

#define CACHE_SIZE 256
#define NUM_CACHE_BLOCKS CACHE_SIZE/4

#define ADDR_BIT_WIDTH 32
#define G_BIT_WIDTH 2

void cache_init(void);
uint32_t cache_read(uint32_t addr);
void cache_write(uint32_t addr, uint32_t value);

uint32_t num_cache_hit;
uint32_t num_cache_miss;

#endif
