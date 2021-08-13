#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char	input_buf[5000] = {0};
	int		len = 0;
	int		end = 0;
	int		pos = 0;

#if 0
	while (scanf("%s", input_buf) != EOF) {
		len = strlen(input_buf);
		memset(input_buf, 0, sizeof(input_buf));
	}
	printf("%d\r\n", len);
#else
	//while (scanf("%s", input_buf) != EOF) {
	while (gets(input_buf) != NULL) {
		printf("input_buf = %s\r\n", input_buf);
		pos = strlen(input_buf) - 1;
		// 去除末尾的空格
		while (input_buf[pos] == ' ')
			--pos;
		end = pos;
		// 寻找下一个空格
		while (pos > 0 && input_buf[pos] != ' ')
			--pos;
		if (pos == 0)
			pos = -1;
		printf("%d\r\n", end - pos);
		memset(input_buf, 0, sizeof(input_buf));
	}
#endif
}
