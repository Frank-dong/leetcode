/********************************************************
 * 罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。

 * 字符          数值
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做
 *  XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
 * 通常情况下，罗马数字中小的数字在大的数字的右边。但也存
 * 在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 
 * 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
 * 同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
 *
 * I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
 * X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
 * C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
 *
 * 给你一个整数，将其转为罗马数字。
 ********************************************************/

#include "stdio.h"
#include "stdlib.h"

/**
 * 此题初看有点像兑换硬币的题目，但是此题中进制已确定
 * 直接根据进制，逐个位进行转换
 * 首先得到输入整数的最大位数，然后向后逐个转换
 *
 * 各个进制处理中有相似部分，可以优化代码
 */
char * intToRoman(int num)
{
	int		i = 0;
	int		div = 1;
	int		tmp = num;
	int		num_sig = 0;
	int		pos = 0;
	char*	str = calloc(1, 30);

	while (tmp / 10) {
		div *= 10;
		tmp = tmp/10;
	}
	
	tmp = num;
	while (div != 0 && tmp != 0) {
		if (tmp/div == 0) {
			div /= 10;
			continue;
		}
		num_sig = tmp/div;
		if (div >= 1000) {
			for (i = 1; i < num_sig; ++i) {
				str[pos++] = 'M';
			}
			str[pos++] = 'M';
		} else if (div == 100) {
			if (num_sig == 9) {
				str[pos++] = 'C';
				str[pos++] = 'M';
			} else if (num_sig == 4) {
				str[pos++] = 'C';
				str[pos++] = 'D';
			} else if (num_sig == 5) {
				str[pos++] = 'D';
			} else {
				if (num_sig > 5) {
					str[pos++] = 'D';
					num_sig -= 5;
				}
				for (i = 1; i < num_sig; ++i) {
					str[pos++] = 'C';
				}
				str[pos++] = 'C';
			}
		} else if (div == 10) {
			if (num_sig == 9) {
				str[pos++] = 'X';
				str[pos++] = 'C';
			} else if (num_sig == 4) {
				str[pos++] = 'X';
				str[pos++] = 'L';
			} else if (num_sig == 5) {
				str[pos++] = 'L';
			} else {
				if (num_sig > 5) {
					str[pos++] = 'L';
					num_sig -= 5;
				}
				for (i = 1; i < num_sig; ++i) {
					str[pos++] = 'X';
				}
				str[pos++] = 'X';
			}
		} else {
			if (num_sig == 9) {
				str[pos++] = 'I';
				str[pos++] = 'X';
			} else if (num_sig == 4) {
				str[pos++] = 'I';
				str[pos++] = 'V';
			} else if (num_sig == 5) {
				str[pos++] = 'V';
			} else {
				if (num_sig > 5) {
					str[pos++] = 'V';
					num_sig -= 5;
				}
				for (i = 0; i < num_sig; ++i) {
					str[pos++] = 'I';
				}
			}
		}
		tmp = tmp%div;
		div /= 10;
	}
	return str;
}


struct Roman_val {
	char	sym[12];
	int		val;
};
/**
 * 上面的算法显然不是出题者想要的解法。
 * 可以使用贪心算法, 把所有表示数值的字符罗列出来，然后拆解数字
 * 寻找当前满足的最大的值，最后组合出来的就是需要的字符串。
 */
char * intToRoman_1(int num)
{
	// 由于使用贪心算法，所以列表顺序由大值到小值罗列
	struct Roman_val val_list[] = {
		{"M", 1000},
		{"CM", 900},
		{"D", 500},
		{"CD", 400},
		{"C", 100},
		{"XC", 90},
		{"L", 50},
		{"XL", 40},
		{"X", 10},
		{"IX", 9},
		{"V", 5},
		{"IV", 4},
		{"I", 1},
		{"", 0}	// 结束标志
	};
	char*	rst = NULL;
	int		pos = 0;
	int		i = 0;

	rst = calloc(1, 100);
	while (num > 0) {
		for (i = 0; val_list[i].val != 0; ++i) {
			if (num >= val_list[i].val) {
				strcpy(rst + pos, val_list[i].sym);
				pos += strlen(val_list[i].sym);
				num -= val_list[i].val;
				break;
			}
		}
	}
	return rst;
}


int main(int argc, char* argv[])
{
	char*	rst = intToRoman(atoi(argv[1]));

	printf("rst = %s\r\n", rst);

	rst = intToRoman_1(atoi(argv[1]));
	printf("rst = %s\r\n", rst);
	
	free(rst);

	return 0;
}
