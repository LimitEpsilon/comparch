BINS = emu-rv32i first

CROSS_COMPILE = riscv-none-embed-
RV32I_CFLAGS = -march=rv32i -mabi=ilp32 -O0 -nostdlib

CFLAGS = -O3 -Wall
LDFLAGS = -lelf

all: $(BINS)

emu-rv32i: emu-rv32i.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

first: first.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

bubble_recur: bubble_recur.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

bubble_iter: bubble_iter.c
	$(CROSS_COMPILE)gcc $(RV32I_CFLAGS) -o $@ $<

check: $(BINS)
	./emu-rv32i first

clean:
	$(RM) $(BINS) bubble_recur bubble_iter
