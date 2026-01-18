void uart_puts(const char *);

void main(void)
{
    uart_puts("HELLO FROM BARE METAL\n");
    while (1);
}
