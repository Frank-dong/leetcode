/********************************************************
 * 给定一个不含重复数字的数组 nums ，返回其 所有可能的全
 * 排列 。你可以 按任意顺序 返回答案。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 全排列问题就是枚举所有的可能，这是典型的回溯算法的应用
 * 就是试探所有可能的结果，所以算法复杂度一般都比较高.
 */

void arrange(int* nums, int numsSize, int* used, int* rst, int index, int** rst_list, int* rst_num)
{
	int	route = -1;	
	int	i = 0;

	// 结束条件
	if (index >= numsSize) {
		// 加入结果列表
		rst_list[*rst_num] = calloc(1, sizeof(int)*numsSize);
		memcpy(rst_list[*rst_num], rst, sizeof(int)*numsSize);
		*rst_num += 1;
		return ;
	}

	for (i = 0; i < numsSize; ++i) {
		if (used[i] == 0) { 
			// 选择路径 (这里的路径就相当于是选择到了第几个数值, 这个是在used里面标注)
			rst[index] = nums[i];
			used[i] = 1;
			arrange(nums, numsSize, used, rst, index + 1, rst_list, rst_num);

			// 撤销选择
			used[i] = 0;
		}
	}

}
#define MAX_SIZE	1000
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	int**	rst_list = calloc(1, sizeof(void*)*MAX_SIZE);
	int*	colsize_array = calloc(1, sizeof(void*)*MAX_SIZE);
	int		used[numsSize];
	int		rst_buf[numsSize];
	int		i = 0;

	memset(used, 0, sizeof(int)*numsSize);
	memset(rst_buf, 0, sizeof(int)*numsSize);
	// 在题目中传入的returnSize可能指向一个未初始化的空间，导致错误。
	// 所以这里在使用前进行强制初始化
	*returnSize = 0;
	arrange(nums, numsSize, used, rst_buf, 0, rst_list, returnSize);

	for (i = 0; i < *returnSize; ++i) {
		colsize_array[i] = numsSize;
	}
	*returnColumnSizes = colsize_array;
	return rst_list;
}

int main(int argc, char* argv[])
{
	int	nums[] = {1, 2, 3};
	int	returnSize = 0;
	int* colsize_array = NULL;
	int	i = 0;
	int	j = 0;

	int**	rst_list = permute(nums, sizeof(nums)/sizeof(nums[0]), &returnSize, &colsize_array);

	for (i = 0; i < returnSize; ++i) {
		for (j = 0; j < sizeof(nums)/sizeof(nums[0]); ++j) {
			printf("%d ", rst_list[i][j]);
		}
		printf("\r\n");
	}
}
