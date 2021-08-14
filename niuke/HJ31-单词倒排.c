#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int      sec_num = 0;
	char*    str_list[100] = {0};
	char*    start = NULL;
	char*    end = NULL;
	char     input_buf[100] = {0};

	//gets(input_buf);
	fgets(input_buf, sizeof(input_buf), stdin);

	start = input_buf;
	while (*start) {
		// 找到头
		while (*start && ((*start < 'a' && *start > 'Z') || 
					*start < 'A' || *start > 'z'))
			++start;
		if (*start == 0)
			break;
		// 找到尾巴
		end = start;
		while (*end && ((*end >= 'A' && *end <= 'Z') ||
					(*end >= 'a' && *end <= 'z')))
			++end;
		str_list[sec_num] = calloc(1, end - start + 1);
		strncpy(str_list[sec_num], start, end - start);
		start = end;
		++sec_num;
	}

	while (sec_num > 0) {
		printf("%s", str_list[sec_num-1]);
		if (sec_num == 0)
			break;
		printf(" ");
		sec_num--;
	}
	printf("\r\n");

	return 0;

}
