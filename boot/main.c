volatile int boot_ok;

void main(void)
{
    boot_ok = 1234;
    while (1);
}
