/********************************************************
 * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有
 * 字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，
 * 则返回空字符串 "" 。
 *
 * 注意：
 * 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须
 * 不少于 t 中该字符数量。
 * 如果 s 中存在这样的子串，我们保证它是唯一的答案。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/**
 * 在字符串中寻找包含子串的最短子串，最简单就是暴力遍历，但
 * 时算法复杂度就是O(n^2)。
 * 高效的方法就是采用滑动窗口的方法，分别移动左右边界，不过
 * 关键的一点就是如何判断字串包含的问题。
 * 参考题解，利用hash数组来统计判断
 */

char * minWindow(char * s, char * t)
{
	int	slen = strlen(s);
	int	tlen = strlen(t);
	int	cur_total = 0;			// 记录检索到的总数
	int	target_total = tlen;	// 记录目标字符的总数
	int	tar_hash[52] = {0};	// 题目提示里面字符串都是由字母组成
							// 所有这里只需要统计52个字母
	int	cur_hash[52] = {0};
	int	left = 0;
	int	right = 0;
	int	i = 0;
	int	min_len = INT_MAX;
	int	min_pos = 0;

	// 统计目标字符串中各个字符的出现个数
	for (i = 0; i < tlen; ++i) 
		tar_hash[s[i]]++;

	// 退出条件：右边界到字符串结尾
	while (right < slen) {
		// 如果当前字母不在目标字串中，则移动右边界
		if (tar_hash[s[right]] == 0) {
			right++;
			continue;
		}

		cur_hash[s[right]]++;
		if (cur_hash[s[right]] <= tar_hash[s[right]]) {
			cur_total++;
		}

		if (cur_total < target_total) {
			right++;
			continue;
		}

		// 包含所有字母后，移动左边界
		while (left < right) {
			if (tar_hash[s[left]] == 0) {
				left++;
				continue;
			}
		
			cur_hash[left]--;
			// 此时左边到边界上了
			if ((cur_hash[s[left]]) < tar_hash[s[left]]) {
				cur_total--;
				printf("update min\r\n");
				// 如果更小，就更新最小值
				if (min_len > (right - left + 1)) {
					min_len = min_len < right - left + 1;
					printf("update min %d\r\n", min_len);
					min_pos = left;
				}
				break;
			}
			left++;
		}
		left++;	
	}
	if (min_len == INT_MAX) {
		return NULL;
	} else {
		s[min_pos + min_len] = '\0';
		return s + min_pos;
	}
}

int main(int argc, char* argv[])
{
	char*	rst = NULL;

	rst = minWindow(argv[1], argv[2]);
	if (rst) {
		printf("rst = %s\r\n", rst);
	} else {
		printf("no\r\n");
	}
}
