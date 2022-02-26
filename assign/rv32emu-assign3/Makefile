BINS = emu-rv32i emu-rv32i-dir-cache emu-rv32i-set-cache
MAT_BINS = mat-row2 mat-col2 mat-row4 mat-col4 mat-row8 mat-col8 mat-row16 mat-col16
NATIVE_MAT_BINS = native-mat-row2 native-mat-col2 native-mat-row4 native-mat-col4
NATIVE_MAT_BINS += native-mat-row8 native-mat-col8 native-mat-row16 native-mat-col16

CROSS_COMPILE = riscv-none-embed-
RV32I_CFLAGS = -march=rv32im -mabi=ilp32 -O0 -nostdlib

CFLAGS = -O3 -Wall
LDFLAGS = -lelf
CC = gcc-7

all: $(BINS) $(MAT_BINS) $(NATIVE_MAT_BINS)

emu-rv32i: emu-rv32i.c emu-rv32i.h
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

emu-rv32i-%-cache: emu-rv32i.c emu-%-cache.c
	$(CC) $(CFLAGS) -DUSE_CACHE -o $@ $^ $(LDFLAGS)

mat: $(MAT_BINS)

native-mat-row%: mat.c
	$(CC) -DNATIVE -DMAT_ORDER=$* -DROW_MAJOR -o $@ $<

native-mat-col%: mat.c
	$(CC) -DNATIVE -DMAT_ORDER=$* -o $@ $<

mat-row%: mat.c
	$(CROSS_COMPILE)gcc -DMAT_ORDER=$* -DROW_MAJOR $(RV32I_CFLAGS) -o $@ $<

mat-col%: mat.c
	$(CROSS_COMPILE)gcc -DMAT_ORDER=$* $(RV32I_CFLAGS) -o $@ $<

check: $(BINS) $(MAT_BINS) $(NATIVE_MAT_BINS)
	@./check-correct.sh

.PHONY: mat check

clean:
	$(RM) $(BINS) $(MAT_BINS) $(NATIVE_MAT_BINS) *.o *.mem rom.v *.log

