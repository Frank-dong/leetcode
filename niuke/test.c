#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_num_list(char* buf, char* num_list, int limit)
{
	int	index = 0;	
	char*	str_pos = NULL;

	str_pos = buf;
	while (*str_pos != 0) {
		if (*str_pos != ',') {
			num_list[index++] = (*str_pos - '0') ? 1 : -1;
		}
		++str_pos;
	}
	return 0;
}

int get_max_pos(char* num_list)
{
	int	max = 0;
	int	tmp = 0;
	char*	start = num_list;
	char*	end = num_list;

	while (*start && *end) {
		// 寻找头
		while (*start == 1)	{
			++start;
		}
		// 寻找尾巴
		end = start;
		while (*end == -1) {
			++end;
		}

		// 记录一次
		if (start == num_list || *end == 0) {
			tmp = end - start;
		} else {
			tmp = end - start;
			tmp = tmp%2 == 0 ? tmp/2 : tmp/2+1;	
		}
		max = max < tmp ? tmp : max;
		start = end;
	}
	return max;
}

int main(int argc, char* argv[])
{
	char	num_list[100] = {0};	// 1有车，-1无车,0结尾
	char	input_buf[256] = {0};
	int		max_pos = 0;	
	int		flag = 0;

	while (scanf("%s", input_buf) != EOF) {
		get_num_list(input_buf, num_list, 100);
		max_pos = get_max_pos(num_list);
		printf("%d\r\n", max_pos);
	}
}
