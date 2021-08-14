#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void del_head(int* err_list, int limit)
{
	int	i = 0;
	
	for (i = 0; i < limit; ++i) {
		err_list[i] = err_list[i + 1];
	}
}

void clr_list(int* err_list, int limit)
{
	int i = 0;
	for (i = 0; i < limit; ++i) {
		err_list[i] = -1;
	}
}
int main(int argc, char* argv[])
{
	int	m = 0;	// 故障检测窗口大小
	int	t = 0;	// 故障个数门限值
	int	p = 0;	// 恢复周期个数
	int	nums[100000] = {0};
	int	nums_size = 0;
	int	i = 0;
	int* err_list = NULL;
	int	err_num = 0;
	int	min_index = 0;
	int	j = 0;

	while (scanf("%d %d %d", &m, &t, &p) != EOF) {
		while (scanf("%d", &(nums[nums_size++])) != EOF) {
			if (getchar() == '\n') {
				break;
			}
		}
#if 0
		printf("m: %d, t:%d, p:%d, nums:%d\r\n", m, t, p, nums_size);
		for (i = 0; i < nums_size; ++i) {
			printf("%d ", nums[i]);
		}
		printf("\r\n");
#endif
		err_list = calloc(1, sizeof(int)*m);	
		for (i = 0; i < m; ++i) {
			err_list[i] = -1;
		}

		// 遍历数组
		for (i = 0; i < nums_size; ++i) {
			// 判断此值是否错误
			if (nums[i] <= 0 || (i > 0 && (nums[i] < nums[i-1] || (nums[i] - nums[i-1] >= 10)))) {
				// 判断是否故障
				if (++err_num >= t) {
					err_num = 0;
					clr_list(err_list, m);
					j = i;
					for (i = j; i < j+p; ++i) {
						nums[i] = -1;
					}
					i -= 1;
				} else { // 记录并修复此值
					err_list[err_num-1] = i;
					// 开头的值, 或者前面就是错误值, 就直接丢弃
					if (i == 0 || nums[i - 1] < 0) {
						nums[i] = -1;	// 标记为丢弃的值
					} else {
						nums[i] = nums[i-1];
					}
				}
			} else {	// 此值正常
				if (i - err_list[0] + 1 > t) {
					del_head(err_list, err_num);	
				}
			}
		}

		int	max_len = 0;
		int	max_start = 0;
		int	max_end = 0;
		// 统计结果
		while (max_start < nums_size) {
			// 找到头
			while (nums[max_start] == -1) {
				max_start++;
			}
			// 
			max_end = max_start;
			while (max_end < nums_size && nums[max_end] != -1)
				max_end++;

			max_len = max_len < (max_end - max_start) ? (max_end - max_start) : max_len;
			max_start = max_end+1;
		}
		printf("%d\r\n", max_len);
	}

}
