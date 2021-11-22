/********************************************************
 * 给你一个字符串 s ，请你去除字符串中重复的字母，使得每
 * 个字母只出现一次。需保证 返回结果的字典序最小（要求不
 * 能打乱其他字符的相对位置）。
 *
 * 示例 1：
 * 输入：s = "bcabc"
 * 输出："abc"
 *
 * 示例 2：
 * 输入：s = "cbacdcbc"
 * 输出："acdb"
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 这道题里面提出一个概念：字典序。也就是字母中的顺序。字典序
 * 最小，就是按照字母顺序排列.
 * 去重：可以使用哈希表(使用数组来统计个数)来实现
 * 不打乱相对位置，顺序遍历过去就可以实现不打乱
 * 字典序最小：这个就需要在去重时，尽量保证小的字母在前，重复的
 * 较大字母保留后面的
 */
char * removeDuplicateLetters(char * s)
{
	char	stack[128] = {0};
	char	count[128] = {0};	// 用来统计各个字母出现的次数
	char	in_stack[128] = {0};	// 用来标记该字母是否已入栈
	int		i = 0;
	int		top = 0;
	int		len = strlen(s);
	char*	rst = NULL;

	// 统计每个字母出现的次数，以此判断后面是否还有该字母
	for (i = 0; i < len; ++i) {
		count[s[i]] += 1;
	}

	for (i = 0; i < len; ++i) {
		if (in_stack[s[i]] == 1)  {	// 如果该字母已经入栈，就丢弃掉
			count[s[i]]--;
			continue;
		}
		
		// 由于需要保持最小字典序，也就是如果两个相同字母中间有
		// 较小字典序的字母，那么就要丢弃前面的字母，保留后面的.
		// 所以这里在对字母入栈的时候，需要与栈顶元素比对一
		// 下，如果小于栈顶元素，并且栈顶元素在后面还会有，
		// 那就要丢弃掉栈顶元素
		while (top > 0 && s[i] < stack[top - 1] && count[stack[top-1]] > 1) {
			in_stack[stack[top-1]] = 0;
			count[stack[top-1]]--;
			top--;
		}

		in_stack[s[i]] = 1;
		stack[top++] = s[i];
	}

	rst = calloc(1, sizeof(char)*(top+1));
	strncpy(rst, stack, top);
	return rst;
}

void main(int argc, char* argv[])
{
	printf("rst = %s\r\n", removeDuplicateLetters(argv[1]));
}
