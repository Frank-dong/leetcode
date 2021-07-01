/********************************************************
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往
 * 下、从左到右进行 Z 字形排列。
 * |  /|  /|
 * | / | / |
 * |/  |/  |
 *
 * 
 * 2021年 06月 30日 星期三 18:47:46 CST
 * ******************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * 审题错误，不是要打印出Z字形结果，而是要打印以Z字形结果
 * 排列后的顺序。
 */
char * convert_z(char * s, int numRows)
{
	int	s_len = 0;
	int	unit_num = 0;
	int	tmp = 0;
	int	column = 0;
	int	i = 0;
	int	j = 0;
	int	pos = 0;
	char	val = 0;
	char*	new_str = NULL;

	if (numRows == 1) {
		new_str = calloc(1, strlen(s)+1);
		strcpy(new_str, s);
		return new_str;
	}

	s_len = strlen(s);
	unit_num = s_len/(numRows-1);	
	if (unit_num%2 == 0) {	//偶数
		column = (unit_num/2)*(numRows-1);
		if (s_len%(numRows-1) != 0)
			column += 1;
	} else {
		column = (unit_num/2)*(numRows-1) + 1;
		tmp = s_len%(numRows-1);
		if (tmp > 1) {
			column += tmp-1;
		}
	}
	column += 1;
	new_str = calloc(1, sizeof(char)*(column*numRows));
	printf("%d-%d-%d\n", s_len, column, (column*numRows));
	printf("%d-%d-%d\n", s_len, column, (column*numRows));

	while (i < column) {
		if (pos >= s_len) {
			if (i == (column-1)) {
				*(new_str + j++*column + i) = '\n';
			} else {
				*(new_str + j++*column + i) = ' ';
			}
		} else {
			if (i%(numRows-1) == 0) {
				*(new_str + j++*column + i) = *(s+pos++);	
			} else {
				if (j == (numRows - 1 - i%(numRows-1)))
					*(new_str + j++*column + i) = *(s+pos++);	
				else 
					*(new_str + j++*column + i) = ' ';	
			}
		}
		if (j >= numRows) {
			j = 0;	
			i += 1;
		}
	}

	return new_str;
}


/** 
 * 这个题有两种思考路径，一种是从排布好的结构出发，寻找
 * 结果字符串与原字符串序列的关系。
 * 另一种是从原字符串出发，确定每一个字符在目标字符串的
 * 位置。相比较之下，第二种方式更容易实现。
 */
char * convert(char * s, int numRows)
{
	int	column = 0;
	int	i = 0;
	int	cur_col = 0;
	int	direct = 0; 
	char*	new_str = NULL;
	char**	col_list = NULL;
	
	new_str = calloc(1, strlen(s) + 1);
 	if (numRows == 1) {
		strcpy(new_str, s);
		return new_str;	
	}
	column = strlen(s) > numRows ? numRows : strlen(s);	
	col_list = calloc(1, sizeof(char*)*column);
	for (i = 0; i < column; ++i) {
		col_list[i] = calloc(1, sizeof(char)*(strlen(s)/column + 2));
	}
	
	for (i = 0; i < strlen(s); ++i) {
		col_list[cur_col][strlen(col_list[cur_col])] = *(s+i);
		if (cur_col == 0 || cur_col == (numRows-1))
			direct = !direct;	
		cur_col += (direct == 0 ? -1 : 1);
	}
	
	for (i = 0; i < column; ++i) {
		strcat(new_str, col_list[i]);
		free(col_list[i]);
	}	
	free(col_list);
	return new_str;
}

int main(int argc, char* argv[])
{
	char*	rst = NULL;

	rst = convert_z(argv[1], atoi(argv[2]));
	printf("rst = \r\n%s\r\n", rst);
	free(rst);
	rst = convert(argv[1], atoi(argv[2]));
	printf("rst = \r\n%s\r\n", rst);
	free(rst);

	return 0;
}

