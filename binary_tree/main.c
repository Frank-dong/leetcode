#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_tree.h"


int main(int argc, char *argv[])
{
	int	nums[] = {1, 2, 3, '#', '#', 4, '#', 5, '#', '#', 6, 7, '#', '#', 8, 9, 11, '#', '#', '#', 10, '#', 12, '#', '#'};
	struct BTreeNode* root = NULL;

	create_btree(nums, sizeof(nums)/sizeof(nums[0]), &root);

	printf("pre order traversal: ");
	pre_order_traversal(root);
	printf("\r\n");

	printf("in order traversal: ");
	in_order_traversal(root);
	printf("\r\n");

	printf("post oder traversal: ");
	post_order_traversal(root);
	printf("\r\n");

	printf("----------------------\r\n");
	printf("       NO recursion   \r\n");
	pre_order_no_recursion(root);
	printf("\r\n");
	
	in_order_no_recursion(root);
	printf("\r\n");
	
	post_order_no_recursion(root);
	printf("\r\n");
}
