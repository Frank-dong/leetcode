/********************************************************
 * 背包问题:是指给定一组物品，每种物品都有自己的重量和价值
 * 要求在不超过一定重量W的情况下，获取最大价值V的一类问题。
 *
 * 如果每种物品限定选择0个或者1个，称为0-1背包问题.
 * 如果物品j限定最多选择Bj个，称为有界背包问题.
 * 如果不限定每种物品的数量，称为无界背包问题.
 *
 * 参考链接：
 *	https://zhuanlan.zhihu.com/p/93857890?utm_source=wechat_session
 *  https://www.bilibili.com/video/BV1tp4y167c5?p=24
 * ******************************************************/

/**
 * 0-1背包问题
 * 假设物品重量分别是W1,W2,W3,,,Wn
 * 物品价值分贝是V1,V2,V3,,,Vn
 *
 * 原问题：在不超过总重量W的情况下从全部n件物品中获取最大价值
 * 子问题：在不超过W的情况下，从前n-1件物品中获取最大价值 与
 *         在不超过W-Wn的情况下，从n-1件物品获取最大价值+Vn的较大值
 *
 * 状态转义方程
 * f(n, W) = {
 *		//这里n表示下标计数，程序中从0开始计数
 *		n = 1, f(1, W) = Wn > W ? Vn : 0
 *		n = 2, f(2, W) = max(f(1, W), f(1, W-W1) + V1)
 *		...
 *		n = N, f(N, W) = max(f(N-1, W), f(N-1), W-WN + VN)
 * }
 *
 * 定义DP数组：由状态转义方程可以看出,需要计算的子问题个数有N*W个，
 * 也就是要计算有n(0<=n<=N)个物品,限重分别为w(0<=w<=W)的情况下的
 * 最大价值.
 */

#include <stdio.h>

/**
 * 假设物品的价值和重量都是正整数
 */
struct thing {
	int	weight;
	int	value;
};

int zero_one_package(struct thing* things_list, int num, int weight_limit)
{
	int		i = 0;
	int		j = 0;
	int		tmp_limit = 0;
	int**	dp_array = NULL;

	dp_array = calloc(1, sizeof(void*)*num);
	for (i = 0; i < num; ++i) {
		dp_array[i] = calloc(1, sizeof(int)*(weight_limit+1));
	}

	for (i = 0; i < num; ++i) {					// 物品数量
		for (j = 1; j <= weight_limit; ++j) {	// 限重范围
			if (i == 0) {
				dp_array[0][j] = things_list[0].weight > j ? 0 : things_list[0].value;
			} else {
				if (j < things_list[i].weight) {
					// 当前物品超过限重时, 肯定不能带
					dp_array[i][j] = dp_array[i-1][j];
				} else {
					// 当前物品不超过时, 可带可不带，需要做比较
					tmp_limit = j - things_list[i].weight;
					if (tmp_limit <= 0)
						dp_array[i][j] = dp_array[i-1][j] > things_list[i].value ? 
											dp_array[i-1][j] : things_list[i].value;
					else
						dp_array[i][j] = dp_array[i-1][j] > (dp_array[i-1][tmp_limit] + things_list[i].value) 
										? dp_array[i-1][j] : (dp_array[i-1][tmp_limit] + things_list[i].value);
				}
			}
			//printf("dp[%d][%d] = %d\r\n", i, j, dp_array[i][j]);
		}
	}
	return dp_array[num-1][weight_limit];
}

int main(int argc, char*argv[])
{
	struct thing thing_list[10] = {
		{6, 540},
		{3, 200},
		{4, 180},
		{5, 350},
		{1, 60},
		{2, 150},
		{3, 280},
		{5, 450},
		{4, 320},
		{2, 120},
	};
	
	printf("rst = %d.\r\n", zero_one_package(thing_list, 10, 30));
}