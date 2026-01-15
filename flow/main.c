volatile int a, b, c, d;

int level3(void) {
    d = 40;
    return d;
}

int level2(void) {
    c = 30;
    return level3() + c;
}

int level1(void) {
    b = 20;
    return level2() + b;
}

void main(void) {
    a = 10;
    int result = level1();
    while (1);
}
