void *memcpy(void *dst, const void *src, unsigned int n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;

    while (n--)
        *d++ = *s++;

    return dst;
}

void *memset(void *dst, int val, unsigned int n)
{
    unsigned char *p = (unsigned char *)dst;

    while (n--) {
        *p++ = (unsigned char)val;
    }

    return dst;
}
