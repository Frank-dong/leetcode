#ifndef __B_TREE_H__
#define __B_TREE_H__
struct BTreeNode {
	int	data;
	struct BTreeNode* left;
	struct BTreeNode* right;
};

void create_btree(int* nums, int nums_size, struct BTreeNode** root);
void pre_order_traversal(struct BTreeNode* root);
void in_order_traversal(struct BTreeNode* root);
void post_order_traversal(struct BTreeNode* root);

int pre_order_no_recursion(struct BTreeNode* root);
int in_order_no_recursion(struct BTreeNode* root);
int post_order_no_recursion(struct BTreeNode* root);
#endif //__B_TREE_H__
