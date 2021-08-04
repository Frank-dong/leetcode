/********************************************************
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 *
 * 展开后的单链表应该同样使用 TreeNode ，其中 right 
 * 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 * ******************************************************/

/**
 * 根据题目里的图例很容易看出，需要变换的顺序，正好就是二叉树
 * 前序遍历的顺序。所以可以采用前序便利的方法，生成一个新的链
 * 表，然后遍历链表，修改二叉树节点的左右子节点指针。
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct TreeNode {
	int	val;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct tree_list {
	struct TreeNode*	node;
	struct tree_list*	next;
};

/**
 * 在利用递归创建时，需要注意要保证标号(index)每次都会被修改,
 * 并且每个过程都是递增上去的, 也就是第二个参数index需要传地址
 * 这是关键
 */
void create_btree_node(int* nums, int* index, int limit, struct TreeNode** node)
{
	if (*index > limit || nums[*index] == '#')
		return ;
	*node = calloc(1, sizeof(struct TreeNode));
	(*node)->val = nums[*index];

	++(*index);
	create_btree_node(nums, index, limit, &(*node)->left);
	++(*index);
	create_btree_node(nums, index, limit, &(*node)->right);
}

/**
 * 从一个数列按照前序遍历方式生成一个二叉树
 * 数列中的某个值为'#'表示此值为空
 */
void create_btree(int* nums, int nums_size, struct TreeNode** root)
{
	struct TreeNode* r = NULL;
	struct TreeNode* node = NULL;
	int		i = 0;
	
	create_btree_node(nums, &i, nums_size - 1, root);
}

struct tree_list* pre_order_traversal(struct TreeNode* node, struct tree_list* tree)
{
	struct tree_list* last = NULL;
	struct tree_list* new_node = NULL;
	if (!node)
		return tree;

	new_node = calloc(1, sizeof(struct tree_list));	
	new_node->node = node;
	tree->next = new_node;
	if (tree->node)
		printf("last = %d, add %d to list\r\n", tree->node->val, node->val);

	last = pre_order_traversal(node->left, new_node);
	last = pre_order_traversal(node->right, last);
	return last;
}

void flatten(struct TreeNode* root)
{
	struct tree_list	list = {NULL, NULL};
	struct tree_list*	tmp = NULL;
	struct TreeNode*	tree_tmp = NULL;


	// 先遍历生成一个新的链表
	pre_order_traversal(root, &list);

	// 通过链表修改原节点中的左右指针指向
	tmp = (&list)->next;
	while (tmp) {
		//printf("%d ", tmp->node->val);			
		tmp->node->left = NULL;
		if (tmp->next)
			tmp->node->right = tmp->next->node;
		tmp = tmp->next;
	}

	// 遍历新生成的二叉树链表进行验证
	tree_tmp = root;
	while (tree_tmp->right) {
		printf("%d ", tree_tmp->val);			
		tree_tmp = tree_tmp->right;
	}
}

int main(int argc, char* argv[])
{
	int	nums[] = {1, 2, 3, 4, '#', '#', 5, '#', '#', 6, '#', 7, '#', '#', 8, 9, '#', '#', 10, '#', 11, '#', '#'};
	struct TreeNode* root = NULL;

	create_btree(nums, sizeof(nums)/sizeof(nums[0]), &root);
	flatten(root);
}
