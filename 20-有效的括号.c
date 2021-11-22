/********************************************************
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 
 * s ，判断字符串是否有效。
 *
 * 有效字符串需满足：
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 *
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct char_list {
	char	left;
	char	right;
} g_chr_list[] = {
	{'[', ']'},
	{'{', '}'},
	{'(', ')'},
};

char pair_char(char c)
{
	int	i = 0;
	for (i = 0; i < sizeof(g_chr_list)/sizeof(g_chr_list[0]); ++i) {
		if (c == g_chr_list[i].right)
			return g_chr_list[i].left;
	}
	return 0;
}
/**
 * 成对出现的类型，最适合用栈的方法来处理
 */
bool isValid(char * s)
{
	int	deep = 0;
	int	top = -1;
	int	i = 0;
	int	chr = 0;

	if (!s)
		return false;

	deep = strlen(s);
	int	stack[deep];
	memset(stack, 0, deep*sizeof(int));
	for (i = 0; i < deep; ++i) {
		chr = pair_char(s[i]);
		printf("input %c, output %c\r\n", s[i], chr);
		if (chr) {	// 遇到右括号,则出栈一个左括号，若不匹配，就是无效的括号
			if (top < 0 || (stack[top--] != chr)) {
				return false;
			}
		} else {	// 左括号入栈
			stack[++top] = s[i];
		}
	}
	if (top >= 0)
		return false;
	return true;
}

int main(int argc, char* argv[])
{
	printf("%s\r\n", isValid(argv[1]) ? "true" : "false");
}
