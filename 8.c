/********************************************************
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转
 * 换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
 *
 * 本题中的空白字符只包括空格字符 ' ' 。
 * 除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
 * 
 * 2021年 07月 08日 星期四 15:51:35 CST
 * ******************************************************/

/**
 * 从字符串开头开始逐个遍历，遇到不满足条件时退出
 * 取到的字符通过与字符0做差转换成整型数字，然后
 * 按照10进制累加上去，最后判断范围
 */
int myAtoi(char * s)
{
	long long rst = 0;	
	int	i = 0;
	int	start_flag = 0;
	int	symbol = 1;

	//去除前导空格
	for (i = 0; s[i] != 0 && s[i] == ' '; ++i) {}

	//判断是会否有符号
	if (s[i] == '+') {
		++i;
	} else if (s[i] == '-') {
		symbol = -1;
		++i;
	}
	//逐个字符计算
	for (; s[i] != 0; ++i) {
		if (s[i] > '9' || s[i] < '0')
			break;
		rst = rst*10 + (s[i] - '0');
		if (rst > 0x7fffffff)
			break;
	}
	rst *= symbol;
	
	if (rst > 0x7fffffff)
		return 0x7fffffff;
	else if (rst < (signed int)0x80000000)
		return (signed int)0x80000000;
	return (int)rst;
}

int main(int argc, char* argv[])
{
	printf("rst = %d\r\n", myAtoi(argv[1]));
}

