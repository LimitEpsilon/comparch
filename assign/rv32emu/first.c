// riscv-none-embed-gcc -march=rv32i -mabi=ilp32 -nostdlib ./first.c -o first

void _start()
{
    volatile char* tx = (volatile char*) 0x40002000;
    const char* hello = "Hello RISC-V!\n";
    while (*hello) {
        *tx = *hello;
        hello++;
    }
}
