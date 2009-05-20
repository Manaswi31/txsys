#include <stdio.h>
#include <stdlib.h>

int   bitcnt (unsigned   int   src)  
{  
  int   count=0;  

  for(;src!=0;count+=src&1,src>>=1);  
    return   count;  
}   

void usage(void)
{
}

int main(int argc, char* args[])
{

    int op;
    if (argc!=2) usage();
    op = atoi(args[1]);
    printf("%d\n", bitcnt(op));

}
