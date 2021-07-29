/********************************************************
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 * ******************************************************/
#include <stdio.h>
#include <string.h>

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

int main(int argc, char* argv[])
{
	printf("str = %s\r\n", longestPalindrome(argv[1]));
}
