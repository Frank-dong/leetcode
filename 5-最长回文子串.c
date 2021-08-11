/********************************************************
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if 0
char * longestPalindrome(char * s){
	char*	found = NULL;
	char*	left = s;
	char*	right = NULL;
	int		len = 0;


}
#elif 0
char * longestPalindrome(char * s){
	char*	find_l = s;
	char*	find_r = NULL;
	char*	found = s;
	int		found_len = 1;
	int		str_len = 0;
	int		i = 0;

	if (!s)
		return NULL;

	str_len = strlen(s);
	while ((*find_l != 0) && (*(find_l + 1) != 0)) {
		if (*(find_l + 2) != 0 && (*find_l == *(find_l + 2))) {
			find_r = find_l + 2;
			for (i = 1; (find_l - i >= s) && (find_r + i <= s + str_len); ++i) {
				if (*(find_l - i) != *(find_r + i))
					break;
			}
			if (found_len < (find_r - find_l + (i-1)*2 + 1)) {
				found_len = find_r - find_l + (i-1)*2 + 1;
				found = find_l - i + 1;
			}
		} 

		if (*find_l == *(find_l + 1)) {
			find_r = find_l + 1;
			for (i = 1; (find_l - i >= s) && (find_r + i <= s + str_len); ++i) {
				if (*(find_l - i) != *(find_r + i))
					break;
			}
			if (found_len < (find_r - find_l + (i-1)*2 + 1)) {
				found_len = find_r - find_l + (i-1)*2 + 1;
				found = find_l - i + 1;
			}
		}

		find_l = find_l + 1;
	}

	*(found + found_len) = 0;
	return found;
}
#elif 1
/**
 * 这种方法是确定一个中心，然后向两边扩展检查。可以解题，但是时间复杂度较高
 */
char * longestPalindrome(char * s){
	int left=0, right = 0, maxLength = 0, startIndex = 0, index = 0;

	while(s[index]){
		right = index;
		left = index - 1;

		//从当前字符开始往右读取连续重复字符(连续重复字符必定能构成回文子串，也必定是回文子串的一部分)
		//如"abcccd" 中从索引1开始的连续重复字符是"b"，从索引2开始连续重复字符是'ccc'
		while(s[right] == s[index]){
			right++;
		}

		//定位下一个子串的中心
		index = right;

		//以连续重复字符为中心，往左右延展,判断当前子串是否为回文子串
		while(left >= 0 && s[right] && s[left] == s[right]){
			left--;
			right++;
		}

		//记录回文子串的最大长度和起始索引
		if(right-left-1 > maxLength){
			startIndex = left + 1;
			maxLength = right - left - 1;
		}

	}

	//返回回文子串
	char* returnStr = (char*)malloc(maxLength+1);
	returnStr[maxLength] = '\0';
	for(int i = 0; i < maxLength; ++i){
		returnStr[i] = s[startIndex+i];
	}
	return returnStr;
}
#endif

/**
 * 使用动态规划的方法来求解。对于一个{[i,j], j > i]}区间,如果是回文字符串，那么
 * 头尾各去掉一个字符，应该仍然是回文字符串。在此基础上罗列原问题和子问题
 *
 * 原问题 [i, j]是否为回文字符串
 * 子问题 [i + 1, j - 1]是否为回文字符串
 *
 * 状态转移方程：
 * P[i, j] = P[i+1, j-1] && (Si = Sj)
 * P[i, i] = true
 * P[i, i+1] = (Si == Sj)
 *
 * 解题步骤：
 * 1. 定义dp数组，考虑初始化值
 * 2. 自底向上开始运算求解
 */
char* longestPalindrome_dp(char* s)
{
	int	i = 0;
	int	j = 0;
	int	max = 0;
	int	begin = 0;
	int	len = strlen(s);
	int	dp[len][len];	// 可以这样定义临时变量
	char*	rst = NULL;

	if (len == 1)
		return s;

	// 初始化
	for (i = 0; i < len; ++i) {
		dp[i][i] = true;
	}

	max = 1;
	// 两个状态，则两层循环(枚举所有情况)
	for (j = 0; j < len; ++j) {
		// 注意第二层的循环条件, 因为表示一个大于1各字符的范围时头下标小于尾下标
		for (i = 0; i < j; ++i) {
			if (s[i] != s[j]) {
				dp[i][j] = false;
			} else {
				// 如果头尾相等，就要参考更小范围的结果		
				if (i + 1 == j) {
					dp[i][j] = true;
				} else {
					dp[i][j] = dp[i+1][j-1];
				}
			}
			if (dp[i][j] && (max < (j - i + 1))) {
				max = j - i + 1;
				begin = i;
			}
		}
	}
	rst = calloc(1, max + 1);
	strncpy(rst, s + begin, max);
	return rst;
}

int main(int argc, char* argv[])
{
	printf("str = %s\r\n", longestPalindrome_dp(argv[1]));
}
