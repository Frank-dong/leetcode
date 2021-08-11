/********************************************************
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往
 * 下、从左到右进行 Z 字形排列。之后，你的输出需要从左往
 * 右逐行读取，产生出一个新的字符串
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
 * 这个题有两种大的解题思路，一种是暴力罗列，先得到每行的字母，
 * 然后把所有行拼接起来，这种方式内存消耗大，因为要给每行分配内存
 * 来临时存储字符串
 *
 * 另一种是通过计算新串与原串之间的对应关系，直接填充新串。这个
 * 思路有两种实现方式，一种是从原字符串出发，遍历原字符串，将每
 * 个字符填充到新串的指定位置上。另一种是从新串出发，逐个位置寻
 * 找应该填充旧串的某个位置的字符。相比较来说，第二种更容易理解
 * 和找到合适的规律，也就更容易实现一些。
 */

/**
 * 每一行先单独保存，通过找规律，直接填充到对应的行, 最后再合并
 */
char * convert_1(char * s, int numRows)
{
	int	column = 0;
	int	i = 0;
	int	cur_col = 0;
	int	direct = 0; 
	int	rows = 0;
	int*	len_list = NULL;
	char*	new_str = NULL;
	char**	col_list = NULL;
	
	new_str = calloc(1, strlen(s) + 1);
 	if (numRows == 1) {
		strcpy(new_str, s);
		return new_str;	
	}

	rows = strlen(s) > numRows ? numRows : strlen(s);	
	col_list = calloc(1, sizeof(void*)*rows);
	for (i = 0; i < rows; ++i) {
		//此处偷懒了，准确的做法应该是计算得到总共多少列，然后分配内存
		col_list[i] = calloc(1, 1000);
	}
	
	for (i = 0; i < strlen(s); ++i) {
		col_list[cur_col][strlen(col_list[cur_col])] = *(s+i);
		if (cur_col == 0 || cur_col == (numRows-1))
			direct = !direct;	
		cur_col += (direct == 0 ? -1 : 1);
	}
	
	for (i = 0; i < rows; ++i) {
		strcat(new_str, col_list[i]);
		free(col_list[i]);
	}	
	free(len_list);
	free(col_list);
	return new_str;
}

/** 
 * 直接找位置关系填充
 */
char * convert_2(char * s, int numRows)
{
	int		str_len = 0;
	int		pos = 0;
	int		i = 0;
	int		j = 0;
	int		circle_len = 0;
	char*	new_str = NULL;

	if (numRows == 1) {
		return s;
	}
	// 计算得到循环单元长度
	circle_len = 2 * numRows - 2;
	str_len = strlen(s);
	new_str = calloc(1, sizeof(char)*(str_len+1));	
	for (i = 0; i < numRows; ++i) {
		for (j = 0; j < str_len; ++j) {
			// 遍历字符串，将符合条件的字符填入新字符串中
			if (j % circle_len == i || j % circle_len == (circle_len - i))
				new_str[pos++] = *(s+j);
		}
	}
	return new_str;
}

int main(int argc, char* argv[])
{
	char*	rst = NULL;

	rst = convert_z(argv[1], atoi(argv[2]));
	printf("rst = \r\n%s\r\n", rst);
	free(rst);
	rst = convert_1(argv[1], atoi(argv[2]));
	printf("rst = \r\n%s\r\n", rst);
	if (rst != argv[1])
		free(rst);

	return 0;
}

