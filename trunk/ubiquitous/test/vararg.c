
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
 printf("&i = %p\n", &i);//��ӡ����i�ڶ�ջ�еĵ�ַ
 printf("arg_ptr = %p\n", arg_ptr);
 //��ӡva_start֮��arg_ptr��ַ,
 //Ӧ�ñȲ���i�ĵ�ַ��sizeof(int)���ֽ�
 //��ʱarg_ptrָ����һ�������ĵ�ַ
 
 j=*((int *)arg_ptr);
 printf("%d %d\n", i, j); 
 j=va_arg(arg_ptr, int);
 printf("arg_ptr = %p\n", arg_ptr);
 //��ӡva_arg��arg_ptr�ĵ�ַ
 //Ӧ�ñȵ���va_argǰ��sizeof(int)���ֽ�
 //��ʱarg_ptrָ����һ�������ĵ�ַ
 va_end(arg_ptr);
 printf("%d %d\n", i, j);
}
