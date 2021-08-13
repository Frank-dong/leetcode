/********************************************************
 * 给定一个二叉树，找出其最小深度。
 *
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 *
 * 说明：叶子节点是指没有子节点的节点。
 * ******************************************************/

/**
 * 求最小深度，也就是广度优先，直到遍历到一个节点没有左右节点为止
 */
struct node_queue {
	struct TreeNode* node;
	struct node_queue* next;
	int deep;
};

struct node_queue* init_queue()
{
	struct node_queue* queue = calloc(1, sizeof(struct node_queue));
	return queue;
}

void queue_add_tail(struct node_queue* queue, struct TreeNode* node, int deep)
{
	while (queue->next) {
		queue = queue->next;
	}
	struct node_queue* _node = calloc(1, sizeof(struct node_queue));
	_node->node = node;
	_node->deep = deep;
	queue->next = _node;
}
int minDepth(struct TreeNode* root){
	struct node_queue* head = init_queue();
	struct node_queue* qnode = NULL;
	struct node_queue* tmp = NULL;
	struct TreeNode* node = NULL;
	int ret = 0;

	if (!root)
		return 0;
	queue_add_tail(head, root, 1);
	while (head->next) {
		// 这里可以再加一层循环，每次遍历完当前队列中所有的节点，然后再进行下一步的扩散入队。
		// 这样就不用在各自节点中记录深度，更加通用一些。
		qnode = head->next;
		node = qnode->node;
		if (!node->left && !node->right) {
			ret = qnode->deep;
			break;
		}
		if (node->left)
			queue_add_tail(head, node->left, qnode->deep+1);
		if (node->right)
			queue_add_tail(head, node->right, qnode->deep+1);
		tmp = head->next;
		head->next = head->next->next;
		free(tmp);
	}
	while (head->next) {
		tmp = head->next;
		head->next = head->next->next;
		free(tmp);
	}
	free(head);
	return ret;
}
