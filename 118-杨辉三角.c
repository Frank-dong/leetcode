/********************************************************
 * 给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
 *
 * 在「杨辉三角」中，每个数是它左上方和右上方的数的和。
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * 非常明显的规律，每个位置的数的来源很确定，整体思路下来就是
 * 动态规划，求解各个子问题，最终得到结果
 *
 * 状态转义方程
 * F(i, j) = {
 *                 1 (j = 0 or j = i);
 *                 F(i-1, j-1) + F(i-1, j) (j != 0 and j != i)
 *			}
 * }
 */

int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
	int**	rst_list = NULL;
	int*	col_list = NULL;
	int		i = 0;
	int		j = 0;

	rst_list = calloc(1, sizeof(void*)*numRows);
	col_list = calloc(1, sizeof(int)*numRows);
	
	for (i = 0; i < numRows; ++i) {
		rst_list[i] = calloc(1, sizeof(int)*(i+1));
		col_list[i] = i + 1;
		for (j = 0; j <= i; ++j) {
			if (j == 0 || j == i)
				rst_list[i][j] = 1;
			else 
				rst_list[i][j] = rst_list[i-1][j-1] + rst_list[i-1][j];
		}
	}
	*returnSize = numRows;
	*returnColumnSizes = col_list;
	return rst_list;
}

int main(int argc, char* argv[])
{
	int**	rst_list = NULL;
	int*	col_list = NULL;
	int		ret_num = 0;
	int		i = 0;
	int		j = 0;

	rst_list = generate(atoi(argv[1]), &ret_num, &col_list);

	for (i = 0; i < ret_num; ++i) {
		for (j = 0; j < col_list[i]; ++j) {
			printf("%d ", rst_list[i][j]);
		}
		printf("\r\n");
	}

	return 0;
}
