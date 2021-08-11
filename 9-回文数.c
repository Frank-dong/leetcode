/********************************************************
 * 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。
 *
 * 尽量不转成字符串来处理
 * 2021年 07月 08日 星期四 17:35:37 CST
 * ******************************************************/
#include "stdio.h"
#include "stdbool.h"

/**
 * 不转成字符串的话，就只能按照位数来比较数值。想办法取最高位
 * 和最低位的值进行比较。最低位可以通过取余的方式获得。最高位
 * 不好获得。
 */

/** 既然最低位好取，那就逐个取完，得到一个反转的整型数，和原
 * 数相比。
 */
bool isPalindrome(int x)
{
	long long rst = 0;
	int		tmp = x; 
	int		i = 0;
	int		start = 0;

	if (x < 0)
		return false;

	while (1) {
		if (x/10 == 0)
			break;
		rst = rst*10 + x%10;
		x = x/10;
	}
	rst = rst*10 + x;	
	if (rst > 0x7fffffff)
		return false;
	return rst == tmp;
}

/**
 * 优化
 */
bool isPalindrome_1(int x)
{
	int		rst = 0;
	int		i = 0;

	if (x < 0 || (x > 0 && x %10 == 0))
		return false;

	while (1) {
		if (x/10 == 0)
			break;
		rst = rst*10 + x%10;
		x = x/10;
		// 如果是回文数，则会在某个时刻，从后向前得到的数值和
		// 前半部分数值相等
		if (rst !=0 && (rst == x || rst == x/10))
			return true;
		else if (rst > x)
			return false;
	}
	return rst != 0 ? rst == x : true;
}
/**
 * 进一步简化代码
 */
bool isPalindrome_2(int x)
{
	int		rst = 0;
	int		i = 0;

	if (x < 0 || (x > 0 && x %10 == 0))
		return false;

	while (x > rst) {
		rst = rst*10 + x%10;
		x = x/10;
	}
	return x == rst || x == rst/10;
}

int main(int argc, char* argv[])
{
	printf("is palindrome ? %s\r\n", isPalindrome_2(atoi(argv[1])) ? "Y" : "N");
}
