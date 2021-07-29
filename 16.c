/********************************************************
 * 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。
 * 找出 nums 中的三个整数，使得它们的和与 target 最接近。
 * 返回这三个数的和。假定每组输入只存在唯一答案。
 *
 * ******************************************************/
#include <stdlib.h>
#include <stdio.h>

/**
 * 这道题与15题比较相似，只不过15题求解的是确定值，并且
 * 可能有多个结果，这道题目是求一个接近值，同时假定只有
 * 一组结果，所以最后肯定是有一个结果的。
 *
 * 所以同样是先排序，然后利用双指针的方法来求解
 */

int compare_func(const void *num1, const void *num2)
{
	return *((int*)num1) - *((int*)num2);
}
int threeSumClosest(int* nums, int numsSize, int target)
{
	int	first = 0;
	int	second = 0;
	int	third = 0;
	int	cur = 0;
	int	sum = 0;
	int	tmp = 0;
	int	near_target = abs(nums[0] + nums[1] + nums[2] - target);
	int	rst = nums[0] + nums[1] + nums[2];

	qsort(nums, numsSize, sizeof(int), compare_func);

	for (first = 0; first < numsSize - 2; ++first) {
		if (first > 0 && nums[first] == nums[first-1])
			continue;
		// 先确定第一个数值，然后从头和尾两边去枚举后面两个数
		third = numsSize - 1;
#if 0
		// 这样操作是第二次定位b，轮询c，其实不是双指针的思想
		// 应该分情况考虑这次是移动b，还是移动c
		for (second = first + 1; second < numsSize-1; ++second) {
			if (second > first + 1 && nums[second] == nums[second-1])
				continue;
			for (; third > second; --third) {
				sum = nums[first] + nums[second] + nums[third];	
				cur = abs(sum - target);
				if (cur == 0)
					return target;
				rst = rst > cur ? cur : rst;
			}
		}
#else
		second = first + 1;
		while (second < third) {
			sum = nums[first] + nums[second] + nums[third];	
			cur = abs(sum - target);
			printf("sum = %d, cur = %d\r\n", sum, cur);
			if (cur == 0)
				return target;
			if (near_target > cur) {
				near_target = cur;
				rst = sum;
				printf("update rst = %d\r\n", rst);
			}
			if (sum > target) {	// 如果和大于target，需要移动c，在数轴上靠近target
				tmp = nums[third];
				while (nums[--third] == tmp && second < third);	// 跳过相同的数值
			} else {	//移动b
				tmp = nums[second];
				while (nums[++second] == tmp && second < third);	// 跳过相同的数值
			}
			
		}
#endif
	}

	return rst;
}

int main(int argc, char* argv[])
{
	//int	nums[] = {-1,2,1,-4};
	//int	nums[] = {0, 0, 0};
	int	nums[] = {1, 1, 1, 0};

	printf("rst = %d\r\n", threeSumClosest(nums, sizeof(nums)/sizeof(nums[0]), atoi(argv[1])));

	return 0;
}
