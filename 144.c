/*****************************************************
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 * 展开后的单链表应该同样使用 TreeNode ，其中 right
 * 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 ****************************************************/

/**
 * 通过一个实际的转换例子可以看出，就是将二叉树进行前序遍历
 * 把每个节点串起来形成一个新的链表。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
	int	val;
	struct TreeNode* left;
	struct TreeNode* right;	
};

struct list_node {
	void* data;
	struct list_node* next;
};

/**
 * 以一个前序遍历的数组形式来生成一个二叉树，#表示节点为空
 */
void create_btree_node(int* nums, int* index, int limit, struct TreeNode** node)
{
	if (*index > limit || nums[*index] == '#')
		return ;
	*node = calloc(1, sizeof(struct TreeNode));
	(*node)->val= nums[*index];
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
void create_btree(int* nums, int nums_size, struct TreeNode** root)
{
	struct TreeNode* r = NULL;
	struct TreeNode* node = NULL;
	int		i = 0;
	int		index = 0;
	
	create_btree_node(nums, &index, nums_size - 1, root);
}
struct list_node* pre_order_tran(struct TreeNode* node, struct list_node* list)
{
	if (!node)
		return list;
	struct list_node* last = NULL; 
	struct list_node* lnode = calloc(1, sizeof(struct list_node));	

	printf("add %d\r\n", node->val);
	lnode->data = node;
	list->next = lnode;
	last = pre_order_tran(node->left, lnode);
	last = pre_order_tran(node->right, last);
	
	return last;
}

/**
 * 通过递归方式前序遍历，创建一个新的链表，
 */
void faltten(struct TreeNode* root)
{
	struct list_node*	list = NULL;
	struct list_node*	tmp = NULL;
	struct TreeNode*	tree_node = NULL;
	if (!root)
		return;
	list = calloc(1, sizeof(struct list_node));
	pre_order_tran(root, list);
	printf("trans end\r\n");
	tmp = list;
	while (tmp) {
		tree_node = (struct TreeNode*)(tmp->data);
		printf("%d \r\n", tree_node->val);
		tree_node->left = NULL;
		tree_node->right = tmp->next->data;
		tmp = tmp->next;	
	}
	printf("\r\n");
}


void main(int argc, char* argv[])
{
	int	nums[] = {1, 2, 3, '#', '#', 4, '#', 5, '#', '#', 6, 7, '#', '#', 8, 9, 11, '#', '#', '#', 10, '#', 12, '#', '#'};
	struct TreeNode* root = NULL;

	create_btree(nums, sizeof(nums)/sizeof(nums[0]), &root);
	printf("create end.\r\n");

	faltten(root);	
}
