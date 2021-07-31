#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "b_tree.h"

/**
 * 以一个中序遍历的数组形式来生成一个二叉树，#表示节点为空
 */
void create_btree_node(int* nums, int* index, int limit, struct BTreeNode** node)
{
	if (*index > limit || nums[*index] == '#')
		return ;
	*node = calloc(1, sizeof(struct BTreeNode));
	(*node)->data = nums[*index];
	printf("add node %d\r\n", nums[*index]);

	++(*index);
	create_btree_node(nums, index, limit, &(*node)->left);
	
	++(*index);
	create_btree_node(nums, index, limit, &(*node)->right);
}

/**
 * 从一个数列按照前序遍历方式生成一个二叉树
 * 数列中的某个值为'#'表示此值为空
 */
void create_btree(int* nums, int nums_size, struct BTreeNode** root)
{
	struct BTreeNode* r = NULL;
	struct BTreeNode* node = NULL;
	int		i = 0;
	int		index = 0;
	
	create_btree_node(nums, &index, nums_size - 1, root);
}

/**
 * 前序遍历
 */
void pre_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	pre_order_traversal(root->left);
	printf("%d ", root->data);
	pre_order_traversal(root->right);
}
/**
 * 中序遍历
 */ 
void in_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	printf("%d ", root->data);
	in_order_traversal(root->left);
	in_order_traversal(root->right);
}

/**
 * 后序遍历
 */ 
void post_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	post_order_traversal(root->left);
	post_order_traversal(root->right);
	printf("%d ", root->data);
}
