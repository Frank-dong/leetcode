/********************************************************
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 * ******************************************************/
/**
 * 解题思路: 
 * 在字符串中寻找不重复的子串，肯定需要记录当前已扫描的子串，
 * 即:需要标记子串开头在哪。
 * 要判断新增字符是否与当前子串有重复元素，要么挨个比较, 要么
 * 就要记录所有字符的出现次数,直接判断新增字符的频次是否为0
 */
#include "stdio.h"

/**
 * 确定左右两个边界，判断窗口内是否有重复字符，如果有，就向
 * 右移动左边界，相当于缩小窗口。如果没有，则向右移动右边界,
 * 相当于扩大窗口。每次移动后求取一个最大值。整个遍历完成后
 * 就可以获得结果
 *
 *
 */
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
		// 没有与当前字符重复，则右移右边界
		if (char_freq[*right] == 0) {
			char_freq[*right] = 1;	// 向set中增加一个字符
			right += 1;
		} else {
			// 如果右边界检测到重复，则右移左边界
			// 这里需要注意以下，使用此种方式，必须一个个的移动
			// 左边界，因为要从set中删除字符。上面的那种解题方式
			// 可以直接定位左边界到重复字符出现的位置，因为那个里
			// 面右个游标，在每次变换窗口后，会逐个判断窗口内是否
			// 有重复字符。
			char_freq[*left] = 0;	// 从set中去除一个字符
			left += 1;				// 移动左边界
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

