#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_tree.h"


int main(int argc, char *argv[])
{
	int	nums[] = {'#', 2, 3, 4, '#', '#', 5, 6, '#', 7, 8, 9, 10};
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
}
