#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>


//变参函数
//如何获得a往后的参数列表？ va_list 类型的变量
//如何定位a后面第一个参数的位置  va_start函数
//如何获取下一个可变参数列表中的参数  va_arg函数
//如何结束整个获取可变参数列表的动作  va_end函数
//
//
//
/*
#define P(func) {\
	printf("%s = %d\n", #func, func);\
}

int max_int(int n, ...)
{
	int ans = INT32_MIN;
	va_list arg;
	va_start(arg, n);
	while (n--)
	{
		int temp = va_arg(arg, int);
		if (temp > ans)
			ans = temp;
	}
	va_end(arg);
	return ans;
}

int main()
{
	//printf("%d\n", max_int(3, 1, 2, 3));
	//printf("%d\n", max_int(5, 1, 3, 5, 13, 1));
	//printf("%d\n", max_int(5, 1, 14, 3, 7, 11, 23, 44));
	P(max_int(3, 1, 2, 3));
	P(max_int(5, 1, 3, 5, 13, 1));
	P(max_int(5, 1, 14, 3, 7, 11, 23, 44));
	return 0;
}
*/

int reverse_num(int n, int* temp)
{
	int digit = 0;
	do {
		*temp = *temp * 10 + n % 10;
		n /= 10;
		digit++;
	} while (n);
	return digit;
}

int output_num(int n, int digit)
{
	int cnt = 0;
	while (digit--) {
		putchar(n % 10 + '0'), ++cnt;
	}
	return cnt;
}


int my_printf(const char* frm, ...)
{
	int cnt = 0;
	va_list arg;
	va_start(arg, frm);
	#define PUTC(a) putchar(a), ++cnt
	for (int i = 0; frm[i]; i++)
	{
		switch (frm[i]) {
			case '%':
			{
				switch (frm[++i])
				{
					case '%': PUTC(frm[i]); break;
					case 'd':
					{
						int x = va_arg(arg, int);
						uint32_t xx = 0;
						if (x < 0) PUTC('-'), xx = -x;
						else xx = x;
						int x1 = xx / 100000, x2 = xx % 100000;
						int temp1 = 0, temp2 = 0;
						int digit1 = reverse_num(x1, &temp1);
						int digit2 = reverse_num(x2, &temp2);
						if (x1) digit2 = 5;
						else digit1 = 0;
						cnt += output_num(temp1, digit1);
						cnt += output_num(temp2, digit2);

						/*
						int temp = va_arg(arg, int);
						if (temp < 0)PUTC('-'), temp = -temp;
						int x = 0;
						while (temp) {
							x = x * 10 + temp % 10;
							temp /= 10;
							//将数字倒过来123；321
							int x = va_arg(arg, int);
							do {
							PUTC(x % 10 + '0');
							x /= 10;
							} while (x);
						}break;
						*/

					}break;
					case's': {
						const char* str = va_arg(arg, const char*);
						for (int i = 0; str[i]; i++)
						{
							PUTC(str[i]);
						}
					}
				}
			}break;
			default:PUTC(frm[i]); break;
		}
	}
	#undef PUTC
	va_end(arg);
	return cnt;
}

int main()
{
	int a = 123;
	printf("hello world\n");
	my_printf("hello world\n");
	printf("int(a) = %d\n", a);
	//my_printf("int(a) = %%\n", a);
	my_printf("int(a) = %d\n", a);
	printf("int (a) = %d\n", 0);
	my_printf("int (a) = %d\n", 0);
	printf("int (a) = %d\n", 1000);
	my_printf("int (a) = %d\n", 1000);
	printf("int (a) = %d\n", -123);
	my_printf("int (a) = %d\n", -123);
	printf("INT32_MAX = %d\n", INT32_MAX);
	my_printf("INT32_MAX = %d\n", INT32_MAX);
	printf("INT32_MIN = %d\n", INT32_MIN);
	my_printf("INT32_MIN = %d\n", INT32_MIN);
	char str[] = "I love China!";
	printf("%s\n", str);
	my_printf("%s\n", str);
	int n;
	while (~scanf("%d", &n))
	{
		printf(" has %d digits!\n", printf("%d", n));
		my_printf(" has %d digits!\n", printf("%d", n));
	}
	return 0;
	}