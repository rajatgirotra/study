
/* Don't compile this, only view the generates asm. */
unsigned int A = 10, B = 10;

void foo() {
    A = B+1;
    B = 0;
}

int main() {}
