void _start()
{
    volatile char* tx = (volatile char*) 0x40002000;
    char x = 2;
    char y = 3;
    char z = x * y;
    *tx = z + 0x30;
}
