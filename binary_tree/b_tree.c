#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "b_tree.h"

/**
 * 以一个前序遍历的数组形式来生成一个二叉树，#表示节点为空
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
 * 前序遍历(根左右)
 */
void pre_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	printf("%d ", root->data);
	pre_order_traversal(root->left);
	pre_order_traversal(root->right);
}
/**
 * 中序遍历(左根右)
 */ 
void in_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	in_order_traversal(root->left);
	printf("%d ", root->data);
	in_order_traversal(root->right);
}

/**
 * 后序遍历(左右根)
 */ 
void post_order_traversal(struct BTreeNode* root)
{
	if (!root)
		return;

	post_order_traversal(root->left);
	post_order_traversal(root->right);
	printf("%d ", root->data);
}
//--------------------------------------------------------------------
// 以上是使用递归的方式遍历二叉树
// 下面使用非递归的方式进行遍历，需要借助栈结构来实现
//--------------------------------------------------------------------

struct stack_node {
	void*	 data;
	struct stack_node* next;
};

/**
 * data 记录个数
 * next 记录top节点
 */
struct stack_node* create_stack(void)
{
	struct stack_node* head = calloc(1, sizeof(struct stack_node));
	return head;
}

void stack_destroy(struct stack_node* stack)
{
	struct stack_node* tmp = NULL;
	while (stack->next) {
		tmp = stack->next;
		stack->next = stack->next->next;	
		free(tmp);
	}
	free(stack);
}

void stack_push(struct stack_node* stack, void* data)
{
	if (!stack) {
		return;
	}

	struct stack_node* node = calloc(1, sizeof(struct stack_node));
	node->data = data;
	node->next = stack->next;
	stack->next = node;
}

void* stack_pop(struct stack_node* stack)
{
	struct stack_node* tmp = NULL;
	void* data = NULL;

	if (!stack || !stack->next)
		return NULL;
	data = stack->next->data;
	tmp = stack->next;
	stack->next = stack->next->next;
	free(tmp);
	return data;
}

/**
 * 前序遍历，访问根节点，并压入栈，然后访问左节点，并且入栈，直到
 * 左节点为空，此时出栈根节点，访问右节点
 */
int pre_order_no_recursion(struct BTreeNode* root)
{
	struct stack_node* stack = create_stack();	
	struct BTreeNode* node = root;
	while (1) {
		if (node) {
			// 访问根节点，并压入栈
			printf("%d ", node->data);
			stack_push(stack, node);
			node = node->left;
		} else {
			node = stack_pop(stack);	
			if (!node)
				break;
			node = node->right;
		}
	}
	stack_destroy(stack);
	return 0;
}

/**
 * 中序遍历，先入栈根节点，然后访问左节点，然后出栈根节点，访问
 * 根节点，访问右节点
 */
int in_order_no_recursion(struct BTreeNode* root)
{
	struct stack_node*	stack = create_stack();	
	struct BTreeNode*	node = root;
	while (1) {
		if (node) {
			stack_push(stack, node);
			node = node->left;
		} else {
			node = stack_pop(stack);
			if (!node)
				break;
			printf("%d ", node->data);	
			node = node->right;
		}
	}
	stack_destroy(stack);
	return 0;
}

int post_order_no_recursion(struct BTreeNode* root)
{
	struct stack_node*	stack = create_stack();
	struct BTreeNode*	node = root;
	struct BTreeNode*	tmp = NULL;
	while (1) {
		if (node) {
			// 判断是否是根节点
			if (tmp && tmp == node->right) {
				printf("%d ", node->data);
				tmp = node;
				node = stack_pop(stack);
				if (!node)
					break;
				//printf("pop %d\r\n", node->data);
			} else if (tmp && tmp == node->left) {
				//printf("push %d\r\n", node->data);
				stack_push(stack, node);
				node = node->right;
			} else {
				//printf("push %d\r\n", node->data);
				stack_push(stack, node);
				node = node->left;
			}
		} else {
			node = stack_pop(stack);
			if (!node)
				break;
			//printf("pop %d\r\n", node->data);
			if (node->right) {
				//printf("push %d\r\n", node->data);
				stack_push(stack, node);
				node = node->right;
			} else {
				printf("%d ", node->data);		
				tmp = node;
				node = stack_pop(stack);
				if (!node)
					break;
				//printf("pop %d\r\n", node->data);
			}
		}
	}
	stack_destroy(stack);
	return 0;
}

//--------------------------------------------------------------------
// 以上是使用使用深度优先DFS(Deep First Search)和BFS(Breadth First Search)
// 来遍历二叉树
// 参考链接：
// https://developer.51cto.com/art/202004/614590.html
//--------------------------------------------------------------------
/**
 * 对于二叉树来说或，深度优先，就是二叉树的前序遍历
 */


/**
 * 广度优先，也叫做层级遍历，就是遍历一个节点的同一层的相邻节点
 * 可以使用队列来实现，从根节点开始，访问后就入队左右子节点，然后每访问一个
 * 节点，就需要入队左右节点，这样的话，访问一层，就同时入队了下一层。达到
 * 层级访问的目的。
 */




































