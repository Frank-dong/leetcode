/********************************************************
 * 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函
 * 数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何
 * 一种硬币组合能组成总金额，返回 -1。
 *
 * 你可以认为每种硬币的数量是无限的。
 * ******************************************************/
#include "tools.h"
#include "stdio.h"

/********************************************************
 * 分析(递归方法)
 * 总金额amount是由另一个较小金额(子总金额)加其中某一个 硬币而得到。
 * 那能达到总金额amount的路径就有数组元素个数条。那找到这些"子
 * 总金额"中路径最短的。就跟原问题相似了
 * 
 * 假设要达到的目标总金额是T，硬币数组是[c1, c2...cn]
 * 原问题: 达到T所需的所需的最少硬币数
 * 子问题: 达到T-c1, T-c2..T-cn 所需要的最少硬币数
 *
 * 状态转移方程
 * f(T) = min(f(T-c1), f(T-c2)..f(T-cn)) + 1
 * T-c < 0   f(T-c) = -1	//无效
 * T-c = 0   f(T-c) = 0		//表示已凑齐
 * ******************************************************/
int coinChange_dg(int* coins, int coinsSize, int amount)
{
	int		coin_count = 0;
	int		i = 0;
	int		min_num = -1;
	int		ret = 0;
	static int amount_pre = 0;
	static int*	amount_array = NULL;

	if (!coins || coinsSize <= 0 || amount < 0)
		return -1;

	if (amount == 0)
		return 0;

	if (!amount_array) {
		amount_pre = amount;
		// 申请的这个数组相当于就是备忘录，记录所有限额下的最优解
		amount_array = calloc(1, sizeof(int)*amount);
		for (i = 0; i < amount; ++i)
			amount_array[i] = -2;
	}

    // 如果没计算过，就计算当前总金额下需要的最小个数
	if (amount_array[amount - 1] == -2) {
	    // 这里的for循环，是为了寻找到多个硬币路线下的最小个数
		for (i = 0; i < coinsSize; ++i) {
			if (amount - coins[i] < 0) {
                // 如果当前面值较大，则不需要
				coin_count = -1;
			} else if (amount - coins[i] == 0) {
				coin_count = 0; // 刚好凑齐，就是说当前这个硬币下的路径最小是0
				                // 也就是说在这个限额下，其他的硬币都不要，只要这一个就行了。
			} else {
			    // 如果拿了当前这个硬币，还有一定的剩余额度，就递归求解一下。
				coin_count= coinChange_dg(coins, coinsSize, amount - coins[i]);
		    }

            // 通过多个硬币路线的比较，去一个最小值
			if ((min_num < 0 && coin_count >= 0) || (coin_count >= 0 && coin_count < min_num))
				min_num = coin_count;
		}
		// 最小值有效就更新，否则就是都不合适
		amount_array[amount - 1] = min_num < 0 ? -1: min_num + 1;
	}
	ret = amount_array[amount - 1];
	if (amount == amount_pre) {
		free(amount_array);
		amount_array = NULL;
		amount_pre = 0;
	}
	return ret;
}

/********************************************************
 * 分析(动态规划, 计算过程自底向上)
 * 总金额amount是由另一个较小金额(子总金额)加其中某一个 硬币而得到。
 * 那能达到总金额amount的路径就有数组元素个数条。那找到这些"子
 * 总金额"中路径最短的。就跟原问题相似了
 * 
 * 假设要达到的目标总金额是T，硬币数组是[c1, c2...cn]
 * 原问题: 达到T所需的所需的最少硬币数
 * 子问题: 达到T-c1, T-c2..T-cn 所需要的最少硬币数
 *
 * 状态转移方程
 * f(T) = min(f(T-c1), f(T-c2)..f(T-cn)) + 1
 * T-c < 0   f(T-c) = -1	//无效
 * T-c = 0   f(T-c) = 0		//表示已凑齐
 * ******************************************************/
int coinChange_dp(int* coins, int coinsSize, int amount)
{
	//建立一个dp数组,个数为amount + 1个
	int*	amount_dp = NULL;
	//创建一个数组用来保存每个硬币路径的个数
	int		i = 0;
	int		j = 0;
	int		min_num = 0;
	int		tmp = 0;

	if (!coins || coinsSize < 0 || amount < 0)
		return -1;

	if (amount == 0)
		return 0;

	amount_dp = calloc(1, sizeof(int)*(amount + 1));
	amount_dp[0] = -1;

    // 两个限制条件，则两层循环
	// 开始从底开始计算

	// 第一层限额从小到大
	for (i = 1; i <= amount; i++) {
		min_num = -2;	//标记此变量未赋值

		// 寻找出多条硬币路线中个数 最少的一条
		for (j = 0; j < coinsSize; ++j) {
			//子问题目标是凑够 i - coins[j] 的问题（也就是确定带当前一枚硬币，然后计算剩下的额度适合带的硬币，这个在之前已经记录过了），
			// 在整个算完之后，在统计amount_dp[i] 的时候，如果有效，还会再加1，也就是确定待上这枚硬币，如果都无效，那这个值也就无效了。 
			tmp = i - coins[j];
			if (tmp == 0) {
				min_num = 0;    // 这条就是最少的了，不用继续找了
				break;
			} else if (tmp > 0) {
			    // 
				if (min_num != -2) // 找到几条中更小的
					min_num = (min_num > amount_dp[tmp] && amount_dp[tmp] >= 0) ? amount_dp[tmp] : min_num;
				else    // 如果还没找到合适的路线，那就更新路线为
					min_num = amount_dp[tmp] >= 0 ? amount_dp[tmp] : min_num;
			}
		}
		amount_dp[i] = min_num == -2 ? -1 : min_num + 1;
		//printf("amount_dp[%d] = %d\r\n", i, amount_dp[i]);
	}
	tmp = amount_dp[amount];
	free(amount_dp);
	return tmp;
}
//-------------------------------------------------
/*****
 * 下面是leetcode上网友的解决方法, 耗时很短
 **/
#include "limits.h"
#include <math.h>
int myCmp(int *a, int *b)
{
	    return *b > *a;
}
int g_min;
void backtrack(int* coins, int coinsSize, int amount, int index, int cnt)
{
	// amount为0，表示已凑齐了指定钱数；
	if (amount == 0) {
		g_min = fmin(cnt, g_min);
		return;
	}
	// 到达边界，返回；
	if (index == coinsSize) {
		return;
	}

	// 从最大的钱币，按照数量从多到少遍历，注意性能优化点：addcnt + cnt < g_min
	for (int addcnt = amount / coins[index]; addcnt >= 0 && cnt + addcnt < g_min; addcnt--) {
		if (cnt + addcnt < g_min) {
			backtrack(coins, coinsSize, amount - addcnt * coins[index], index + 1, cnt + addcnt);
		}
	}
}

int coinChange(int* coins, int coinsSize, int amount){
	qsort(coins, coinsSize, sizeof(int), myCmp);
	g_min = INT_MAX;
	backtrack(coins, coinsSize, amount, 0, 0);

	// [288,160,10,249,40,77,314,429] 9208
	// 当输入如上用例的时候，g_count = 808401654，函数backtrack调用非常多，如果不做性能优化，性能会超时；

	return g_min < INT_MAX ? g_min : -1;
}
//-------------------------------------------------

int main(int argc, char* argv[])
{
	int*	coin_array = NULL;
	int		i = 0;


	if (argc < 3) {
		printf("Usage: %s <coin_1> <coin_2> ... <coin_n> <amount>\r\n", argv[0]);
		return 0;
	}

	coin_array = calloc(1, sizeof(int)*(argc-2));
	for (i = 1; i < argc - 1; ++i) {
		coin_array[i-1] = atoi(argv[i]);
	}

	printf("need coins least : %d\r\n", coinChange(coin_array, argc-2, atoi(argv[argc-1])));
}

