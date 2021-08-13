#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* prase_num(char* buf)
{
	char*    start = buf;
	char*    end = NULL;
	char*	 valid = calloc(1, strlen(buf) + 1);
	

	printf("input = %s\r\n", buf);
	start = strstr(buf, "0x");
	end = start;
	while (*end != ' ' && *end != 0)
		end++;
	strncpy(valid, start, end - start);
	printf("output = %s\r\n", valid);
	return valid;
}
int trans_num(char* buf)
{
	int        step = 1;
	int        i = 0;
	int        num = 0;

	//跳过0x字符
	for (i = strlen(buf)-1; i > 1; --i) {
		if (buf[i] >= 'A')
			num += step*(buf[i] - 'A' + 10);
		else if (buf[i] >= '0' && buf[i] <= '9')
			num += step*(buf[i] - '0');
		else
			return -1;
		step *= 16;
	}
	return num;
}
int main(int argc, char* argv[])
{
	char*     num_valid = NULL;
	int       nums_size = 0;
	int       num_rst = 0;
	int       i = 0;
	char      input_buf[1024] = {0};


	while (scanf("%s", input_buf) != EOF) {
		num_valid = prase_num(input_buf);
		if (num_valid) {
			num_rst = trans_num(num_valid);
			if (num_rst != -1)
				printf("%d\r\n", num_rst);
			free(num_valid);
		}
		memset(input_buf, 0, sizeof(input_buf));
	}
}
