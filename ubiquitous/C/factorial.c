#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long factorial (long n)
{
    assert(n>=0);

    if (n==0) {
	    return 1;
    } else {
	return n*factorial(n-1);
    }
}

void usage(void)
{
    printf("usage:\n");
    printf("<program> number\n");
}

int main(int argc, char* args[])
{
    int n;

    if (argc<2) {
	usage();
	exit(0);
    } else {
	n = atoi(args[1]);
    }
    printf("%ld\n", factorial(n));
    return 0;
}
