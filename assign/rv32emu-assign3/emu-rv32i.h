// Assignment #3: DO NOT MODIFY THIS FILE

#ifndef _EMU_RV32I_H_
#define _EMU_RV32I_H_

#define RAM_SIZE 0x10000

// #define DEBUG_OUTPUT
// #define DEBUG_EXTRA
// #define CACHE_DEBUG

#ifdef DEBUG_OUTPUT
#define debug_out(...) printf("## " __VA_ARGS__)
#else
#define debug_out(...)
#endif

#ifdef CACHE_DEBUG
#define cache_debug(...) printf("## " __VA_ARGS__)
#else
#define cache_debug(...)
#endif

#endif
