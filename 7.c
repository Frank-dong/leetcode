/********************************************************
 * 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
 * 如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
 * 假设环境不允许存储 64 位整数（有符号或无符号）。
 *
 * 2021年 07月 07日 星期三 22:39:00
 * ******************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * 这道题主要是在数字顺序的调整上，可以把数字转换成字符，
 * 调换字符后，再转成整型数，加上一些条件判断即可
 * 
 * 这个思路的缺点是使用了atoi和sprintf这样的系统函数，
 * 是比会影响效率，或者有违题目要求.
 */
int reverse(int x)
{
	char	buf[16] = {0};
	char	max_limit[16]  = {0};
	char	min_limit[16] = {0};
	int	i = 0;
	int	j = 0;
	int	len_limit = 0;
	int	num_len = 0;
	int	ret = 0;
	int	start = 0;
	char	tmp = 0;
		
	sprintf(max_limit, "%d", 0x7fffffff-1);
	sprintf(min_limit, "%d", 0 - 0x7fffffff);
	sprintf(buf, "%d", x);
	len_limit = strlen(max_limit);

	num_len = strlen(buf);
	if (buf[0] == '-') {
		start = 1;
	}

	j = num_len - 1;
	for (i = start; i < (num_len-start)/2 + start; ++i, j--) {
		tmp = buf[i];
		buf[i] = buf[j];
		buf[j] = tmp;
	}
	if (start == 1) {
		if (num_len > len_limit+1 ||
			(num_len == len_limit+1 &&  strcmp(min_limit, buf) < 0)) {
			return 0;	
		}
	} else {
		if (num_len > len_limit || (num_len == len_limit && strcmp(max_limit, buf) < 0)) {
			return 0;	
		}
	}

	return atoi(buf);	
}

int main(int argc, char* argv[])
{
	char*	rst = NULL;

	//printf("%d\r\n", atoi("42949672990"));	
	printf("%d\r\n", reverse(atoi(argv[1])));

	return 0;
}

