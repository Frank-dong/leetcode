/********************************************************
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的
 * 一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两
 * 个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使
 * 得它们与 x 轴共同构成的容器可以容纳最多的水。
 *
 * 说明：你不能倾斜容器。
 *
 * ******************************************************/

#include "stdio.h"
#include "tools.h"



/**
 * 最简单的方法就是两层循环，通过比较得到最大的值
 * 但是这个方法的时间复杂度是n^2,不符合测试要求
 */
int maxArea(int* height, int heightSize)
{
	int		i = 0;
	int		j = 0;
	int		cubage = 0;
	int		max = 0;

	for (i = 0; i < heightSize; ++i) {
		for (j = i+1; j < heightSize; ++j) {
			cubage = (height[i]	> height[j] ? height[j] : height[i]) * (j-i);
			max = max < cubage ? cubage : max;
		}
	}

	return max;
}


/**
 * 滑动窗口方法
 * 计算最大容积，就是两个边中的短边和距离的乘积。
 * 通过观察可以发现，收缩长边，得到的结果肯定小于或者
 * 等于当前结果。收缩短边，得到的结果可能变大，也可能
 * 变小。所以采取收缩短边的方式，逐个遍历，得到最大值
 */
int maxArea(int* height, int heightSize)
{
	int		i = 0;
	int		j = 0;
	int		cubage = 0;
	int		max = 0;

	j = heightSize-1;
	while (i < j) {
		if (height[i] < height[j]) {
			cubage = height[i] * (j - i);
			++i;
		} else {
			cubage = height[j] * (j - i);
			--j;
		}
		max = max < cubage ? cubage : max;
	}

	return max;
}

int main(int argc, char* argv)
{
	int	nums[10];
	int	i = 0;

	create_nums(nums, 10, 1, 10);
	for (i = 0; i < 10; ++i) 
		printf("%d ", nums[i]);
	printf("\r\n");

	printf("max cubage = %d\r\n", maxArea(nums, 10));
}
