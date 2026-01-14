void kernel_main(void)
{
    volatile int x = 0x1234;

    while (1) {
        x++;
    }
}
