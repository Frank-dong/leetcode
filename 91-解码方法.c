/********************************************************
 * 一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * 要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：
 *
 * "AAJF" ，将消息分组为 (1 1 10 6)
 * "KJF" ，将消息分组为 (11 10 6)
 * 注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。
 *
 * 给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。
 *
 * 题目数据保证答案肯定是一个 32 位 的整数。
 *
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 先通过罗列一些数据，从中找找演变的规律，然后确定状态转移方程
 *
 * 下面这个代码还有再优化的空间
 */
int numDecodings(char * s)
{
	int		len = strlen(s);
	int*	dp = calloc(1, sizeof(int)*(len));
	int		i = 0;
	int		sig_num = 0;

	for (i = 0; i < len; ++i) {
		if (i == 0) {
			if (s[i] != '0') {
				dp [i] = 1;
				sig_num = 1;
			}
			continue;
		}
		if (s[i] != '0') {
			if (s[i - 1] != 0 && (strncmp(s + i - 1, "26", 2) <= 0)) {
				dp[i] = dp[i-1] + sig_num;
			} else {
				dp[i] = dp[i-1];
			}
			sig_num = dp[i-1];
		} else {
			// 由于不会出现类似40 50 这样的编码，所以这里不用判断
			// 错了，会出现，出现则作为错误处理，返回0
			if (s[i - 1] != 0 && (strncmp(s + i - 1, "26", 2) <= 0)) {
				dp[i] = sig_num;
				sig_num = 0;
			} else {
				return 0;
			}
		}
	}
	return dp[len - 1];
}

void main(int argc, char* argv[])
{
	printf("%d\r\n", numDecodings(argv[1]));
}
