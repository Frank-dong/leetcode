/********************************************************
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * 如果不存在公共前缀，返回空字符串 ""。
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 寻找公共前缀，即每个字符串有相同的头部子串，所以直接按照
 * 顺序遍历即可，遇到不相等时退出
 *
 * 从算法的时间复杂度上来说是O(mn)
 */
char * longestCommonPrefix(char ** strs, int strsSize)
{
	int	i = 0;
	int	j = 0;
	int	ret = 0;
	int	pos = 0;
	char*	rst = NULL;

	for (i = 0; i < strlen(strs[0]); ++i) {
		for (j = 1; j < strsSize; ++j) {
			if (strs[j][i] != strs[0][i]) {
				ret = 1;
				break;
			}
		}
		if (ret)
			break;
	}
	printf("i = %d\r\n", i);
	rst = calloc(1, i + 1);
	strncpy(rst, strs[0], i);
	return rst;
}

/**
 * 上面一种方法可以算作是纵向比较，即对每个字符串按照顺序
 * 逐个比较。
 * 也可以换一种方式，称之为横向比较，以第一个字符串为公共
 * 前缀初始值，然后逐个跟后面的一个求公共前缀，直到遍历完
 * 所有字符串，或者公共前缀为空，结束。
 *
 * 从算法的时间复杂度上来说是O(mn)
 */
char * longestCommonPrefix_2(char ** strs, int strsSize)
{
	int	i = 0;		
	int	j = 0;
	char*	rst = NULL;

	rst = calloc(1, strlen(strs[0]) + 1);
	strcpy(rst, strs[0]);

	for (i = 1; i < strsSize && strlen(rst) > 0; ++i) {
		for (j = 0; j < strlen(rst); ++j) {
			if (strs[i][j] != rst[j]) {
				rst[j] = 0;
				break;
			}
		}
	}

	return rst;
}


int main(int argc, char* argv[])
{
	char*	strs[] = {"flower","flow","flight"};
	//char*	strs[] = {"dog","racecar","car"};
	char*	rst = NULL;

	rst = longestCommonPrefix_2(strs, 3);	
	printf("rst = %s\r\n", rst);
	free(rst);
	return 0;
}
