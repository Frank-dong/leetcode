/********************************************************
 * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定
 * 的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通 
 * 的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 *
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你不触动警
 * 报装置的情况下 ，一夜之内能够偷窃到的最高金额。
 * ******************************************************/
#include "stdio.h"
#include "tools.h"
#include "stdlib.h"


/**
 * 递归方法
 * 状态转移方程
 * f(n) =  {
 *     n = 1   M(1) 
 *     n = 2   max(M(1), M(2))
 *     n >= 3  max(f(n-2)+M(n), f(n-1))
 * }
 */
int rob_dg(int* nums, int numsSize){
	int	m1 = 0;
	int	m2 = 0;

	if (numsSize <= 0 || nums == NULL)
		return 0;
	if (numsSize == 1)
		return nums[0];
	else if (numsSize == 2)
		return nums[0] > nums[1] ? nums[0] : nums[1];
	else	
		m1 = rob_dg(nums, numsSize - 2) + nums[numsSize - 1];
		m2 = rob_dg(nums, numsSize - 1);
		return m1 > m2 ? m1 : m2;
}


/**
 * 动态规划(自底向上)
 * 状态转移方程
 * f(n) =  {
 *     n = 1   f(1) = M(0) 
 *     n = 2   f(2) = max(M(1), M(0))
 *     n = 3   f(3) = max(f(2), f(1) + M2)
 *     n = 4   f(4) = max(f(3), f(2) + M3)
 *     n = 5   f(5) = max(f(4), f(3) + M4)
 *     ...
 *     n = N   f(N) = max(f(N-1), f(n-2) + M(N-1))
 *   注意:后面计算过程中需要的一些子问题，在前面已经得到了计算(前面计算后需要将结果保留下来)
 * }
 */
int rob_dp(int* nums, int numsSize){
	int	i = 0;
	int*	total_num = NULL;

	if (numsSize <= 0 || nums == NULL)
		return 0;

	total_num = calloc(1, numsSize * sizeof(int));
	if (numsSize == 1) {
		return nums[0];
	} else if (numsSize == 2) {
		return nums[0] > nums[1] ? nums[0] : nums[1];
	} else {
		total_num[0] = nums[0];
		total_num[1] = nums[1] > nums[0] ? nums[1] : nums[0];
		for (i = 2; i < numsSize; ++i) {
			total_num[i] = total_num[i - 1] > (total_num[i - 2] + nums[i])
				 ? total_num[i - 1] : (total_num[i - 2] + nums[i]); 	
		}	
		return total_num[numsSize - 1];
	}
}

/**
 * 动态规划(自底向上), 内存优化
 * 状态转移方程
 * f(n) =  {
 *     n = 1   f(1) = M(0) 
 *     n = 2   f(2) = max(M(1), M(0))
 *     n = 3   f(3) = max(f(2), f(1) + M2)
 *     n = 4   f(4) = max(f(3), f(2) + M3)
 *     n = 5   f(5) = max(f(4), f(3) + M4)
 *     ...
 *     n = N   f(N) = max(f(N-1), f(n-2) + M(N-1))
 *   注意:后面计算过程中需要的一些子问题，在前面已
 *        经得到了计算(前面计算后需要将结果保留下来)
 *   内存优化：每个计算当前N个房子的最大总数，其实只需要前N-2和前N-1个
 *        房子的偷窃最大值, 所以只需要记录下当前结果和上次结果就可以
 *        为下次计算做好准备了。
 * }
 */
int rob_dp_mem(int* nums, int numsSize){
	int	total_cur = 0;
	int	total_pre = 0;
	int	tmp = 0;
	int	i = 0;

	if (numsSize <= 0 || nums == NULL)
		return 0;

	if (numsSize == 1) {
		return nums[0];
	} else if (numsSize == 2) {
		return nums[0] > nums[1] ? nums[0] : nums[1];
	} else {
		total_pre = nums[0];
		total_cur = nums[1] > nums[0] ? nums[1] : nums[0];
		for (i = 2; i < numsSize; ++i) {
			tmp = total_cur > total_pre + nums[i] ? total_cur : total_pre + nums[i];
			total_pre = total_cur;
			total_cur = tmp;
			
		}	
		return total_cur;
	}
}

#define NUMS_COUNT	40
int main(int argc, char* argv[])
{
	int	nums[NUMS_COUNT] = {0};

	create_nums(nums, NUMS_COUNT, 0, 20);
	start_time();
	printf("total = %d\r\n", rob_dg(nums, NUMS_COUNT));
	stop_time();

	start_time();
	printf("total = %d\r\n", rob_dp_mem(nums, NUMS_COUNT));
	stop_time();
}

