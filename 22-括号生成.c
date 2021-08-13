/********************************************************
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够
 * 生成所有可能的并且 有效的 括号组合。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 这也相当与一个全排列问题，只不过修剪条件不同而已。
 * 这类题目都适合回溯算法处理
 *
 * 路径列表: n个(, n个)
 * 结束条件: 左右括号个数都等于n，记录结果
 * 修剪条件: 左右括号个数<=n; 并且已有右括号不能多于左括号(否则无效)
 *
 */
void generate(int n, int left, int right, char* rst, int index, char** rst_list, int* rst_num)
{
	if (left == n && right == n) {
		rst_list[*rst_num] = calloc(1, n*2 + 1);
		strcpy(rst_list[*rst_num], rst);
		// ++的优先级高于*，所以此处需要带括号
		(*rst_num)++;
		return;
	}

	// 这里路径选择只有两个，要么选择左括号，要么选择右括号
	if (left < n) {	// 左括号可选，就选左括号
		rst[index] = '(';
		generate(n, left + 1, right, rst, index + 1, rst_list, rst_num);
	}

	// 这里没有循环，但是由于只有两条路径，这里也就相当于选择了另外一条路径
	if (right < left && right < n) {
		rst[index] = ')';
		generate(n, left, right + 1, rst, index + 1, rst_list, rst_num);
	}
}
char ** generateParenthesis(int n, int* returnSize)
{
	char**	rst_list = calloc(1, 1500);
	char	rst[n*2+1];

	memset(rst, 0, n*2+1);
	*returnSize = 0;
	generate(n, 0, 0, rst, 0, rst_list, returnSize);
	return rst_list;
}


/**
 * 考虑使用动态规划的方式来做
 */



int main(int argc, char* argv[])
{
	char**	rst_list = NULL;
	int		i = 0;
	int		rst_num = 0;

	rst_list = generateParenthesis(atoi(argv[1]), &rst_num);
	
	for (i = 0; i < rst_num; ++i) {
		printf("%s\r\n", rst_list[i]);
	}
	printf("Total: %d\r\n", rst_num);
}
