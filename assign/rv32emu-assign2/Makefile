BINS = emu-rv32i multiply

CROSS_COMPILE = riscv-none-embed-
RV32I_CFLAGS = -march=rv32im -mabi=ilp32 -O0 -nostdlib

CFLAGS = -O3 -Wall
LDFLAGS = -lelf

all: $(BINS)

emu-rv32i: emu-rv32i.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

multiply.s: multiply.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -S -o $@ $<

multiply.o: multiply.s
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -c -o $@ $<

multiply: multiply.o
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

hash.s: hash.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -S -o $@ $<

hash.o: hash.s
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -c -o $@ $<

hash: hash.o
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

hash_rv32z.s: hash_rv32z.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -S -o $@ $<

hash_rv32z.o: hash_rv32z.s
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -c -o $@ $<

hash_rv32z: hash_rv32z.o
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

check: $(BINS)
	./emu-rv32i multiply
	./emu-rv32i hash
	./emu-rv32i hash_rv32z

clean:
	$(RM) $(BINS) *.o *.s multiply multiply.s hash_rv32z hash
