#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char*    str_list[100];
	char*    start = NULL;
	char*    end = NULL;
	char    input_buf[1000] = {0};
	int     sec_num = 0;


	gets(input_buf);
	start = input_buf;
	while (start) {
		// 按照空格拆分
		end = strchr(start, ' ');
		if (!end) {
			str_list[sec_num] = calloc(1, strlen(start) + 1);
			strcpy(str_list[sec_num], start);
			sec_num++;
			break;
		}

		str_list[sec_num] = calloc(1, end - start + 1);
		strncpy(str_list[sec_num], start, end - start);
		sec_num++;
		start = end + 1;
	}

	while (sec_num > 0) {
		printf("%s", str_list[sec_num-1]);
		if (sec_num > 0)
			printf(" ");
		sec_num--;
	}
	printf("\r\n");

	return 0;
}
