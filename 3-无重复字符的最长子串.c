/********************************************************
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 * 
 * 解题思路: 
 * 在字符串中寻找不重复的子串，肯定需要记录当前已扫描的子串，
 * 即:需要标记子串开头在哪。
 * 要判断新增字符是否与当前子串有重复元素，要么挨个比较, 要么
 * 就要记录所有字符的出现次数,直接判断新增字符的频次是否为0
 * ******************************************************/
#include "stdio.h"

int get_long(char* str)
{
	int num = 0;
	char*	start = str;
	char*	find  = str;
	char*	cursor = start;

	if (!str)
		return 0;

	while (*find != 0) {
		for(; cursor != find; ++cursor) {
			if (*cursor == *find) {
				break;
			}
		}
		if (cursor != find) {
			start = cursor + 1;
		}
		find = find + 1;
		num = (find - start) > num ? (find - start) : num;
		cursor = start;
	}
	return num;
}

/********************************************************
 * 利用ascii编码规律减少一次循环
 * ******************************************************/
int get_long_2(char* str)
{
	int		max = 0;
	int		char_freq[128] = {0};	//ascii一共128字符
	char*	left = str;
	char*	right = str;	

	if (!str)
		return 0;

	while (*right != 0) {
		if (char_freq[*right] == 0) {
			char_freq[*right] = 1;
			right += 1;
		} else {
			char_freq[*left] = 0;
			left += 1;
		}
		max = (right - left) > max ? (right - left) : max;
	}

	return max;
}


int main(int argc, char* argv[])
{
	if (argc == 2) {
		printf("num = %d\r\n", get_long(argv[1]));
	} else {
		printf("input error.\r\n");
	}
}

