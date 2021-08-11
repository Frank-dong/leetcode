/********************************************************
 * 给定一个整数数组 nums ，找到一个具有最大和的连续子数
 * 组（子数组最少包含一个元素），返回其最大和。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
/**
 * 这道题求最大和的连续子序列，由于是求子序列，所以不能提前
 * 排序，需要枚举所有可能结果，然后选出最大的值。在此过程中
 * 建立dp数组(备忘录)来省略部分运算
 *
 * 状态转移方程：
 * DP[i, j] = {
 *				= num[i] (i = j)
 *				= dp[i, j - 1] + nums[j];
 *			}
 */
/**
 * 这个方法相当于枚举出了所有的结果，时间复杂度和空间复杂度都是O(n^2)
 */
int maxSubArray(int* nums, int numsSize)
{
	int		max = INT_MIN;
	int		i = 0;
	int		j = 0;
	// 对于未知大小的数组，最好动态申请空间，不要直接定义
	// 容易导致函数栈溢出
#if 0
	int		dp[numsSize][numsSize];

	for (i = 0; i < numsSize; ++i) {
		for (j = 0; j < numsSize; ++j) 
			dp[i][j] = 0;
	}
#else
	printf("numsSize = %d\r\n", numsSize);
	int**	dp = calloc(1, sizeof(void*)*numsSize);
	for (i = 0; i < numsSize; ++i) {
		dp[i] = calloc(1, sizeof(int)*numsSize);
	}
#endif
	printf("start calc...\r\n");
	for (i = 0; i < numsSize; ++i) {
		for (j = i; j < numsSize; ++j) {
			if (i == j) {
				dp[i][j] = nums[i];
			} else {
				dp[i][j] = dp[i][j-1] + nums[j];
			}
			max = max < dp[i][j] ? dp[i][j] : max;
			//printf("max = %d\r\n", max);
		}
	}
	return max;
}

/**
 * 再次审题，转换思路，把关注点放在题目的最终解上，即最终
 * 求解的最大值上。求出以i下标结尾的子串的最大和，这样就只用
 * 一个一位数组就可以保存dp结果。
 * 
 * 这里最关键的一个思维转换是要看当前节点的值是正作用还是反作用
 * 以此来判断是否丢弃从此节点开启一个新的区间.
 *
 * 考虑nums[i]是单独成为一段，还是加入上一个段，结果取决于
 * dp[i-1]+nums[i] 和 nums[i] 的值. 通过这个也可以看出来，当前结果只
 * 与上一结果相关，所以也不用一维数组了，一个整形变量保存即可。 
 * 这样时间复杂度就降低为O(n)， 空间复杂度降低为O(1)
 *
 * 其实这个也可以理解为是贪心算法的一种
 */
int maxSubArray_1(int* nums, int numsSize)
{
	int		max = INT_MIN;	
	int		pre = 0;
	int		i = 0;

	pre = 0;
	for (i = 0; i < numsSize; ++i) {
		//pre = (pre + nums[i]) > pre ? (pre + nums[i]) : pre;
		//max = max < pre ? pre : max;
		/** 
		 * 这一处理不好理解，由于是限制连续数列，所以这里比较的是
		 * 前面的数列和+当前节点 和 当前节点的值作比较
		 * 相当于是判断前面的节点对当前节点起正作用(增大)还是反作用(减小)
		 * 所以这里其实还可以有另外一种表达方式
		 */
		//pre = fmax(pre + nums[i], nums[i]);	
		pre = pre < 0 ? nums[i] : (pre + nums[i]);
		max = fmax(max, pre);
	}
	return max;
}

int main(int argc, char* argv[])
{
	int	nums[] = {-2,1,-3,4,-1,2,1,-5,4};

	printf("num = %d\r\n", sizeof(nums)/sizeof(nums[0]));
	printf("max = %d\r\n", maxSubArray_1(nums, sizeof(nums)/sizeof(nums[0])));
}
