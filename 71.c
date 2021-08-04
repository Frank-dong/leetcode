/********************************************************
 * 给你一个字符串 path ，表示指向某一文件或目录的 Unix 
 * 风格 绝对路径 （以 '/' 开头），请你将其转化为更加简洁
 * 的规范路径。
 *
 * 在 Unix 风格的文件系统中，一个点（.）表示当前目录本
 * 身；此外，两个点 （..） 表示将目录切换到上一级（指向
 * 父目录）；两者都可以是复杂相对路径的组成部分。任意多
 * 个连续的斜杠（即，'//'）都被视为单个斜杠 '/' 。 对于
 * 此问题，任何其他格式的点（例如，'...'）均被视为文
 * 件/目录名称。
 *
 * 请注意，返回的 规范路径 必须遵循下述格式：
 *		始终以斜杠 '/' 开头。
 * 		两个目录名之间必须只有一个斜杠 '/' 。
 * 		最后一个目录名（如果存在）不能 以 '/' 结尾。
 * 		此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
 * 		返回简化后得到的 规范路径 。
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 几种臃肿的路径表示方法中只有使用..相对路径的不好处理，
 * 其它多余的几个可以直接做忽略处理。
 * 对于向上反溯的问题，可以利用栈的思想来处理。这里也是
 * 一样，逐个入栈，该忽略的忽略，遇到../就出栈一个元素,
 * 将最后剩余的元素拼接起来就行了.
 */

/**
 * 审题不清：题目中提到除了 . 和 .. ，其他形式的点，比如
 * ...视为文件或者目录的组成部分。
 * 下面这个对这个情况没有考虑，所以出错了
 */
char * simplifyPath(char * path)
{
	char*	path_stack = NULL;
	char*	path_pos = path;
	char*	stack_top = NULL;

	path_stack = calloc(1, strlen(path) + 1);
	stack_top = path_stack;
	while (*path_pos) {
		// 如果是.. ,则从栈中弹出一层路径
		if (*path_pos == '.' && *(path_pos+1) == '.') {
			if ((stack_top-1) > path_stack) {
				*--stack_top = 0;
				while (stack_top != path_stack && *stack_top != '/')
					*stack_top-- = 0;
				stack_top++;
			}
			path_pos += 2;
		} else if (*path_pos == '.' || (*path_pos == '/' && 
				 (stack_top > path_stack && *(stack_top-1) == '/'))) {
			path_pos++;
			continue;
		} else {
			*stack_top++ = *path_pos++;
		}
	}

	if ((stack_top-1) != path_stack && *(stack_top-1) == '/')
		*(stack_top-1) = 0;
	printf("stack: %s\r\n", path_stack);
	return path_stack;
}

void main(int argc, char* argv[])
{
	//char	str[] = "/a/./b/../../c/";
	//char	str[] = "/../";
	char	str[] = "/";

	simplifyPath(str);
}
