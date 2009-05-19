
#include <stdio.h>
#include <stdarg.h>

void arg_test(int i, ...);
int main(int argc,char *argv[])
{
 //int int_size = _INTSIZEOF(int);
 int int_size = sizeof (int);
 printf("int_size=%d\n", int_size);
 arg_test(0, 4);
 
 //arg_cnt(4,1,2,3,4);
 return 0;
}
void arg_test(int i, ...)
{
 int j=0;
 va_list arg_ptr; 
 
 va_start(arg_ptr, i); 
 printf("&i = %p\n", &i);//打印参数i在堆栈中的地址
 printf("arg_ptr = %p\n", arg_ptr);
 //打印va_start之后arg_ptr地址,
 //应该比参数i的地址高sizeof(int)个字节
 //这时arg_ptr指向下一个参数的地址
 
 j=*((int *)arg_ptr);
 printf("%d %d\n", i, j); 
 j=va_arg(arg_ptr, int);
 printf("arg_ptr = %p\n", arg_ptr);
 //打印va_arg后arg_ptr的地址
 //应该比调用va_arg前高sizeof(int)个字节
 //这时arg_ptr指向下一个参数的地址
 va_end(arg_ptr);
 printf("%d %d\n", i, j);
}
