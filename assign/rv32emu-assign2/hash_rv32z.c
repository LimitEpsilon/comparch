#define STR1(x) #x
#define STR(x) STR1(x)

#define OPCODE_HASH_INIT   0b1111100
#define OPCODE_HASH_UPDATE 0b1111101
#define OPCODE_HASH_DIGEST 0b1111110

#define BUILD_INST(opcode, rd, rs1, rs2, funct) \
  opcode                              |         \
  (rd                   << (7))       |         \
  (0x7                  << (7+5))     |         \
  (rs1                  << (7+5+3))   |         \
  (rs2                  << (7+5+3+5)) |         \
  (0                    << (7+5+3+5+5))

unsigned hash_rv32z(const char *key)
{
  unsigned hash_value = 0;

  asm (".word "STR(BUILD_INST(OPCODE_HASH_INIT, 0, 0, 0, 0))"\n\t");

  for (;*key;++key) {
    asm ("mv a5, %[_rs1]\n\t"
         ".word "STR(BUILD_INST(OPCODE_HASH_UPDATE, 0, 15, 0, 0))"\n\t"
         :
         : [_rs1] "r" (*key)
         : "a5");
  }

  asm (".word "STR(BUILD_INST(OPCODE_HASH_DIGEST, 15, 0, 0, 0))"\n\t"
       "mv %[_rd], a5"
       : [_rd] "=r" (hash_value)
       :
       : "a5");
  return hash_value;
}

unsigned hash(const char *key)
{
  return hash_rv32z(key);
}

void print_hash(unsigned hashval)
{
  volatile char* tx = (volatile char*) 0x40002000;
  unsigned char v;
  for(int i=0; i<=7; i++) {
    v = (hashval >> (7-i)*4) & 0xf;
    if (v < 10) {
      *tx = v + 0x30;
    } else {
      *tx = (v - 10) + 0x61;
    }
  }
  *tx = '\n';
}

void _start(void)
{
  print_hash(hash("Hello x86 Hello x86 Hello x86 Hello x86 Hello x86"));
  print_hash(hash("Hello risc-v Hello risc-v Hello risc-v Hello risc-v Hello risc-v"));
}
