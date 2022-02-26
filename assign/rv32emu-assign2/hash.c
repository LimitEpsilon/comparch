unsigned hash_rv32m(const char *key)
{
    unsigned hash_value = 0x23198485;
    for (;*key;++key) {
      hash_value^= *key;
      hash_value*= 0x5bd1e995;
      hash_value^= hash_value>> 15;
    }
    return hash_value;
}

unsigned hash(const char *key)
{
  return hash_rv32m(key);
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
