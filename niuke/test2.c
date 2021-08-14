#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[])
{
	int     chr_list[26] = {0};
	char    input_buf[2000] = {0};
	char    chr_stack[2000] = {0};
	int     stack_top = 0;
	int     min = INT_MAX;
	int     len = 0;
	int     i = 0;

	while(scanf("%s", input_buf) != EOF) {
		len = strlen(input_buf);
		// 找出最小的字母个数
			for (i = 0; i < len; ++i) {
				chr_list[input_buf[i] - 'a']++;
			}   

		for (i = 0; i < 26; ++i) {
			if (chr_list[i] != 0) {
				min = min < chr_list[i] ? min : chr_list[i];    
			}   
		}   

		// 遍历拷贝
		for (i = 0; i < len; ++i) {
			if (chr_list[input_buf[i] - 'a'] != min) {
				printf("get %c\r\n", input_buf[i]);
				chr_stack[stack_top++] = input_buf[i];
			}   
		}   

		// 输出
		if (strlen(chr_stack)) {
			printf("%s\r\n", chr_stack);
		} else {
			printf("empty\r\n");
			//printf("");
		}   
		memset(input_buf, 0, sizeof(input_buf));
		memset(chr_stack, 0, sizeof(chr_stack));
		memset(chr_list, 0, sizeof(chr_list));
		min = INT_MAX;
		stack_top = 0;
	}   
	return 0;
}
