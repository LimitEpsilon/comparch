#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <assert.h>
#include "emu-rv32i.h"
#include "emu-cache.h"

// Address in 4-Way Set-associative Cache
//
//   TAG   |      INDEX                         | OFFSET
//         | log(NUM_CACHE_BLOCKS)-log(NUM_WAY) | G
// 26 bits |     4 bits                         | 2 bits

#define NUM_WAY 4
#define INDEX_BIT_WIDTH 4
#define TAG_BIT_WIDTH (ADDR_BIT_WIDTH - G_BIT_WIDTH - INDEX_BIT_WIDTH)

struct cache_block
{
  uint32_t tag:TAG_BIT_WIDTH;
  uint32_t valid:1;
  uint32_t data;
  uint32_t counter:2;
};

struct cache_block cache[NUM_CACHE_BLOCKS];
struct cache_block* ways[NUM_WAY];

void cache_init(void)
{
  num_cache_hit = 0;
  num_cache_miss = 0;

  for(uint32_t idx=0; idx<NUM_CACHE_BLOCKS; idx++) {
    cache[idx].valid = 0;
    cache[idx].counter = 0;
  }
  ways[0] = cache;
  for(unsigned i = 1; i < NUM_WAY; ++i){
    ways[i] = ways[i - 1] + (NUM_CACHE_BLOCKS / NUM_WAY);
  }
  return;
}

uint32_t cache_read(uint32_t addr)
{
  // TODO: Assignment #3
  uint32_t value = 0;
  uint32_t idx = ((addr << TAG_BIT_WIDTH) >> (ADDR_BIT_WIDTH - INDEX_BIT_WIDTH));
  uint32_t tag = (addr >> (ADDR_BIT_WIDTH - TAG_BIT_WIDTH));
  uint32_t max_ctr = 0, min_ctr = 4, evicted = NUM_WAY;
  char hit = 0;
  for(unsigned i = 0; i < NUM_WAY; ++i){
    if(ways[i][idx].valid == 1 && ways[i][idx].tag == tag) {
      ++num_cache_hit; hit = 1;
      value = ways[i][idx].data;
    }
    max_ctr = (max_ctr < ways[i][idx].counter ? ways[i][idx].counter : max_ctr);
    if (ways[i][idx].counter < min_ctr) {
      min_ctr = ways[i][idx].counter;
      evicted = i;
    }
    else if (ways[i][idx].valid == 0) evicted = i;
  }

  if(min_ctr == 3) { // handle counter saturation
    for(unsigned i = 0; i < NUM_WAY; ++i) ways[i][idx].counter = 0; 
    max_ctr = 0;
  }

  if(hit == 0){
    ++num_cache_miss;
    uint8_t* p = ram + (((ways[evicted][idx].tag << INDEX_BIT_WIDTH) | idx) << G_BIT_WIDTH);
    if(ways[evicted][idx].valid){ // if every way was valid, always evict the LRU block
      value = ways[evicted][idx].data;
      p[0] = value & 0xff;
      p[1] = (value >> 8) & 0xff;
      p[2] = (value >> 16) & 0xff;
      p[3] = (value >> 24) & 0xff;
    }
    p = ram + (((tag << INDEX_BIT_WIDTH) | idx) << G_BIT_WIDTH);
    value = ways[evicted][idx].data = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
    ways[evicted][idx].tag = tag;
    ways[evicted][idx].valid = 1;
  }
  ways[evicted][idx].counter = max_ctr + (max_ctr < 3 ? 1 : 0);
  return value;
}

void cache_write(uint32_t addr, uint32_t value)
{
  // TODO: Assignment #3
  uint32_t idx = ((addr << TAG_BIT_WIDTH) >> (ADDR_BIT_WIDTH - INDEX_BIT_WIDTH));
  uint32_t tag = (addr >> (ADDR_BIT_WIDTH - TAG_BIT_WIDTH));
  uint32_t max_ctr = 0, min_ctr = 4, written = NUM_WAY;
  char hit = 0;
  for(unsigned i = 0; i < NUM_WAY; ++i){
    if(ways[i][idx].tag == tag && ways[i][idx].valid == 1) {
      ++num_cache_hit; hit = 1;
      written = i;
    }
    max_ctr = (max_ctr < ways[i][idx].counter ? ways[i][idx].counter : max_ctr);
    if (ways[i][idx].counter < min_ctr) {
      min_ctr = ways[i][idx].counter;
      if(hit == 0) written = i;
    }
    else if(ways[i][idx].valid == 0 && hit == 0) written = i;
  }

  if(min_ctr == 3) { // handle counter saturation
    for(unsigned i = 0; i < NUM_WAY; ++i) ways[i][idx].counter = 0; 
    max_ctr = 0;
  }

  if(hit == 0){
    if(ways[written][idx].valid){ // if every way was valid, always evict the LRU block
      ++num_cache_miss;
      uint8_t* p = ram + (((ways[written][idx].tag << INDEX_BIT_WIDTH) | idx) << G_BIT_WIDTH);
      uint32_t val = ways[written][idx].data;
      p[0] = val & 0xff;
      p[1] = (val >> 8) & 0xff;
      p[2] = (val >> 16) & 0xff;
      p[3] = (val >> 24) & 0xff;
    }
    else ++num_cache_hit; // no need for memory access: increase hit counter
    ways[written][idx].tag = tag;
    ways[written][idx].valid = 1;
  }
  ways[written][idx].counter = max_ctr + (max_ctr < 3 ? 1 : 0);
  ways[written][idx].data = value;
  return;
}
