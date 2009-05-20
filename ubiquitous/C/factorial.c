#include <stdio.h>
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

int main(int argc, char* args[])
{
    printf("%ld\n", factorial(-1));
    return 0;
}
