void *memcpy(void *dst, const void *src, unsigned int n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;

    while (n--)
        *d++ = *s++;

    return dst;
}
