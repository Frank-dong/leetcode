/********************************************************
 * 编写一个程序，通过填充空格来解决数独问题。
 *
 * 数独的解法需 遵循如下规则：
 *
 * 数字 1-9 在每一行只能出现一次。
 * 数字 1-9 在每一列只能出现一次。
 * 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
 * 数独部分空格内已填入了数字，空白格用 '.' 表示。
 *
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 这道题也是典型的回溯算法的题目，是要通过不断试探才能得出结果
 *
 * 路径选择：每行每格中能填的数值
 * 结束条件：最后一行试探也通过的话，就算是找到了结果，记录结果
 * 修剪条件：小的3X3区域已包含，或者横排竖排已包含
 */

bool is_valid(char** board, int row, int col, int val)
{
	int	i = 0;
	int	j = 0;
	int	offset_col = 0;
	int	offset_row = 0;

	// 横排肯定不冲突
	
	// 检查竖排是否冲突
	for (i = 0; i < 9; ++i) {
		if (board[i][col] == ('0' + val))
			return false;
	}

	// 检查3*3范围是否冲突
	offset_col = (col/3)*3;
	offset_row = (row/3)*3;
	for (i = offset_row; i < offset_row + 3; ++i) {
		for (j = offset_col; j < offset_col + 3; ++j) {
			if (board[i][j] == ('0' + val))
				return false;
		}
	}

	return true;
}
bool fill_num(char** board, char** used, int row, int col)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	static int end_flag = 0;

	if (end_flag == 1)
		return true;

	// 判断结束条件: 最后一行填满值
	for (i = 0; i < 9; ++i) {
		if (board[8][i] == '.') {
			end_flag = 0;
			break;
		}
	}
	if (i == 9) {
		printf("end\r\n");
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				printf("%c ", board[i][j]);
			}
			printf("\r\n");
		}
		end_flag = 1;
		return true;
	}

	/**
	 * 如果从row和col作为起始的话，那么整个循环完就不能直接返回true
	 * 而要返回false
	 * 如果都是从0开始，则相当于每次进来都是从第一个元素开始遍历判断
	 * 的，那么整个循环完还没有返回错误，那就相当于是正确的。
	 */
	//for (i = row; i < 9; ++i) {
		//for (j = col; j < 9; ++j) {
	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			// 跳过已经有数字的地方
			if (board[i][j] == '.') {
				// 选择一个可填入的数值
				for (k = 0; k < 9; ++k) {
					if (used[i][k] == 0) {
						// 修剪条件
						if (is_valid(board, i, j, k + 1)) {
							board[i][j] = (k + 1) + '0';	// 填写值
							used[i][k] = 1;			// 标记
							//printf("[%d-%d] try %d\r\n", i, j, k + 1);
							if (fill_num(board, used, row, j + 1))
								return true;
						
							// 撤销选择
							board[i][j] = '.';
							used[i][k] = 0;
						}
					}
				}
				//printf("[%d-%d] test end.\r\n", i, j);
				return false;	// 可选填的数值都填完了，没有合适的，就返回错误
			}
		}
	}
	printf("out here\r\n");
	return true;
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
	int		i = 0;
	int		j = 0;
	char**	used = calloc(1, sizeof(void*)*boardSize);

	for (i = 0; i < boardSize; ++i) {
		used[i] = calloc(1, sizeof(char)*boardSize);	
		for (j = 0; j < boardSize; ++j) {
			printf("%c ", board[i][j]);
			if (board[i][j] != '.') {
				used[i][board[i][j] - '0' - 1] = 1;
			}
		}
		printf("\r\n");
	}

	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			printf("%d ", used[i][j]);
		}
		printf("\r\n");
	}

	fill_num(board, used, 0, 0);
}

void main(int argc, char* argv[])
{
	/**
	 * 注意solveSudoku接口的第一个参数是二级指针，那么它第一纬度的步进单位
	 * 就是一个指针的大小。也即是实参必须也是这样的，也就是下面这种形式传递
	 * 而不能直接定义一个二维数组
	 */
	char*	board[9] = {0};
	char board_1[9] = {'5','3','.','.','7','.','.','.','.'};
	char board_2[9] = {'6','.','.','1','9','5','.','.','.'};
	char board_3[9] = {'.','9','8','.','.','.','.','6','.'};
	char board_4[9] = {'8','.','.','.','6','.','.','.','3'};
	char board_5[9] = {'4','.','.','8','.','3','.','.','1'};
	char board_6[9] = {'7','.','.','.','2','.','.','.','6'};
	char board_7[9] = {'.','6','.','.','.','.','2','8','.'};
	char board_8[9] = {'.','.','.','4','1','9','.','.','5'};
	char board_9[9] = {'.','.','.','.','8','.','.','7','9'};
	board[0] = board_1;
	board[1] = board_2;
	board[2] = board_3;
	board[3] = board_4;
	board[4] = board_5;
	board[5] = board_6;
	board[6] = board_7;
	board[7] = board_8;
	board[8] = board_9;

	solveSudoku((char**)board, 9, NULL);
}
